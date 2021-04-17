#include "global.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "LTexture.h"
#include "Dot.h"
#include "Bullet.h"
#include "LTexGlobal.h"
//#include "FiniteStateMachine.h"
//#include "vector";

#include "Sensor.h"
#include "VisionEnemySensor.h"
#include "VisionDotBulletSensor.h"
#include "CheckTeammatesSensor.h"
#include "Azimuth.h"
#include "WallVerticalSensor.h"
#include "WallGorizontalSensor.h"

#include <functional>
#include <chrono>

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
			WallVerticalSensor *wallVerticalSensor = new WallVerticalSensor;
			WallGorizontalSensor *wallGorizontalSensor = new WallGorizontalSensor;

			Dot dot;
			Bullet bullet;
			std::vector<EnemyBullet> enemyBullet(NUMBEROFOPPONENTS);
			std::vector<Genome> genome(NUMBEROFOPPONENTS);
			std::vector<std::shared_ptr<Enemy>> enemy(NUMBEROFOPPONENTS);
			std::function<double(unsigned int)> s1;
			std::function<double(unsigned int)> s2;
			std::function<double(unsigned int)> s3;
			std::function<double(unsigned int)> s4;
			std::function<double(unsigned int)> s5;
			std::function<void(unsigned int)> f1;
			std::function<void(unsigned int)> f2;
			std::function<void(unsigned int)> f3;
			std::function<void(unsigned int)> f4;
			std::vector<int> sec2(2560);

			for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
				genome[i].add_section({1,2,3,4,5});

				for (int j = 0; j < 16; ++j) {

					sec2[i] =  1*rand() % 9;
					sec2[i+16] =1*rand() % 9;
					sec2[i+32] = 1*rand() % 9;
					sec2[i+48] = 1*rand() % 9;
					sec2[i+64] = 1*rand() % 9;
					sec2[i+80] = 1*rand() % 9;
					sec2[i+96] = 1*rand() % 9;
					sec2[i+112] = 1*rand() % 9;
					sec2[i+128] = 1*rand() % 9;
					sec2[i+144] = 1*rand() % 9;
					sec2[i+160] = 1*rand() % 9;
				}
				genome[i].add_section(sec2);  // 2^predic* sensors

				enemy[i] = std::make_shared<Enemy>(i, genome[i]);
				s1 = [&](unsigned id) -> double { return azimuthSensor->checkA((*enemy[id]), dot); };
				enemy[i] ->add_sensor(s1);
				s2 = [&](unsigned id) -> double { return visionEnemySensor->location((*enemy[id]), dot); };
				enemy[i] ->add_sensor(s2);
				s3 = [&](unsigned id) -> double { return visionDotBulletSensor->location((*enemy[id]), bullet); };
				enemy[i] ->add_sensor(s3);
				s4 = [&](unsigned id) -> double { return wallVerticalSensor->location((enemy[id])); };
				enemy[i] ->add_sensor(s4);
				s5 = [&](unsigned id) -> double { return wallGorizontalSensor->location((enemy[id])); };
				enemy[i] ->add_sensor(s5);
				f1 = [&](unsigned id){ enemy[id]->moveStraight(); };
				enemy[i]->add_actor(f1);
				f2 = [&](unsigned id){ enemy[id]->moveLeft(); };
				enemy[i]->add_actor(f2);
				f3 = [&](unsigned id){ enemy[id]->moveRight(); };
				enemy[i]->add_actor(f3);
				f4 = [&](unsigned id){ enemy[id]->moveBull(enemyBullet[i]); };
				enemy[i]->add_actor(f4);

			}


//			double an = 0;
//			int ves = 0;
			int scrollingOffset = 0;
			using clk = std::chrono::high_resolution_clock;
			auto start = clk::now();
			auto stop = start + std::chrono::seconds(10);

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
					bullet.hittingTheEnemy(*enemy[i]);
					enemy[i] ->render();

//					enemy[i] ->moveBull(enemyBullet[i]);
//					enemyBullet[i].move(enemy[i]->getMPosX(), enemy[i]->getMPosY());
//					enemyBullet[i].render();
				}

				for (int i = 0; i < NUMBEROFENEMYBULLETS; ++i) {
					for (int j = 0; j < NUMBEROFENEMYBULLETS; ++j) {
						enemyBullet[i].hittingTheAlly(*enemy[j]);
					}
				}

				if (clk::now() >= stop){
					std::cout<<"время прошло"<<std::endl;
					start = clk::now();
					stop = start + std::chrono::seconds(10);
					for (int k = 0; k < NUMBEROFOPPONENTS; ++k) {
						{
							enemy[k]->getVelY(1);
							enemy[k]->getVelX(1);
							enemy[k]->setMPosX();
							enemy[k]->setMPosY();
//							genome[k-1].mutate(1, k-1, 2);
//							genome[k-1] = splice(genome[k-1], genome[k], order);
						}
					}
				}

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	close();

	return 0;
}
