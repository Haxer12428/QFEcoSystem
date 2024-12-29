#include "QFVec2.h"
#include <glm/vec2.hpp>
#include "imgui.h"

/* Constructors */
qfVec2::qfVec2() : m_Data{ glm::vec2(0, 0) } {};
qfVec2::qfVec2(float _both) : m_Data{ glm::vec2(_both, _both) } {}
qfVec2::qfVec2(float _x, float _y) : m_Data{glm::vec2(_x, _y)} {}
qfVec2::qfVec2(const glm::vec2& _Vec) : m_Data{ _Vec } {}
qfVec2::qfVec2(ImVec2 _Vec) : m_Data { glm::vec2(_Vec.x, _Vec.y) } {}

/* Overloads -> to type */
qfVec2::operator glm::vec2() const { return m_Data; }

float qfVec2::_x() const { return m_Data.x; };
float qfVec2::_y() const { return m_Data.y; };

const std::string qfVec2::getString() const {
	return fmt::format("qfVec2({}, {})", m_Data.x, m_Data.y);
}

/* Operators */
qfVec2 qfVec2::operator+(const qfVec2& _Other) const {
	return (m_Data + _Other.m_Data);
}
qfVec2 qfVec2::operator-(const qfVec2& _Other) const {
	return (m_Data - _Other.m_Data);
}
qfVec2 qfVec2::operator*(const qfVec2& _Other) const {
	return (m_Data * _Other.m_Data);
}
qfVec2 qfVec2::operator/(const qfVec2& _Other) const {
	return (m_Data / _Other.m_Data);
}

qfVec2 qfVec2::operator+=(const qfVec2& _Other) {
	m_Data[0] += _Other._x();
	m_Data[1] += _Other._y();

	return *this;
}

qfVec2 qfVec2::operator-=(const qfVec2& _Other) {
	m_Data[0] -= _Other._x();
	m_Data[1] -= _Other._y();

	return *this;
}

/* Checks */
const bool qfVec2::isIntersecting(const qfVec2& _First, const qfVec2& _Last) const {
	return (
		m_Data.x >= (
		_First.m_Data.x < _Last.m_Data.x ? _First.m_Data.x : _Last.m_Data.x)
		) &&
		(m_Data.x <= (_First.m_Data.x > _Last.m_Data.x ? _First.m_Data.x : _Last.m_Data.x)
		) &&
		(m_Data.y >= (_First.m_Data.y < _Last.m_Data.y ? _First.m_Data.y : _Last.m_Data.y)
		) &&
		(m_Data.y <= (_First.m_Data.y > _Last.m_Data.y ? _First.m_Data.y : _Last.m_Data.y)
		);
}
