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

	inline auto &position() const { return mRect.topleft(); }
	inline void setPosition(const Point2D<int> &pos) { mRect.setTopLeft(pos); }
	inline void setPosition(int nx, int ny) { mRect.setTopLeft(nx, ny); }
	inline void translate(int dx, int dy) { mRect.translate(dx, dy); }

	inline void setDimensions(const Vector2D<int> &dims) { mRect.setSize(dims); }
	inline void setDimensions(int w, int h) { mRect.setSize(w, h); }
	inline int width() const { return mRect.width(); }
	inline int height() const { return mRect.height(); }
	inline auto &rect() const { return mRect; }

	virtual void render()
	{
		if (mTexture)
			mTexture->render(position().x, position().y);
	}

protected:
	void setTexture(LTexture * tex) { mTexture = tex; }

private:
	LTexture * mTexture { nullptr };
	Rectangle2D<int> mRect;
};

#endif /* SPRITE_H_ */
