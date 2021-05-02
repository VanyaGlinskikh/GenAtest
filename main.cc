#include "global.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "LTexture.h"
#include "Dot.h"
#include "Bullet.h"

//#include "FiniteStateMachine.h"
//#include "vector";

#include "Sensor.h"
#include "VisionEnemySensor.h"
#include "VisionDotBulletSensor.h"
#include "VisionAllySensor.h"
#include "VisionAllyBulletSensor.h"

#include "CheckTeammatesSensor.h"
#include "Azimuth.h"
#include "WallVerticalSensor.h"
#include "WallGorizontalSensor.h"

#include <fstream>

#include <functional>
#include <chrono>

SDL_Window* gWindow = NULL;
TTF_Font *gFont = NULL;

LTexture gEnemyBulletTexture;
LTexture gBulletTexture;
LTexture gEnemyTexture;
LTexture gBGTexture;
LTexture gPanelTexture;
LTexture gTextTexture;
LTexture gTextGenerationTexture;
#include "LTexGlobal.h"

int threadFunction( void* data );

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
		gWindow = SDL_CreateWindow( "GenA", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH2, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
				//Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
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

	if( !gPanelTexture.loadFromFile( "panel.png" ) )
	{

		printf( "Failed to load background texture!\n" );
		success = false;
	}

	//Open the font
	gFont = TTF_OpenFont( "lazy.ttf", 24 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 0, 0, 0 };
		if( !gTextTexture.loadFromRenderedText( "kyky", textColor ) )
		{
			printf( "Failed to render text texture!\n" );
			success = false;
		}
		if( !gTextGenerationTexture.loadFromRenderedText( "kyky", textColor ) )
		{
			printf( "Failed to render text texture!\n" );
			success = false;
		}
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
	gPanelTexture.free();

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	 //Free loaded images
	gTextTexture.free();
	gTextGenerationTexture.free();

	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

struct GraficCord
{
	float generation;        // поколение
	float avResFF;    // среднее значение фф у 8 лучших
	GraficCord(float g, float a) : generation(g), avResFF(a)
	{}
};

int threadFunction( void* input )
{
//	std::vector<GraficCord >* cord = (vector<GraficCord>*) input;
//	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
//	SDL_RenderDrawLine(gRenderer,650,200, 840, 200);
//	SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
//	SDL_RenderDrawLine(gRenderer,650,150, 650, 250);
//	for( unsigned i = 0; i < cord.size(); i += 1 )
//	{
//		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
//		if (650+(cord[i].generation*10)>= 840)
//			SDL_RenderDrawPointF(gRenderer,(650+(cord[i].generation*5)),(200)-cord[i].avResFF);
//		else
//			SDL_RenderDrawPointF(gRenderer,(650+(cord[i].generation*10)),(200)-cord[i].avResFF);
//	}
//
	return 0;
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
			//In memory text stream
			std::stringstream helthText;
			std::stringstream generationText;
			//Set text color as black
			SDL_Color textColor = { 0, 0, 0, 255 };

			SDL_Event e;

			VisionEnemySensor *visionEnemySensor = new VisionEnemySensor;
			VisionDotBulletSensor *visionDotBulletSensor = new VisionDotBulletSensor;
			VisionAllySensor *visionAllySensor = new VisionAllySensor;
			VisionAllyBulletSensor *visionAllyBulletSensor = new VisionAllyBulletSensor;
//			CheckTeammatesSensor *checkTeammatesSensor = new CheckTeammatesSensor;
//			Azimuth *azimuthSensor = new Azimuth;
//			WallVerticalSensor *wallVerticalSensor = new WallVerticalSensor;
//			WallGorizontalSensor *wallGorizontalSensor = new WallGorizontalSensor;

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
			std::function<void(unsigned int)> f5;
//			std::vector<int> sec2(2560);// 2^predic* states
			int sec1Length = (enemy[1]->MAX_STATES);
			int sec2Length = (2<<enemy[1]->PREDICATE_COUNT)* (enemy[1]->MAX_STATES);
			std::vector<int> sec1(sec1Length);
			std::vector<int> sec2(sec2Length);
			std::random_device random_device;
			std::mt19937 engine{ random_device() };
			std::uniform_int_distribution<> dist2(0, 9);
			std::uniform_int_distribution<> forX(1, 620);
			std::uniform_int_distribution<> forY(20, 80);

			std::uniform_int_distribution<> forOrder(0, 254);
			std::uniform_int_distribution<> forSplice(0, 7);
			std::uniform_int_distribution<> forSection(0, 1);
			std::uniform_int_distribution<> forBit(0, 3);

			constexpr double Pmut = 0.02;
			std::uniform_real_distribution<double> mut(0.0, 1.0);

			for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
				for (int k = 0; k < sec1Length; ++k)
					sec1[k] =  dist2(random_device);
//				genome[i].add_section({1,2,3,4,5,6,7,8,1,2,3,4,5,6,7,8});
				for (int j = 0; j < sec2Length; ++j)
					sec2[j] =  dist2(random_device);

				genome[i].add_section(sec1);
				genome[i].add_section(sec2);  // 2^predic* states
				enemy[i] = std::make_shared<Enemy>(i, genome[i]);
//				s1 = [&](unsigned id) -> double { return azimuthSensor->checkA((*enemy[id]), dot); };
//				enemy[i] ->add_sensor(s1);
				s2 = [&](unsigned id) -> double { return visionEnemySensor->location((*enemy[id]), dot); };
				enemy[i] ->add_sensor(s2);
				s3 = [&](unsigned id) -> double { return visionDotBulletSensor->location((*enemy[id]), bullet); };
				enemy[i] ->add_sensor(s3);
				s4 = [&](unsigned id) -> double { return visionAllySensor->location(enemy, (*enemy[id])); };
				enemy[i] ->add_sensor(s4);
				s5 = [&](unsigned id) -> double { return visionAllyBulletSensor->location(enemyBullet, (*enemy[id])); };
				enemy[i] ->add_sensor(s5);
//				s4 = [&](unsigned id) -> double { return wallVerticalSensor->location((enemy[id])); };
//				enemy[i] ->add_sensor(s4);
//				s5 = [&](unsigned id) -> double { return wallGorizontalSensor->location((enemy[id])); };
//				enemy[i] ->add_sensor(s5);
				f1 = [&](unsigned id){ enemy[id]->moveStraight(); };
				enemy[i]->add_actor(f1);
				f2 = [&](unsigned id){ enemy[id]->moveLeft(); };
				enemy[i]->add_actor(f2);
				f3 = [&](unsigned id){ enemy[id]->moveRight(); };
				enemy[i]->add_actor(f3);
				f4 = [&](unsigned id){ enemy[id]->moveBack(); };
				enemy[i]->add_actor(f4);
				f5 = [&, i](unsigned id){ enemy[id]->moveShot(enemyBullet[i]); };
				enemy[i]->add_actor(f5);
				enemy[i]->resetTickCount();
			}


//			double an = 0;
//			int ves = 0;
//			int scrollingOffset = 0;
			using clk = std::chrono::high_resolution_clock;
			auto start = clk::now();
			auto stop = start + std::chrono::seconds(TIME_OF_ONE_GENERATION);


			std::vector<std::shared_ptr<Enemy>> favoriteEnemy(8);
			std::vector<std::shared_ptr<Enemy>> sortEnemy(NUMBEROFOPPONENTS);
			std::vector<Genome> sortG(NUMBEROFOPPONENTS);
			std::vector<uint8_t>  order;
			std::vector<int> indices(NUMBEROFOPPONENTS);
			std::vector<bool> enemyOnTheFieldVector(NUMBEROFOPPONENTS);
			double favoriteGen = 0.;
			double enemyOnTheField = 0;
			int numberOfEnemyInOneGroup = 8;
			int counterGroup = 1;
			int counterGroupGenome = 0;
			double SumFF = 0;

			std::vector<GraficCord> cord;
			float avResFF;
			float generation;

			std::ofstream out;
			std::ofstream out2;// поток для записи
			std::ofstream out3;// поток для записи
			std::ofstream out4;// поток для записи
//			for( unsigned i = 0; i < cord.size(); i += 1 )
//			{
//				SDL_RenderDrawPointF(gRenderer,(650+i*3+cord[i].generation),(SCREEN_HEIGHT/2)-cord[i].avResFF);
//			}
			out4.open("D:\\genRes.txt");
			out4<<"";
			out4.close();

			int generationCounter=0;

//			SDL_Thread* threadID = SDL_CreateThread( threadFunction, "LazyThread", (void*)cord );

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


				if (bullet.getMPosY() == 1000){
					bullet.setPosY(dot.getMPosY());
					bullet.setPosX(dot.getMPosX());
					bullet.setVelY(-5);

				}
				bullet.move(dot);

				dot.move();


//				++scrollingOffset;
//				if( scrollingOffset > gBGTexture.getHeight() )
//				{
//					scrollingOffset = 0;
//				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );




				//Render background
				gBGTexture.render( 0, 0 );
				gPanelTexture.render( 640, 0 );

//				gBGTexture.render( 0, scrollingOffset );
//				gBGTexture.render( 0, scrollingOffset - gBGTexture.getHeight() );
				helthText.str("");
				helthText << "health: " << dot.getHealth() ;
				generationText.str("");
				generationText << "generation: " << generationCounter;

				bullet.render();
				dot.render();

				for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
					if (!(enemy[i] ->getDead()) && enemyOnTheField < SIMULTANEOUS_NUMBER_OF_ENEMY_ON_THE_FIELD && !enemy[i]->getEnemyOnTheField()){
							enemy[i] ->setEnemyOnTheField(true);
							enemy[i]->setMPosX(forX(random_device));
							enemy[i]->setMPosY(forY(random_device));
							enemyOnTheField++;
							std::cout<<" существ на поле:  "<<enemyOnTheField<<std::endl;
					}
				}

				for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
					if (enemy[i] ->getEnemyOnTheField()){
						enemy[i] ->tick();
	//						std::cout<<enemy[i]->getTickCount()<<std::endl;
						bullet.hittingTheEnemy(*enemy[i]);
						dot.hittingTheDot(enemyBullet[i], *enemy[i]);
						enemy[i] ->render();
						enemy[i] ->moveBull(enemyBullet[i]);

					}
				}
				//Render text
				if( !gTextTexture.loadFromRenderedText( helthText.str().c_str(), textColor ) )
				{
					printf( "Unable to render time texture!\n" );
				}
				gTextTexture.render( 645, 50 );

				if( !gTextGenerationTexture.loadFromRenderedText( generationText.str().c_str(), textColor ) )
				{
					printf( "Unable to render time texture!\n" );
				}
				gTextGenerationTexture.render( 645, 20 );


				for (int i = 0; i < NUMBEROFENEMYBULLETS; ++i) {
					for (int j = 0; j < NUMBEROFENEMYBULLETS; ++j) {
						if(i != j)
							enemyBullet[i].hittingTheAlly(*enemy[j]);
					}
				}
				for (int i = 0; i < NUMBEROFOPPONENTS; ++i)
					if (!(enemy[i]->getEnemyOnTheField()))
							enemyOnTheField = 0;

				for (int j = 0; j < NUMBEROFOPPONENTS; ++j) {
					if (enemy[j]->getEnemyOnTheField()){
						enemyOnTheField++;
					}
				}


				if (clk::now() >= stop){

					std::cout<<"время прошло"<<std::endl;
					start = clk::now();
					stop = start + std::chrono::seconds(TIME_OF_ONE_GENERATION);
					dot.resetHealth();

					for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
//						std::cout<<" результат функции:  "<<enemy[i]->fitnessFunction()<<"  ";
						sortEnemy[i] = enemy[i];
					}

					for (unsigned i = 0; i < indices.size(); ++i) indices[i] = i;
					std::sort(std::begin(indices), std::end(indices), [&](int a, int b) -> int {
					  return sortEnemy[a]->fitnessFunction() > sortEnemy[b]->fitnessFunction();
					});


					out.open("D:\\hello.txt"); // окрываем файл для записи
					if (out.is_open())
					{
						std::cout<<" запись произошла  "<< std::endl;
						for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
							out <<" существо "<<i<<", у которого количество попаданий по игроку= "<<sortEnemy[indices[i]]->getHittingTheDot()<<", а количество попаданий по союзнику="<<sortEnemy[indices[i]]->getHittingTheAlly()<<", а количество выстрелов= "<<sortEnemy[indices[i]]->getShotCount()<<", а время= "<<sortEnemy[indices[i]]->getTickCount()<< std::endl;
									out <<sortEnemy[indices[i]]->fitnessFunction()<< " ";
								out <<"\n";
						}
					}
					out.close();

					out2.open("D:\\gen.txt"); // окрываем файл для записи
					if (out2.is_open())
					{
						std::cout<<" запись произошла  "<< std::endl;
						for (int n = 0; n < NUMBEROFOPPONENTS; ++n) {
							out2 <<" существо "<<n<<std::endl;
							for (unsigned i = 0; i < 2; ++i) {
								out2 <<" секция : "<<i<<std::endl;
								for (unsigned j = 0; j < genome[indices[0]].section_size(i); ++j) {
									out2 <<" "<<genome[indices[n]].operator ()(i, j)<<", ";
								}

									out2 <<"\n";
							}
						}
					}
					out2.close();
					if (favoriteGen < sortEnemy[indices[0]]->fitnessFunction()){
						favoriteGen = sortEnemy[indices[0]]->fitnessFunction();
						out3.open("D:\\genFavorite.txt"); // окрываем файл для записи
						if (out3.is_open())
						{
							std::cout<<" запись в genFavorite произошла на итерации "<<generationCounter<< std::endl;
							out3 <<"итерация: "<<generationCounter<<"\n существо, у которого количество попаданий по игроку= "<<sortEnemy[indices[0]]->getHittingTheDot()<<", а количество попаданий по союзнику="<<sortEnemy[indices[0]]->getHittingTheAlly()<<", а количество выстрелов= "<<sortEnemy[indices[0]]->getShotCount()<<", а время= "<<sortEnemy[indices[0]]->getTickCount()<< std::endl;
							out3 <<"Резульатат функции = "<<sortEnemy[indices[0]]->fitnessFunction()<< " ";
							out3 <<"\n";
							out3 <<" геном этого существа: "<<std::endl;
							for (unsigned i = 0; i < 2; ++i) {
								out3 <<" секция : "<<i<<std::endl;
								for (unsigned j = 0; j < genome[indices[0]].section_size(i); ++j) {
									out3 <<" "<<genome[indices[0]].operator ()(i, j)<<", ";
								}
								out3 <<"\n";
							}
						}
						out3.close();
					}

					out4.open("D:\\genRes.txt", std::ios::app); // окрываем файл для записи
					if (out4.is_open())
					{
						for (int i = 0; i < numberOfEnemyInOneGroup; ++i) {
							SumFF += sortEnemy[indices[0]]->fitnessFunction();
						}
						SumFF /= numberOfEnemyInOneGroup;
						out4 << generationCounter<<" "<<SumFF<<std::endl;
					}
					out4.close();
					order.resize(genome.size());
					for (unsigned i = 0; i < order.size(); ++i) {
						order[i] = forOrder(random_device);
					}
					for (int q = 0; q < (NUMBEROFOPPONENTS/numberOfEnemyInOneGroup); ++q) {

						for (int i = 1; i <= numberOfEnemyInOneGroup; ++i) {
							if(i == (numberOfEnemyInOneGroup * counterGroup)+1){
								counterGroup++;
								counterGroupGenome = 0;
							}
							genome[indices[i+numberOfEnemyInOneGroup*counterGroup-1 ]]=genome[indices[counterGroupGenome]];
							counterGroupGenome++;
	//						genome[indices[i+numberOfEnemyInOneGroup*2-1]]=genome[indices[i-1]];
	//						genome[indices[i+numberOfEnemyInOneGroup*3-1]]=genome[indices[i-1]];
						}
					}
					counterGroup = 1;
					counterGroupGenome = 0;
					for (int i = 1; i <= numberOfEnemyInOneGroup; ++i) {
						genome[indices[i+numberOfEnemyInOneGroup*counterGroup-1]] =  splice(genome[forSplice(random_device)], genome[forSplice(random_device)], order) ;
						genome[indices[i+numberOfEnemyInOneGroup*(counterGroup+2)-1]] =  splice(genome[forSplice(random_device)], genome[forSplice(random_device)], order);
						for (unsigned s = 0; s < 2; ++s) {
						  for (unsigned w = 0; w < genome[0].section_size(s); ++w) {
						    for (unsigned b = 0; b < 4; ++b) {
						      if (mut(random_device) < Pmut) {
						        genome[indices[i+numberOfEnemyInOneGroup*(counterGroup+1)-1]].mutate(s, w, b);
						      }
						    }
						  }
						}
						for (unsigned s = 0; s < 2; ++s) {
						  for (unsigned w = 0; w < genome[0].section_size(s); ++w) {
							for (unsigned b = 0; b < 4; ++b) {
							  if (mut(random_device) < Pmut) {
								genome[indices[i+numberOfEnemyInOneGroup*(counterGroup+2)-1]].mutate(s, w, b);
							  }
							}
						  }
						}
						if (i == numberOfEnemyInOneGroup * counterGroup)
							counterGroup = 5;
					}
					counterGroup = 1;
					for (int k = 0; k < NUMBEROFOPPONENTS; ++k)
					{
						enemy[k]->setVelY(1);
						enemy[k]->setVelX(1);
						enemy[k]->resetTickCount();
						enemy[k]->resetShotCount();
						enemy[k]->resetHittingTheAlly();
						enemy[k]->resetHittingTheDot();
						enemy[k]->setDead(false);
						enemy[k]->setMPosX(forX(random_device));
						enemy[k]->setMPosY(forY(random_device));
						enemy[k]->setEnemyOnTheField(false);
						enemyBullet[k].setPosX(-200);
						enemyBullet[k].setPosY(-200);

					}

//					std::ifstream in("D:\\genRes.txt"); // окрываем файл для чтения
//					if (in.is_open())
//					{
//						while (in >> generation >> avResFF)
//						{
//							cord.push_back(GraficCord(generation, avResFF));
//						}
//					}
//					in.close();
////					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
//					for( unsigned i = 0; i < cord.size(); i += 1 )
//					{
//						SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
//						SDL_RenderDrawPointF(gRenderer,(660+cord[i].generation),400-cord[i].avResFF);
//						SDL_RenderDrawLine(gRenderer,650,300, SCREEN_WIDTH2, 300);
//					}
//					SDL_RenderDrawLine(gRenderer,650,300, SCREEN_WIDTH2, 300);
					bullet.setPosY(1000);
					enemyOnTheField = 0;
					generationCounter++;

				}

//				std::ifstream in("D:\\genRes.txt"); // окрываем файл для чтения
//				if (in.is_open())
//				{
//					while (in >> generation >> avResFF)
//					{
//						cord.push_back(GraficCord(generation, avResFF));
//					}
//				}
//				in.close();
//				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
//				SDL_RenderDrawLine(gRenderer,650,200, 840, 200);
//				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
//				SDL_RenderDrawLine(gRenderer,650,150, 650, 250);
//				for( unsigned i = 0; i < cord.size(); i += 1 )
//				{
//					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
//					if (650+(cord[i].generation*10)>= 840)
//						SDL_RenderDrawPointF(gRenderer,(650+(cord[i].generation*5)),(200)-cord[i].avResFF);
//					else
//						SDL_RenderDrawPointF(gRenderer,(650+(cord[i].generation*10)),(200)-cord[i].avResFF);
//				}
				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	close();

	return 0;
}
