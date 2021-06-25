#ifndef TEXTURE_H_
#define TEXTURE_H_
#include "global.h"
#include "Geometry.h"

class Texture
{
public:
	Texture();
	~Texture();

	// Загрузка изображения из указанного файла
	bool loadFromFile(const std::string &path );

	// Создание изображения из строки
	bool loadFromRenderedText(const std::string	&textureText, SDL_Color textColor );

	// Освобождение памяти
	void free();

	// Рисование текстуры в указанных координатах
	void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

	// Получение размеров изображения
	const Vector2D<int> &size() const { return mSize; }
	int width() const { return mSize.u; }
	int height() const { return mSize.v; }

private:
	// Указатель на текстуру
	SDL_Texture* mTexture;

	// Размеры изображения
	Vector2D<int> mSize;
};

#endif
