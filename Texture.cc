/*
 * LTexture.cc
 *
 *  Created on: 23 янв. 2021 г.
 *      Author: vanya
 */
#include "Texture.h"
Texture::Texture()
{
	mTexture = NULL;
}

Texture::~Texture()
{
	free();
}

bool Texture::loadFromFile(const std::string &path )
{
	// Если уже есть текстура - освобождаем
	free();

	SDL_Texture* newTexture = NULL;

	// Загрузка
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ) {
		displayResourceError(path.c_str(), "Unable to load image!", SDL_GetError());
		return false;
	}

	// Задание "прозрачного" цвета
	SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

	// Создание текстуры
	newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
	if( newTexture == NULL ) {
		displayResourceError(path.c_str(), "Unable to create texture!", SDL_GetError());
		return false;
	}

	mSize.set(loadedSurface->w, loadedSurface->h);

	// Освобождение загруженного изображения
	SDL_FreeSurface( loadedSurface );

	mTexture = newTexture;
	return mTexture != NULL;
}


void Texture::free()
{
	// Освобождаем текстуру, если она есть
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mSize.set(0, 0);
	}
}

void Texture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	// Куда будет рисоваться текстура
	SDL_Rect renderQuad = { x, y, width(), height() };

	// Обрезка, если требуется
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	// Рисование
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

bool Texture::loadFromRenderedText(const std::string &textureText, SDL_Color textColor )
{
    free();

    // Создаём изображение надписи
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
    	displayError( "Unable to render text surface!", TTF_GetError() );
    	goto finish;
    }

	// Создаём текстуру из изображения
	mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
	if( mTexture == NULL )
	{
		displayError("Unable to create texture from rendered text!", SDL_GetError());
		goto finish;
	}

	// Получаем размеры
	mSize.set(textSurface->w, textSurface->h);

finish:
	// Удаляем изображение за ненадобностью
	SDL_FreeSurface( textSurface );

    return mTexture != NULL;
}
