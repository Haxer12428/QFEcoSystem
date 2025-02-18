#pragma once
#include "QFDefines.h"
#include <glm/glm.hpp>
#include "QFVec2.h"
#include "QFString.h"
#include <fmt/core.h>
#include <ostream>
#include "imgui.h"
#include <Windows.h>
#define NOMINMAX

typedef glm::vec<4, float, glm::defaultp> _qfRectInternalDataType;

class qfRect {
public: 
	qfRect();
	qfRect(float _x, float _y, float _sx, float _sy);
	qfRect(const qfVec2& _p1, const qfVec2& _size);
	qfRect(const RECT& _WinRect);

	virtual ~qfRect();

	qfVec2 getPosition() const; 
	qfVec2 getSize() const; 
	qfVec2 getFinalPosition() const; 

	const qfString getString() const;
	
	void shiftAndShrink(float _By);
	void shiftAndShrinkByScale(float _By);
	void scaleSize(float _Scale);

	float& _x(); 
	float& _y(); 
	float& _sx();
	float& _sy();

	void setPosition(const qfVec2& _New);
	void setSize(const qfVec2& _New);

	friend std::ostream& operator<<(std::ostream& _Os, const qfRect& _Rectangle) {
		_Os << _Rectangle.getString(); return _Os;
	}
	

	const bool isIntersecting(const qfRect& _Other); 

	operator _qfRectInternalDataType() const;
private:
	_qfRectInternalDataType m_Data; 
};