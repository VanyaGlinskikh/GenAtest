/*
 * Sprite.h
 *
 *  Created on: 10 июн. 2021 г.
 *      Author: unyuu
 */

#ifndef SPRITE_H_
#define SPRITE_H_

#include "LTexture.h"
#include "Geometry.h"

class Sprite {
public:
	Sprite();
	virtual ~Sprite();

	inline auto &position() const { return mPosition; }
	inline void setPosition(const Point2D<int> &pos) { mPosition = pos; }
	inline void setPosition(int nx, int ny) { mPosition.set(nx, ny); }
	inline void translate(int dx, int dy) { mPosition.translate(dx, dy); }

	virtual void render()
	{
		if (mTexture)
			mTexture->render(position().x, position().y);
	}

protected:
	void setTexture(LTexture * tex) { mTexture = tex; }

private:
	LTexture * mTexture { nullptr };
	Point2D<int> mPosition;
};

#endif /* SPRITE_H_ */
