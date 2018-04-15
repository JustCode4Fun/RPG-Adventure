#pragma once

#include "../Engine.h"
#include "vec2.h"

template <class T>
struct vec4 {
	T x, y, z, w;

	vec4() : x(0), y(0), z(0), w(0) {};
	vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {};
	vec4(T scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {};
	vec4(const vec2<T>& vec) : x(vec.x), y(vec.y), z(0), w(1) {};

	std::string toString() const {
		std::stringstream ss;
		ss << "X: " << x << ", Y: " << y<<", Z: " << z << ", W: " << w;
		std::string result;
		result = ss.str();
		return result;
	};

	T& operator[](std::size_t i) const { return T(*(&x+i)); };
	operator std::string const () const { return toString(); };
};

typedef vec4<_float>	vec4f;
typedef vec4<_int>		vec4i;
typedef vec4<_uint>		vec4ui;