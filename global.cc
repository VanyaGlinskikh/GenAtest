/*
 * global.cc
 *
 *  Created on: 7 июн. 2021 г.
 *      Author: unyuu
 */

#include <iostream>
#include "global.h"

#include "Texture.h"

SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;
TTF_Font *gFont = NULL;

Texture gEnemyBulletTexture;
Texture gDotTexture;
Texture gBulletTexture;
Texture gEnemyOldTexture;
Texture gEnemyTexture;
Texture gBGTexture;
Texture gPanelTexture;
Texture gTextTexture;
Texture gTextGenerationTexture;
Texture gTextModeTexture;
std::vector<Texture> gTextLiveGenomeTexture(8);


const double DEFAULT_PARAMS[] = { 20, -6, 0.06, 2, 0.01, 0.01, 2 };

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

void displayResourceError(const char *resource, const char *message,
		const char *additional)
{
	std::cerr << "An error has occurred:\n" << resource << ':' <<
			message << std::endl;
	if (additional)
		std::cerr << "Additional info:\n" << additional << std::endl;
}
