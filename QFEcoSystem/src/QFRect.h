#pragma once
#include "QFDefines.h"
#include <glm/glm.hpp>
#include "QFVec2.h"

typedef glm::vec<4, float, glm::defaultp> _qfRectInternalDataType;

class qfRect {
public: 
	qfRect();
	qfRect(float _x, float _y, float _sx, float _sy);
	qfRect(const qfVec2& _p1, const qfVec2& _size);

	virtual ~qfRect();

	qfVec2 getPosition() const; 
	qfVec2 getSize() const; 
	qfVec2 getFinalPosition() const; 

	inline operator _qfRectInternalDataType() const;
private:
	_qfRectInternalDataType m_Data; 
};