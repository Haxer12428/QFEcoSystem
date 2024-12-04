#pragma once
#include <glm/glm.hpp>
#include <fmt/core.h>
#include <ostream>
#include <string>
#include <iostream>
#include <string>
#define NOMINMAX

/* 
	This is based on glm's vec2 implementation for performance 
*/

class qfVec2 {
public:
	qfVec2();
	qfVec2(float _both);
	qfVec2(float _x, float _y);
	qfVec2(const glm::vec2& _Vec);

	inline operator glm::vec2() const;

	qfVec2 operator+(const qfVec2& _Other) const; 
	qfVec2 operator-(const qfVec2& _Other) const;
	qfVec2 operator*(const qfVec2& _Other) const;
	qfVec2 operator/(const qfVec2& _Other) const;

	inline float _x() const; 
	inline float _y() const; 

	inline const bool isInBoundingBox2d(const qfVec2& _First, const qfVec2& _Last) const; 
	const std::string gString() const; 

	friend std::ostream& operator<<(std::ostream& _Os, const qfVec2& _Vec) {
		_Os << _Vec.gString(); return _Os;
	}

	/* This should not be used by user */
	glm::vec2 m_Data; 

};
