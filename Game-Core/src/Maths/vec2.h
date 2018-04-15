#pragma once
#include "../Engine.h"
template <class T>
struct vec4;
template <class T>
struct vec2 {
	T x, y;

	vec2(T x, T y) : x(x), y(y){};
	vec2(T scalar) : x(scalar), y(scalar) {};
	vec2(const vec4<T>& vec) :x(vec.x), y(vec.y) {};

	std::string toString() const {
		std::stringstream ss;
		ss << "X: " << x << ", Y: " << y;
		std::string result;
		result = ss.str();
		return result;
	};

	operator std::string const() const { return toString(); }

};

typedef vec2<_float> vec2f;
typedef vec2<_int> vec2i;
typedef vec2<_uint> vec2ui;
