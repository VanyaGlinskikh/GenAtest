/*
 * global.h
 *
 *  Created on: 20 янв. 2021 г.
 *      Author: vanya
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <random>
#include <vector>
#include <memory>

//Screen dimension constants
const int SCREEN_WIDTH2 = 1020;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int SCREEN_FPS = 60;
const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;

const int TIME_OF_ONE_GENERATION = 10;
const int SIMULTANEOUS_NUMBER_OF_ENEMY_ON_THE_FIELD = 16;
const int NUMBER_OF_ENEMY_IN_ONE_GROUP = 8;
const int NUMBEROFOPPONENTS = 512;
static_assert(NUMBEROFOPPONENTS % 32 == 0, "NUMBEROFOPPONENTS must be % 32 ==0");
const int IDLE_LIMIT = 100;
const int NUMBEROFENEMYBULLETS = NUMBEROFOPPONENTS;

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

//Globally used font
extern TTF_Font *gFont;

class LTexture;
extern LTexture gEnemyBulletTexture;
extern LTexture gDotTexture;
extern LTexture gBulletTexture;
extern LTexture gEnemyTexture;
extern LTexture gBGTexture;
extern LTexture gPanelTexture;
extern LTexture gTextTexture;
extern LTexture gTextGenerationTexture;
extern LTexture gTextModeTexture;
extern std::vector<LTexture> gTextLiveGenomeTexture;
extern LTexture gEnemyOldTexture;

constexpr int PARAMS_COUNT = 7;
extern const double DEFAULT_PARAMS[PARAMS_COUNT];
constexpr double Pmut = 0.02;

struct ConfigData
{
	std::vector<double> param;
	int mode;
	double pmut;
	int time;
};

enum {
	CTRL_MODE_MANUAL = 0,
	CTRL_MODE_1,
	CTRL_MODE_2,
	CTRL_MODE_3,
	CTRL_MODE_4,
	CTRL_MODE_5,
	CTRL_MODE_6,
	CTRL_MODE_7,
	CTRL_MODE_8,
};
constexpr int CTRL_MODE_DEFAULT = CTRL_MODE_6;

void displayResourceError(const char * resource,
		const char * message, const char * additional = nullptr);
void displayError(const char * error, const char * additional = nullptr);
void displayWarning(const char * error, const char * additional = nullptr);


#endif /* GLOBAL_H_ */
