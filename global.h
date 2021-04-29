/*
 * global.h
 *
 *  Created on: 20 џэт. 2021 у.
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
//Screen dimension constants
const int SCREEN_WIDTH2 = 840;
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int NUMBEROFOPPONENTS = 64;

const int NUMBEROFENEMYBULLETS = NUMBEROFOPPONENTS;

//The window we'll be rendering to
extern SDL_Window* gWindow;

//The window renderer
extern SDL_Renderer* gRenderer;

//Globally used font
extern TTF_Font *gFont;





#endif /* GLOBAL_H_ */
