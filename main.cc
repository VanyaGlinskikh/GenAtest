#include "global.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "LTexture.h"
#include "Dot.h"
#include "Bullet.h"
#include "LTexGlobal.h"
#include "FiniteStateMachine.h"
//#include "vector";

#include "Sensor.h"
#include "VisionEnemySensor.h"
#include "VisionDotBulletSensor.h"
#include "CheckTeammatesSensor.h"
#include "Azimuth.h"

#include <functional>

SDL_Window* gWindow = NULL;

LTexture gEnemyBulletTexture;
LTexture gBulletTexture;
LTexture gEnemyTexture;
LTexture gBGTexture;


bool init();

bool loadMedia();

void close();

bool init()
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	if( !gDotTexture.loadFromFile( "dot.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !gBulletTexture.loadFromFile( "bullet.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !gEnemyBulletTexture.loadFromFile( "bullet.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !gEnemyTexture.loadFromFile( "enemy.bmp" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}

	if( !gBGTexture.loadFromFile( "bg.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	return success;
}

void close()
{
	gEnemyBulletTexture.free();
	gDotTexture.free();
	gBulletTexture.free();
	gEnemyTexture.free();
	gBGTexture.free();

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			bool quit = false;

			SDL_Event e;

			VisionEnemySensor *visionEnemySensor = new VisionEnemySensor;
			VisionDotBulletSensor *visionDotBulletSensor = new VisionDotBulletSensor;
//			CheckTeammatesSensor *checkTeammatesSensor = new CheckTeammatesSensor;
			Azimuth *azimuthSensor = new Azimuth;
			Dot dot;
			Bullet bullet;
			std::vector<Genome> genome(NUMBEROFOPPONENTS);
			std::vector<std::shared_ptr<Enemy>> enemy(NUMBEROFOPPONENTS);
			std::function<double(unsigned int)> s1;
			std::function<double(unsigned int)> s2;
			std::function<double(unsigned int)> s3;
			std::function<void(unsigned int)> f1;
			std::function<void(unsigned int)> f2;
			std::function<void(unsigned int)> f3;

			for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
				genome[i].add_section({1,2,3,4,5});
				genome[i].add_section({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,12,
									   1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,12,
									   1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,12,
									   1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,12,
									   1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,12,
									   1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,12,
									   1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,12,
									   1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,12});
				enemy[i] = std::make_shared<Enemy>(i, genome[i]);
				s1 = [&](unsigned id) -> double { return azimuthSensor->checkA((*enemy[id]), dot); };
				enemy[i] ->add_sensor(s1);
				s2 = [&](unsigned id) -> double { return visionEnemySensor->location((*enemy[id]), dot); };
				enemy[i] ->add_sensor(s2);
				s3 = [&](unsigned id) -> double { return visionDotBulletSensor->location((*enemy[id]), bullet); };
				enemy[i] ->add_sensor(s3);
				f1 = [&](unsigned id){ enemy[id]->moveStraight(); };
				enemy[i]->add_actor(f1);
				f2 = [&](unsigned id){
					std::cout<<"актор два ";
					enemy[id]->moveLeft(); };
				enemy[i]->add_actor(f2);
				f3 = [&](unsigned id){ enemy[id]->moveRight(); };
				enemy[i]->add_actor(f3);

			}

			std::vector<EnemyBullet> enemyBullet(NUMBEROFENEMYBULLETS);
//			FiniteStateMachine finiteStateMachine;


//			std::vector<std::shared_ptr<Sensor>> sensors;
//			sensors.push_back(std::make_shared<VisionEnemySensor>());
//			sensors.push_back(std::make_shared<VisionDotBulletSensor>());
//			sensors.push_back(std::make_shared<CheckTeammatesSensor>());
//			sensors.push_back(std::make_shared<Azimuth>());
//			double an = 0;
//			int ves = 0;
			int scrollingOffset = 0;

			while( !quit )
			{
				while( SDL_PollEvent( &e ) != 0 )
				{
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					dot.handleEvent( e );
					bullet.handleEvent(e, dot);
				}
				bullet.move(dot);
				for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
//					enemyBullet[i].move(enemy[i]);
//					enemy[i].move(bullet);

					dot.move(enemyBullet[i]);
//					finiteStateMachine.funk(sensors, enemy[i], bullet, dot, enemy);
				}

				++scrollingOffset;
				if( scrollingOffset > gBGTexture.getHeight() )
				{
					scrollingOffset = 0;
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render background
				gBGTexture.render( 0, scrollingOffset );
				gBGTexture.render( 0, scrollingOffset - gBGTexture.getHeight() );

				bullet.render();
				dot.render();



				for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
					enemy[i] ->tick();
					enemy[i] ->render();
//					an = azimuthSensor->checkA(enemy[i], dot);
//					ves = visionEnemySensor->location(enemy[i], dot);
//					an = azimuthSensor->checkA(enemy[i], dot);
//					ves = visionEnemySensor->location(enemy[i], dot);
//					enemy[i].render(an, ves);
//					enemyBullet[i].render();
//					visionDotBulletSensor->location(enemy[i], bullet);
//					visionEnemySensor->location(enemy[i], dot);
//					visionEnemySensor.location(enemy[i], dot);
//					visionDotBulletSensor.location(enemy[i], bullet);
//					std::cout<<"противник "<<i<<" находится по координатам x= "<<enemy[i].getMPosX()<<" y= "<<enemy[i].getMPosY()<<std::endl;
//					std::cout<<"пуля "<<i<<" находится по координатам x= "<<enemyBullet[i].getMPosX()<<" y= "<<enemyBullet[i].getMPosY()<<std::endl;

				}

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	close();

	return 0;
}
