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
	T u {}, v {};
	Vector2D() = default;
	Vector2D(const Vector2D<T>& p): u(p.u), v(p.v) {}
	Vector2D(T px, T py): u(px), v(py) {}

	inline void set(T nu, T nv) { u = nu; v = nv; }

	inline T length() const { return T(hypot(u, v)); }

	inline Vector2D<T> &operator +=(const Vector2D<T> &rhs)
	{
		u += rhs.u;
		v += rhs.v;
		return *this;
	}

	inline Vector2D<T> &operator -=(const Vector2D<T> &rhs)
	{
		u -= rhs.u;
		v -= rhs.v;
		return *this;
	}
};

template <typename T>
inline Vector2D<T> operator +(const Vector2D<T> &lhs, const Vector2D<T> &rhs)
{
	return Vector2D<T>(lhs.u + rhs.u, lhs.v + rhs.v);
}

template <typename T>
inline Vector2D<T> operator -(const Vector2D<T> &lhs, const Vector2D<T> &rhs)
{
	return Vector2D<T>(lhs.u - rhs.u, lhs.v - rhs.v);
}

template <typename T>
inline Vector2D<T> operator -(const Vector2D<T> &rhs)
{
	return Vector2D<T>(-rhs.u, -rhs.v);
}

template <typename T>
inline T operator *(const Vector2D<T> &lhs, const Vector2D<T> &rhs)
{
	return lhs.u * rhs.u + lhs.v * rhs.v;
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
	inline void translate(const Vector2D<T>& v) { x += v.u; y += v.v; }
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
	return Point2D<T>(lhs.x + rhs.u, lhs.y + rhs.v);
}

template <typename T>
class Rectangle2D
{
protected:
	Point2D<T> _topleft;
	Point2D<T> _bottomright;
	Vector2D<T> _size;

public:
	Rectangle2D() = default;
	Rectangle2D(const Point2D<T>& topleft, const Vector2D<T>& size):
		_topleft(topleft), _bottomright(topleft + size), _size(size)
	{
		assert(size.u > 0);
		assert(size.v > 0);
	}

	void setTopLeft(T x, T y)
	{
		_topleft.set(x, y);
		_bottomright = _topleft + _size;
	}

	void setTopLeft(const Point2D<T> p)
	{
		_topleft = p;
		_bottomright = _topleft + _size;
	}

	void setSize(int w, int h)
	{
		_size.set(w, h);
		_bottomright = _topleft + _size;
	}

	void setSize(const Vector2D<T> s)
	{
		_size = s;
		_bottomright = _topleft + _size;
	}

	void translate(T dx, T dy)
	{
		Vector2D<T> offset { dx, dy };
		translate(offset);
	}

	void translate(const Vector2D<T> &offset)
	{
		_topleft.translate(offset);
		_bottomright.translate(offset);
	}

	inline T width() const { return _size.u; }
	inline T height() const { return _size.v; }
	inline const Point2D<T> &topleft() const { return _topleft; }
	inline const Point2D<T> &bottomright() const { return _bottomright; }

	inline T area() const { return width() * height(); }

	inline bool contains(const Point2D<T> &p) const
	{
		if (	p.x >= _topleft.x and
				p.x <= _bottomright.x and
				p.y >= _topleft.y and
				p.y <= _bottomright.y )
			return true;

		return false;
	}

	inline bool overlaps(const Rectangle2D<T> &r) const
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
