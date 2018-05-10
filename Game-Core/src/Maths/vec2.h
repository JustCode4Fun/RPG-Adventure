#pragma once
#include "../Engine.h"
template <class T>
struct vec4;
template <class T>
struct vec2 {
	T x, y;
	vec2() : x(0), y(0) {};
	vec2(T x, T y) : x(x), y(y){};
	vec2(T scalar) : x(scalar), y(scalar) {};
	vec2(const vec4<T>& vec) :x(vec.x), y(vec.y) {};

	vec2<T>& add(const vec2<T>& right) {
		x += right.x;
		y += right.y;
		return *this;
	}
	static vec2<T> Add(const vec2<T>& left, const vec2<T>& right) {
		vec2<T> result = left;
		result.add(right);
		return result;
	}

	vec2<T>& add(const T& right) {
		x += right;
		y += right;
		return *this;
	}
	static vec2<T> Add(const vec2<T>& left, const T& right) {
		vec2<T> result = left;
		result.add(right);
		return result;
	}

	vec2<T>& multiply(const vec2<T>& right) {
		x *= right.x;
		y *= right.y;
		return *this;
	}
	static vec2<T> Multiply(const vec2<T>& left, const vec2<T>& right) {
		vec2<T> result = left;
		result.multiply(right);
		return result;
	}

	vec2<T>& multiply(const T& right) {
		x *= right;
		y *= right;
		return *this;
	}
	static vec2<T> Multiply(const vec2<T>& left, const T& right) {
		vec2<T> result = left;
		result.multiply(right);
		return result;
	}

	std::string toString() const {
		std::stringstream ss;
		ss << "X: " << x << ", Y: " << y;
		std::string result;
		result = ss.str();
		return result;
	};

	vec2<T> operator+(const T& right) {
		return Add(*this, right);
	}
	vec2<T> operator+(const vec2<T>& right) {
		return Add(*this, right);
	}

	vec2<T> operator*(const T& right) { 
		return Multiply(*this, right);
	}
	vec2<T> operator*(const vec2<T>& right) {
		return Multiply(*this, right);
	}

	vec2<T>& operator+=(const vec2<T>& right) {
		return this->add(right);
	};
	vec2<T>& operator+=(const T& right) {
		return this->add(right);
	};

	vec2<T>& operator*=(const vec2<T>& right) {
		return this->multiply(right);
	};
	vec2<T>& operator*=(const T& right) {
		return this->multiply(right);
	};

	operator std::string const() const { return toString(); }
	vec2<T> operator-() { return vec2<T>(-x, -y); };
};

typedef vec2<_float> vec2f;
typedef vec2<_int> vec2i;
typedef vec2<_uint> vec2ui;
