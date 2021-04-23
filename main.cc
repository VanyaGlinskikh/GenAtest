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

#include <fstream>

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

			std::random_device random_device;
			std::mt19937 engine{ random_device() };
			std::uniform_int_distribution<> dist2(0, 9);
			std::uniform_int_distribution<> forX(1, 620);
			std::uniform_int_distribution<> forY(20, 80);

			std::uniform_int_distribution<> forOrder(0, 254);
			std::uniform_int_distribution<> forSplice(0, 7);
			std::uniform_int_distribution<> forSection(0, 1);
			std::uniform_int_distribution<> forLocation(0, 1);
			std::uniform_int_distribution<> forBit(0, 3);

			for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
				genome[i].add_section({1,2,3,4});

				for (int j = 0; j < 160; ++j) {
					sec2[j] =  dist2(random_device);
					sec2[j+160] = dist2(random_device);
					sec2[j+320] = dist2(random_device);
					sec2[j+480] = dist2(random_device);
					sec2[j+640] = dist2(random_device);
					sec2[j+800] = dist2(random_device);
					sec2[j+960] = dist2(random_device);
					sec2[j+1120] = dist2(random_device);
					sec2[j+1280] = dist2(random_device);
					sec2[j+1440] = dist2(random_device);
					sec2[j+1600] = dist2(random_device);
					sec2[j+1760] = dist2(random_device);
					sec2[j+1920] = dist2(random_device);
					sec2[j+2080] = dist2(random_device);
					sec2[j+2240] = dist2(random_device);
					sec2[j+2400] = dist2(random_device);
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
				f4 = [&](unsigned id){ enemy[id]->moveShot(enemyBullet[i]); };
				enemy[i]->add_actor(f4);

				enemy[i]->resetTickCount();

			}


//			double an = 0;
//			int ves = 0;
			int scrollingOffset = 0;
			using clk = std::chrono::high_resolution_clock;
			auto start = clk::now();
			auto stop = start + std::chrono::seconds(10);


			std::vector<std::shared_ptr<Enemy>> favoriteEnemy(8);
			std::vector<std::shared_ptr<Enemy>> sortEnemy(NUMBEROFOPPONENTS);
			std::vector<Genome> sortG(NUMBEROFOPPONENTS);
			std::vector<uint8_t>  order;
			for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
				sortEnemy[i] = enemy[i];
			}

			std::ofstream out;          // поток для записи
			out.open("D:\\hello.txt"); // окрываем файл для записи
			if (out.is_open())
			{
				std::cout<<" запись произошла  "<< std::endl;
				for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
					out <<" существо "<<i<<": "<< std::endl;
					for (int j = 0; j < 2; ++j) {
						out <<" секция "<<j<<" размер секции  "<<genome[i].section_size(j)<< std::endl;
						for (unsigned k = 0; k < genome[i].section_size(j); ++k) {
							out <<genome[i].operator ()(j, k)<< " ";
						}
						out <<"\n"<< std::endl;
					}
				}
			}

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
//						std::cout<<enemy[i]->getTickCount()<<std::endl;
					bullet.hittingTheEnemy(*enemy[i]);
					enemy[i] ->render();
					enemy[i] ->moveBull(enemyBullet[i]);
//					enemyBullet[i].move(enemy[i]->getMPosX(), enemy[i]->getMPosY());
//					enemyBullet[i].render();
				}

				for (int i = 0; i < NUMBEROFENEMYBULLETS; ++i) {
					for (int j = 0; j < NUMBEROFENEMYBULLETS; ++j) {
						enemyBullet[i].hittingTheAlly(*enemy[j]);
					}
				}

//				sort(masLive.begin(), masLive.end());


				if (clk::now() >= stop){
					std::cout<<"время прошло"<<std::endl;
					start = clk::now();
					stop = start + std::chrono::seconds(10);



					for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
//						std::cout<<enemy[q]->getTickCount()<<",  ";
						for (int j = 0; j < NUMBEROFOPPONENTS; ++j) {
							if (sortEnemy[i]->getTickCount() > sortEnemy[j]->getTickCount() ){
								std::shared_ptr<Enemy> enemy = sortEnemy[i];
								Genome &gs  = genome[i];
								sortEnemy[i] = sortEnemy[j];
								genome[i] = genome[j];
								sortEnemy[j] = enemy;
								genome[j] = gs;
							}
						}
					}


					order.resize(genome.size());
					for (unsigned i = 0; i < order.size(); ++i) {
						order[i] = forOrder(random_device);
					}


					for (int i = 1; i <= 8; ++i) {
						genome[i+7] =  splice(genome[forSplice(random_device)], genome[forSplice(random_device)], order) ;
						genome[i+15] = genome[i-1];
						genome[i+15].mutate(forSection(random_device), forLocation(random_device), forBit(random_device));
						genome[i+23] =  splice(genome[forSplice(random_device)], genome[forSplice(random_device)], order) ;
						genome[i+23].mutate(forSection(random_device), forLocation(random_device), forBit(random_device));
					}

//					std::cout<<" отсортированный ";
//					for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
//						std::cout<<" "<<sortEnemy[i]->getTickCount()<<",  ";
//					}
//					std::cout<<"  "<<std::endl;
//					std::cout<<" дефолт ";
//					for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
//						std::cout<<" "<<enemy[i]->getTickCount()<<",  ";
//					}
//					std::cout<<"  "<<std::endl;


					for (int k = 0; k < NUMBEROFOPPONENTS; ++k)
					{


						enemy[k]->setVelY(1);
						enemy[k]->setVelX(1);
						enemy[k]->resetTickCount();
						enemy[k]->setDead(false);
						enemy[k]->setMPosX(forX(random_device));
						enemy[k]->setMPosY(forY(random_device));
//							genome[k-1].mutate(1, k-1, 2);
//							genome[k-1] = splice(genome[k-1], genome[k], order);
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
