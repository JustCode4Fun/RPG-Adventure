#pragma once
template <class T>
struct vec2 {
	T m_x, m_y;

	vec2(T x, T y) : m_x(x), m_y(y){};
	vec2(T scalar) : m_x(scalar), m_y(scalar) {};
};