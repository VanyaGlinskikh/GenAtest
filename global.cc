/*
 * global.cc
 *
 *  Created on: 7 июн. 2021 г.
 *      Author: unyuu
 */

#include <iostream>
#include "global.h"

SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;
TTF_Font *gFont = NULL;

void displayError(const char *message, const char *additional)
{
	std::cerr << "An error has occurred:\n" << message << std::endl;
	if (additional)
		std::cerr << "Additional info:\n" << additional << std::endl;
}

void displayWarning(const char *message, const char *additional) {
	std::cerr << "Warning: " << message << std::endl;
	if (additional)
		std::cerr << "Additional info:\n" << additional << std::endl;
}
