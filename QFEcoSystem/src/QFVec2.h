#pragma once
#include <imgui.h>
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
	
	operator glm::vec2() const;
	operator ImVec2() const { return ImVec2{ _x(), _y() }; };

	qfVec2 operator+(const qfVec2& _Other) const; 
	qfVec2 operator-(const qfVec2& _Other) const;
	qfVec2 operator*(const qfVec2& _Other) const;
	qfVec2 operator/(const qfVec2& _Other) const;

	float _x() const; 
	float _y() const; 

	const bool isIntersecting(const qfVec2& _First, const qfVec2& _Last) const; 
	const std::string getString() const; 

	friend std::ostream& operator<<(std::ostream& _Os, const qfVec2& _Vec) {
		_Os << _Vec.getString(); return _Os;
	}

	/* This should not be used by user */
	glm::vec2 m_Data; 

};
