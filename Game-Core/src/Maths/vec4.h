#pragma once
template <class T>
struct vec4 {
	T m_x, m_y, m_z, m_w;

	vec4(T x, T y, T z, T w) : m_x(x), m_y(y) {};
	vec4(T scalar) : m_x(scalar), m_y(scalar), m_z(scalar), m_w(scalar) {};
};