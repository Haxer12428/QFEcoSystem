#include "QFRect.h"

/* Constructors */
qfRect::qfRect() 
	: m_Data{ _qfRectInternalDataType(0.0f, 0.0f, 0.0f, 0.0f) } {};

qfRect::qfRect(float _x, float _y, float _sx, float _sy) : 
	m_Data{ _qfRectInternalDataType(_x, _y, _sx, _sy) } {};

qfRect::qfRect(const qfVec2& _p1, const qfVec2& _size)
	: m_Data{ _qfRectInternalDataType(_p1._x(), _p1._y(), _size._x(), _size._y()) } {};

/* Destructor */
qfRect::~qfRect() = default; 

/* Public -> Get's */
qfVec2 qfRect::getPosition() const { return qfVec2{ m_Data.x, m_Data.y }; }
qfVec2 qfRect::getSize() const { return qfVec2{ m_Data.z, m_Data.w }; }
qfVec2 qfRect::getFinalPosition() const { return (getPosition() + getSize()); }

/* Operators -> convertions */
qfRect::operator _qfRectInternalDataType() const {
	return m_Data;
}

