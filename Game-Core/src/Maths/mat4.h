#pragma once

#include <iostream>
#include <sstream>
#include "vec2.h"
#include "vec4.h"
#include "../Engine.h"

template <class T>
struct mat4 {


	vec4<T>& operator[](std::size_t i) const { return *(vec4<T>*)(&m_elements[i * 4]); };

	T m_elements[4 * 4];

	mat4(const T* elements) {
		memcpy(m_elements, elements, 4 * 4 * sizeof(T));
	};
	mat4(T diagonal) {
		memset(m_elements, 0, 4 * 4 * sizeof(T));
		m_elements[0 * 4 + 0] = diagonal;
		m_elements[1 * 4 + 1] = diagonal;
		m_elements[2 * 4 + 2] = diagonal;
		m_elements[3 * 4 + 3] = diagonal;
	};
	mat4(const mat4<T>& other) {
		memcpy(m_elements, other.m_elements, sizeof(other.m_elements));
	};
	vec4<T> multiply(const vec4<T>& vec) const {
		vec4<T> result;
		result.x = vec.x * m_elements[0 * 4 + 0] + vec.y * m_elements[1 * 4 + 0] + vec.z * m_elements[2 * 4 + 0] + vec.w* m_elements[3 * 4 + 0];
		result.y = vec.x * m_elements[0 * 4 + 1] + vec.y * m_elements[1 * 4 + 1] + vec.z * m_elements[2 * 4 + 1] + vec.w* m_elements[3 * 4 + 1];
		result.z = vec.x * m_elements[0 * 4 + 2] + vec.y * m_elements[1 * 4 + 2] + vec.z * m_elements[2 * 4 + 2] + vec.w* m_elements[3 * 4 + 2];
		result.w = vec.x * m_elements[0 * 4 + 3] + vec.y * m_elements[1 * 4 + 3] + vec.z * m_elements[2 * 4 + 3] + vec.w* m_elements[3 * 4 + 3];
		return result;
	};

	mat4<T> multiply(const mat4<T>& other) const {
		T elements[16];
		memset(elements, 0x00, sizeof(elements));
		for (_uint yy = 0; yy < 4; yy++) {
			for (_uint xx = 0; xx < 4; xx++) {
				T sum = 0;
				for (_uint i = 0; i < 4; i++) {
					sum += m_elements[i * 4 + yy] * other.m_elements[xx * 4 + i];
				}
				elements[xx * 4 + yy] = sum;
			}
		}
		mat4<T> result(elements);
		return result;
	};

	std::string toString() const {
		std::stringstream ss;
		for (_uint yy = 0; yy < 4; yy++) {
			for (_uint xx = 0; xx < 4; xx++) {
				ss << std::to_string(m_elements[xx * 4 + yy]);
				ss << "\t";
			}
			ss << "\n";
		}
		std::string result;
		result = ss.str();
		return result;
	};

	static mat4<_float> orthographic2D(_float left, _float right, _float top, _float bottom) {
		_float elements[16];
		memset(elements, 0, sizeof(elements));



		_float rminusl = right - left;
		_float rplusl = right + left;

		_float tminusb = top - bottom;
		_float tplusb = top + bottom;

		elements[0 * 4 + 0] = 2.0f / (rminusl);

		elements[1 * 4 + 1] = 2.0f / (tminusb);

		elements[3 * 4 + 0] = -rplusl / rminusl;
		elements[3 * 4 + 1] = -tplusb / tminusb;
		elements[3 * 4 + 3] = 1.0f;

		return mat4<_float>(elements);
	}

	static mat4<_float> translate(const vec2f& translation) {
		mat4<_float> result(1.0f);
		result[3][0] = translation.x;
		result[3][1] = translation.y;
		return result;
	}

	static mat4<_float> scale(vec2f scale) {
		mat4<_float> result(1.0f);
		result[0][0] = scale.x;
		result[1][1] = scale.y;
		return result;
	};
	friend vec4<T> operator*(const mat4<T>& lhs, const vec4<T>& rhs)
	{
		return lhs.multiply(rhs);
	};
	friend mat4<T> operator*(const mat4<T>& lhs, const mat4<T>& rhs)
	{
		return lhs.multiply(rhs);
	};

	mat4<T>& operator*=(const mat4<T>& mat) {
		*this = this->multiply(mat);
		return *this;
	};

	operator std::string const() const { return toString(); }

};


typedef mat4<_float>	mat4f;
typedef mat4<_int>		mat4i;
typedef mat4<_uint>		mat4ui;