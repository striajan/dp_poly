#ifndef VEC2_HPP_
#define VEC2_HPP_

#include <ostream>

template <typename T>
struct vec2
{
	T x;
	T y;

	vec2(const T& x_ = T(), const T& y_ = T())
		: x(x_), y(y_)
	{ }

	vec2(const vec2& v)
		: x(v.x), y(v.y)
	{ }

	T norm2() const
	{
		return x * x + y * y;
	}

	vec2 operator-() const
	{
		return vec2(-x, -y);
	}

	static T dot(const vec2& u, const vec2& v)
	{
		return u.x * v.x + u.y * v.y;
	}
};

template <typename S, typename T>
vec2<T> operator*(const S& a, const vec2<T>& v)
{
	return vec2<T>(a * v.x, a * v.y);
}

template <typename S, typename T>
vec2<T> operator*(const vec2<T>& v, const S& a)
{
	return a * v;
}

template <typename S, typename T>
vec2<T> operator/(const vec2<T>& v, const S& a)
{
	return vec2<T>(v.x / a, v.y / a);
}

template <typename T>
vec2<T> operator+(const vec2<T>& u, const vec2<T>& v)
{
	return vec2<T>(u.x + v.x, u.y + v.y);
}

template <typename T>
vec2<T> operator-(const vec2<T>& u, const vec2<T>& v)
{
	return vec2<T>(u.x - v.x, u.y - v.y);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const vec2<T>& v)
{
	os << "[" << v.x << "," << v.y << "]";
	return os;
}

#endif
