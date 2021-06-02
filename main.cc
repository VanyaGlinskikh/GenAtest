#include "global.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "LTexture.h"
#include "Dot.h"
#include "Bullet.h"

#include "Sensor.h"
#include "VisionEnemySensor.h"
#include "VisionDotBulletSensor.h"
#include "VisionAllySensor.h"
#include "VisionAllyBulletSensor.h"

#include <fstream>

#include <functional>
#include <chrono>
#include "LTexGlobal.h"

SDL_Window* gWindow = NULL;
TTF_Font *gFont = NULL;

LTexture gEnemyBulletTexture;
LTexture gBulletTexture;
LTexture gEnemyTexture;
LTexture gBGTexture;
LTexture gPanelTexture;
LTexture gTextTexture;
LTexture gTextGenerationTexture;


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
//			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
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

//struct GraficCord
//{
//	float generation;        // поколение
//	float avResFF;    // среднее значение фф у 8 лучших
//	GraficCord(float g, float a) : generation(g), avResFF(a)
//	{}
//};

void writeOut(std::ofstream &out, std::vector<std::shared_ptr<Enemy>> sortEnemy, std::vector<int> &indices){
	out.open("D:\\stat.txt"); // окрываем файл для записи
	if (out.is_open())
	{
		std::cout<<" запись произошла  "<< std::endl;
		for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
			out <<" существо "<<i<<", у которого количество попаданий по игроку= "<<sortEnemy[indices[i]]->getHittingTheDot()<<", а количество попаданий по союзнику="<<sortEnemy[indices[i]]->getHittingTheAlly()<<", а количество выстрелов= "<<sortEnemy[indices[i]]->getShotCount()<<", а количество движений  "<<sortEnemy[indices[i]]->getNumberOfMovements()<<", а время= "<<sortEnemy[indices[i]]->getTickCount()<<", а количество движений вниз="<<sortEnemy[indices[i]]->getNumberOfDown()<<", а количество пропущенных шагов "<<sortEnemy[indices[i]]->getStandMovements()<< std::endl;
					out <<sortEnemy[indices[i]]->fitnessFunction()<< " ";
				out <<"\n";
		}
	}
	out.close();
}

void writeOut2(std::ofstream &out2, std::vector<Genome> &genome, std::vector<int> &indices){
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
}

void writeOut3(std::ofstream &out3, std::vector<std::shared_ptr<Enemy>> sortEnemy, std::vector<Genome> &genome, std::vector<int> &indices, int &generationCounter, double &favoriteGen){
	if (favoriteGen < sortEnemy[indices[0]]->fitnessFunction()){
		favoriteGen = sortEnemy[indices[0]]->fitnessFunction();
		out3.open("D:\\genFavorite.txt"); // окрываем файл для записи
		if (out3.is_open())
		{
			std::cout<<" запись в genFavorite произошла на итерации "<<generationCounter<< std::endl;
			out3 <<"итерация: "<<generationCounter<<"\n существо, у которого количество попаданий по игроку= "<<sortEnemy[indices[0]]->getHittingTheDot()<<", а количество попаданий по союзнику="<<sortEnemy[indices[0]]->getHittingTheAlly()<<", а количество выстрелов= "<<sortEnemy[indices[0]]->getShotCount()<<", а количество движений  "<<sortEnemy[indices[0]]->getNumberOfMovements()<<", а время= "<<sortEnemy[indices[0]]->getTickCount()<< std::endl;
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
}

void writeOut4(std::ofstream &out4, std::vector<std::shared_ptr<Enemy>> sortEnemy, std::vector<int> &indices, int &generationCounter,double &SumFF){
	out4.open("D:\\genRes.csv", std::ios::app); // окрываем файл для записи
						if (out4.is_open())
						{
							out4.imbue(std::locale(""));
							for (int i = 0; i < NUMBER_OF_ENEMY_IN_ONE_GROUP; ++i) {
								SumFF += sortEnemy[indices[i]]->fitnessFunction();
							}
	//						SumFF /= numberOfEnemyInOneGroup;
							out4 << generationCounter<<";"<<SumFF/NUMBER_OF_ENEMY_IN_ONE_GROUP<<";"<<sortEnemy[indices[0]]->fitnessFunction()<<";"<<sortEnemy[indices[7]]->fitnessFunction()<<std::endl;
						}
						out4.close();
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

			std::stringstream helthText;
			std::stringstream generationText;

			SDL_Color textColor = { 0, 0, 0, 255 };

			SDL_Event e;

			VisionEnemySensor *visionEnemySensor = new VisionEnemySensor;
			VisionDotBulletSensor *visionDotBulletSensor = new VisionDotBulletSensor;
			VisionAllySensor *visionAllySensor = new VisionAllySensor;
			VisionAllyBulletSensor *visionAllyBulletSensor = new VisionAllyBulletSensor;

			Dot dot;
			Bullet bullet;
			std::vector<EnemyBullet> enemyBullet(NUMBEROFOPPONENTS);
			std::vector<Genome> genome(NUMBEROFOPPONENTS);
			std::vector<std::shared_ptr<Enemy>> enemy(NUMBEROFOPPONENTS);

			std::function<double(unsigned int)> s1;
			std::function<double(unsigned int)> s2;
			std::function<double(unsigned int)> s3;
			std::function<double(unsigned int)> s4;

			std::function<void(unsigned int)> f1;
			std::function<void(unsigned int)> f2;
			std::function<void(unsigned int)> f3;
			std::function<void(unsigned int)> f4;
			std::function<void(unsigned int)> f5;

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

			constexpr double Pmut = 0.02;
			std::uniform_real_distribution<double> mut(0.0, 1.0);

			for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
				for (int k = 0; k < sec1Length; ++k)
					sec1[k] =  dist2(random_device);
				for (int j = 0; j < sec2Length; ++j)
					sec2[j] =  dist2(random_device);

				genome[i].add_section(sec1);
				genome[i].add_section(sec2);  // 2^predic* states
				enemy[i] = std::make_shared<Enemy>(i, genome[i]);
				s1 = [&](unsigned id) -> double { return visionEnemySensor->location((*enemy[id]), dot); };
				enemy[i] ->add_sensor(s1);
				s2 = [&](unsigned id) -> double { return visionDotBulletSensor->location((*enemy[id]), bullet); };
				enemy[i] ->add_sensor(s2);
				s3 = [&](unsigned id) -> double { return visionAllySensor->location(enemy, (*enemy[id])); };
				enemy[i] ->add_sensor(s3);
				s4 = [&](unsigned id) -> double { return visionAllyBulletSensor->location(enemyBullet, (*enemy[id])); };
				enemy[i] ->add_sensor(s4);

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
			using clk = std::chrono::high_resolution_clock;
			auto start = clk::now();
			auto stop = start + std::chrono::seconds(TIME_OF_ONE_GENERATION);

			std::vector<std::shared_ptr<Enemy>> favoriteEnemy(8);
			std::vector<std::shared_ptr<Enemy>> sortEnemy(NUMBEROFOPPONENTS);
			std::vector<Genome> sortG(NUMBEROFOPPONENTS);
			std::vector<uint8_t>  order;
			std::vector<int> indices(NUMBEROFOPPONENTS);
			std::vector<int> enemyIdOnTheField;
			std::vector<bool> enemyOnTheFieldVector(NUMBEROFOPPONENTS);

			double favoriteGen = 0.;
			double enemyOnTheField = 0;
			//int numberOfEnemyInOneGroup = 8;
			int counterGroup = 1;
			int counterGroupGenome = 0;
			double SumFF = 0;

//			std::vector<GraficCord> cord;

			std::ofstream out;
			std::ofstream out2;// поток для записи
			std::ofstream out3;// поток для записи
			std::ofstream out4;// поток для записи

			out4.open("D:\\genRes.txt");
			out4<<"";
			out4.close();

			int generationCounter=0;

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
				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				//Render background
				gBGTexture.render( 0, 0 );
				gPanelTexture.render( 640, 0 );

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
							enemyIdOnTheField.push_back(enemy[i]->getId());
//							std::cout<<" существ на поле:  "<<enemyOnTheField<<std::endl;
					}
				}

				for (int i = 0; i < SIMULTANEOUS_NUMBER_OF_ENEMY_ON_THE_FIELD; ++i) {
					enemy[enemyIdOnTheField[i]] ->tick();
					bullet.hittingTheEnemy(*enemy[enemyIdOnTheField[i]]);
					dot.hittingTheDot(enemyBullet[enemyIdOnTheField[i]], *enemy[enemyIdOnTheField[i]]);
					enemy[enemyIdOnTheField[i]] ->render();
					enemy[enemyIdOnTheField[i]] ->moveBull(enemyBullet[enemyIdOnTheField[i]]);
					enemyBullet[enemyIdOnTheField[i]].hittingTheBullet(bullet);
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

				for (int i = 0; i < SIMULTANEOUS_NUMBER_OF_ENEMY_ON_THE_FIELD; ++i) {
					for (int j = 0; j < SIMULTANEOUS_NUMBER_OF_ENEMY_ON_THE_FIELD; ++j) {
						if(i != j)
							enemyBullet[enemyIdOnTheField[i]].hittingTheAlly(*enemy[enemyIdOnTheField[j]]);
					}
				}
				enemyOnTheField = 0;
				enemyIdOnTheField.clear();
				for (int j = 0; j < NUMBEROFOPPONENTS; ++j) {
					if (enemy[j]->getEnemyOnTheField()){
						enemyOnTheField++;
						enemyIdOnTheField.push_back(enemy[j]->getId());
					}
				}

				if (clk::now() >= stop){

					for (int i = 0; i < NUMBEROFOPPONENTS; ++i) {
//						std::cout<<" результат функции:  "<<enemy[i]->fitnessFunction()<<"  ";
						sortEnemy[i] = enemy[i];
					}

					for (unsigned i = 0; i < indices.size(); ++i) indices[i] = i;
					std::sort(std::begin(indices), std::end(indices), [&](int a, int b) -> int {
					  return sortEnemy[a]->fitnessFunction() > sortEnemy[b]->fitnessFunction();
					});
					writeOut(out,sortEnemy, indices);
					writeOut2(out2, genome, indices);
					writeOut3(out3, sortEnemy, genome, indices, generationCounter, favoriteGen);
					writeOut4(out4, sortEnemy, indices, generationCounter, SumFF);

					order.resize(genome.size());
					for (unsigned i = 0; i < order.size(); ++i) {
						order[i] = forOrder(random_device);
					}
					for (int q = 0; q < (NUMBEROFOPPONENTS/NUMBER_OF_ENEMY_IN_ONE_GROUP); ++q) {

						for (int i = 1; i <= NUMBER_OF_ENEMY_IN_ONE_GROUP; ++i) {
							if(i == (NUMBER_OF_ENEMY_IN_ONE_GROUP * counterGroup)+1){
								counterGroup++;
								counterGroupGenome = 0;
							}
							genome[indices[i+NUMBER_OF_ENEMY_IN_ONE_GROUP*counterGroup-1 ]]=genome[indices[counterGroupGenome]];
							counterGroupGenome++;
						}
					}
					counterGroup = 1;
					counterGroupGenome = 0;
					for (int i = 1; i <= NUMBER_OF_ENEMY_IN_ONE_GROUP; ++i) {
						genome[indices[i+NUMBER_OF_ENEMY_IN_ONE_GROUP*counterGroup-1]] =  splice(genome[forSplice(random_device)], genome[forSplice(random_device)], order) ;
						genome[indices[i+NUMBER_OF_ENEMY_IN_ONE_GROUP*(counterGroup+2)-1]] =  splice(genome[forSplice(random_device)], genome[forSplice(random_device)], order);
						for (unsigned s = 0; s < 2; ++s) {
						  for (unsigned w = 0; w < genome[0].section_size(s); ++w) {
						    for (unsigned b = 0; b < 4; ++b) {
						      if (mut(random_device) < Pmut) {
						        genome[indices[i+NUMBER_OF_ENEMY_IN_ONE_GROUP*(counterGroup+1)-1]].mutate(s, w, b);
						      }
						    }
						  }
						}
						for (unsigned s = 0; s < 2; ++s) {
						  for (unsigned w = 0; w < genome[0].section_size(s); ++w) {
							for (unsigned b = 0; b < 4; ++b) {
							  if (mut(random_device) < Pmut) {
								genome[indices[i+NUMBER_OF_ENEMY_IN_ONE_GROUP*(counterGroup+2)-1]].mutate(s, w, b);
							  }
							}
						  }
						}
						if (i == NUMBER_OF_ENEMY_IN_ONE_GROUP * counterGroup)
							counterGroup = 5;
					}
					counterGroup = 1;
					for (int k = 0; k < NUMBEROFOPPONENTS; ++k)
					{
						enemy[k]->setVelY(1);
						enemy[k]->setVelX(1);
						enemy[k]->resetTickCount();
						enemy[k]->resetShotCount();
						enemy[k]->resetNumberOfMovements();
						enemy[k]->resetTotalNumberOfMovements();
						enemy[k]->resetStandMovements();
						enemy[k]->resetNumberOfDown();
						enemy[k]->resetHittingTheAlly();
						enemy[k]->resetHittingTheDot();
						enemy[k]->setDead(false);
						enemy[k]->setMPosX(forX(random_device));
						enemy[k]->setMPosY(forY(random_device));
						enemy[k]->setEnemyOnTheField(false);
						enemyBullet[k].setPosX(-200);
						enemyBullet[k].setPosY(-200);

					}

					bullet.setPosY(1000);
					enemyOnTheField = 0;
					generationCounter++;
					SumFF = 0;
					dot.resetHealth();


					std::cout<<"время прошло"<<std::endl;
					start = clk::now();
					stop = start + std::chrono::seconds(TIME_OF_ONE_GENERATION);
				}

				SDL_RenderPresent( gRenderer );
			}
		}
	}

	close();

	return 0;
}
