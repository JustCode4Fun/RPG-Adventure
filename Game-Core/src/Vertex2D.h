#pragma once
#include "Maths\vec2.h"
#include "Maths\vec4.h"

struct Vertex2D {
	vec2f position;
	vec2f uv;
	vec4f color;
	_float m_tid;
};