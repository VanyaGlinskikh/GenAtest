/*
 * Geometry.h
 *
 *  Created on: 8 июн. 2021 г.
 *      Author: unyuu
 */

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include <cmath>
#include <cassert>

template <typename T>
class Vector2D
{
public:
	T x {}, y {};
	Vector2D() = default;
	Vector2D(const Vector2D<T>& p): x(p.x), y(p.y) {}
	Vector2D(T px, T py): x(px), y(py) {}

	inline T length() const { return T(hypot(x, y)); }

	inline Vector2D<T> &operator +=(const Vector2D<T> &rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	inline Vector2D<T> &operator -=(const Vector2D<T> &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}
};

template <typename T>
inline Vector2D<T> operator +(const Vector2D<T> &lhs, const Vector2D<T> &rhs)
{
	return Vector2D<T>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <typename T>
inline Vector2D<T> operator -(const Vector2D<T> &lhs, const Vector2D<T> &rhs)
{
	return Vector2D<T>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <typename T>
inline Vector2D<T> operator -(const Vector2D<T> &rhs)
{
	return Vector2D<T>(-rhs.x, -rhs.y);
}

template <typename T>
inline T operator *(const Vector2D<T> &lhs, const Vector2D<T> &rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

template <typename T>
class Point2D
{
public:
	T x {}, y {};
	Point2D() = default;
	Point2D(const Point2D<T>& p): x(p.x), y(p.y) {}
	Point2D(T px, T py): x(px), y(py) {}

	inline void set(T nx, T ny) { x = nx; y = ny; }
	inline void translate(T dx, T dy) { x += dx; y += dy; }
	inline void translate(const Vector2D<T>& v) { x += v.x; y += v.y; }
};

template <typename T>
inline Vector2D<T> operator >>(const Point2D<T> &lhs, const Point2D<T> &rhs)
{
	return Vector2D<T>(rhs.x - lhs.x, rhs.y - lhs.y);
}

template <typename T>
inline Vector2D<T> operator <<(const Point2D<T> &lhs, const Point2D<T> &rhs)
{
	return Vector2D<T>(lhs.x - rhs.x, lhs.y - rhs.y);
}

template <typename T>
inline Point2D<T> operator +(const Point2D<T> &lhs, const Vector2D<T> &rhs)
{
	return Point2D<T>(lhs.x + rhs.x, lhs.y + rhs.y);
}

template <typename T>
class Rectangle2D
{
protected:
	Point2D<T> _topleft, _bottomright;
	T _width, _height;
public:
	Rectangle2D() = default;
	Rectangle2D(const Point2D<T>& topleft, const Vector2D<T>& size):
		_topleft(topleft), _bottomright(topleft + size),
		_width(size.x), _height(size.y)
	{
		assert(size.x > 0);
		assert(size.y > 0);
	}

	void translate(const Vector2D<T> &offset)
	{
		_topleft += offset;
		_bottomright += offset;
	}

	inline T width() const { return _width; }
	inline T height() const { return _height; }
	inline Point2D<T> topleft() const { return _topleft; }
	inline Point2D<T> topright() const { return Point2D<T>(_bottomright.x, _topleft.y); }
	inline Point2D<T> bottomleft() const { return Point2D<T>(_topleft.x, _bottomright.y); }
	inline Point2D<T> bottomright() const { return _bottomright; }

	inline T area() const { return width() * height(); }

	inline bool contains(const Point2D<T> &p)
	{
		if (	p.x >= _topleft.x and
				p.x <= _bottomright.x and
				p.y >= _topleft.y and
				p.y <= _bottomright.y )
			return true;

		return false;
	}

	inline bool overlaps(const Rectangle2D<T> &r)
	{
		if (	r.bottomright().y < topleft().y or
				r.topleft().y > bottomright().y or
				r.bottomright().x < topleft().x or
				r.topleft().x > bottomright().x)
			return false; // не пересекаются
		return true; // пересекаются
	}
};

// Краткие псевдонимы для типов
using V2Dd = Vector2D<double>;
using P2Dd = Vector2D<double>;
using V2Di = Vector2D<int>;
using P2Di = Vector2D<int>;

#endif /* GEOMETRY_H_ */
