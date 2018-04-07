#pragma once

#include <iostream>
#include "../Engine.h"

template <class T>
struct mat4 {
	T m_elements[4 * 4];
	mat4(const T* elements) { 
		memcpy(m_elements, elements, 4 * 4 * sizeof(T));
	};
	mat4(T diagonal) {
		memset(m_elements, 0, 4 * 4 * sizeof(T));
		m_elements[0 * 4 + 0] = diagonal;
		m_elements[1 * 4 + 1] = diagonal;
		m_elements[2 * 4 + 2] = diagonal;
	};
	
	static mat4<_float> orthographic2D(_float left, _float right, _float top, _float bottom) {
		_float elements[16];
		memset(elements, 0, sizeof(elements));



		_float rminusl = right - left;
		_float rplusl = right + left;

		_float tminusb = top - bottom;
		_float tplusb = top + bottom;

		elements[0 * 4 + 0] = 2 / (rminusl);

		elements[1 * 4 + 1] = 2 / (tminusb);

		elements[3 * 4 + 0] = -rplusl / rminusl;
		elements[3 * 4 + 1] = -tplusb / tminusb;
		elements[3 * 4 + 3] = 1;

		return mat4<_float>(elements);
	}
};