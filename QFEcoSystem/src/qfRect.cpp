#include "QFRect.h"

/* Constructors */
qfRect::qfRect() 
	: m_Data{ _qfRectInternalDataType(0.0f, 0.0f, 0.0f, 0.0f) } {};

qfRect::qfRect(float _x, float _y, float _sx, float _sy) : 
	m_Data{ _qfRectInternalDataType(_x, _y, _sx, _sy) } {};

qfRect::qfRect(const qfVec2& _p1, const qfVec2& _size)
	: m_Data{ _qfRectInternalDataType(_p1._x(), _p1._y(), _size._x(), _size._y()) } {};

qfRect::qfRect(const RECT& _WinRect) 
  : m_Data{ _qfRectInternalDataType(
    static_cast<float>(_WinRect.left), // x 
    static_cast<float>(_WinRect.top),  // y
    static_cast<float>(_WinRect.right  - _WinRect.left), // sx
    static_cast<float>(_WinRect.bottom - _WinRect.top)   // sy
  )}
{}

/* Destructor */
qfRect::~qfRect() = default; 

/* Public -> Get's */
qfVec2 qfRect::getPosition() const { return qfVec2{ m_Data.x, m_Data.y }; }
qfVec2 qfRect::getSize() const { return qfVec2{ m_Data.z, m_Data.w }; }
qfVec2 qfRect::getFinalPosition() const { return (getPosition() + getSize()); }


/* those are used for get and set */
float& qfRect::_x() { return m_Data.x; }
float& qfRect::_y() { return m_Data.y; }
float& qfRect::_sx() { return m_Data.z; }
float& qfRect::_sy() { return m_Data.w; }

void qfRect::setPosition(const qfVec2& _New) {
  m_Data.x = _New._x(); 
  m_Data.y = _New._y();
}

void qfRect::setSize(const qfVec2& _New) {
  m_Data.z = _New._x();
  m_Data.w = _New._y();
}

void qfRect::shiftAndShrink(float _By) {
	m_Data.x += _By;
	m_Data.y += _By;
	m_Data.z -= _By * 2; 
	m_Data.w -= _By * 2;
}

void qfRect::shiftAndShrinkByScale(float _Scale) {
	m_Data.x *= _Scale;
	m_Data.y *= _Scale; 

	m_Data.z *= (_Scale);
	m_Data.w *= (_Scale);
}

void qfRect::scaleSize(float _Scale) {
	m_Data.z *= (_Scale);
	m_Data.w *= (_Scale);
}

/* Operators -> convertions */
qfRect::operator _qfRectInternalDataType() const {
	return m_Data;
}
/* Public -> Get's : conversions */
const qfString qfRect::getString() const {
	return fmt::format("qfRect({}, {}, {}, {})", m_Data.x, m_Data.y, m_Data.z, m_Data.w);
}
/* Public -> Checks */

/* This should be valid for all scenarios;
  Only scenario that's not implemented is roatetd rect's but it doens't belong here for now
*/
const bool qfRect::isIntersecting(const qfRect& r2) {
  const qfVec2 pos1 = getPosition();  // Bottom-left corner of rect 1
  const qfVec2 size1 = getSize();     // Width and height of rect 1
  const qfVec2 finalPos1 = getFinalPosition(); // Top-right (or max boundary) of rect 1

  const qfVec2 pos2 = r2.getPosition();  // Bottom-left corner of rect 2
  const qfVec2 size2 = r2.getSize();     // Width and height of rect 2
  const qfVec2 finalPos2 = r2.getFinalPosition(); // Top-right (or max boundary) of rect 2

  // Check if rectangles are overlapping on X and Y axis
  bool overlapX = (finalPos1._x() > pos2._x()) && (pos1._x() < finalPos2._x());
  bool overlapY = (finalPos1._y() > pos2._y()) && (pos1._y() < finalPos2._y());

  // If both axes are overlapping, the rectangles intersect
  return overlapX && overlapY;
}
