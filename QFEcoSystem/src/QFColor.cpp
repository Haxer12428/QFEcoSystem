#include "QFColor.h"
#include <fmt/core.h>

/* Constructors */
qfColor::qfColor(float _r, float _g, float _b, float _a)
	: m_Value{ glm::vec<4, float, glm::defaultp>(_r, _g, _b, _a)  } {
	normalize();
}

qfColor::qfColor(int _r, int _g, int _b, int _a)
	: m_Value{ glm::vec<4, float, glm::defaultp>(static_cast<float>(_r), static_cast<float>(_g), static_cast<float>(_b), static_cast<float>(_a)) } {
	
	normalize();
};

/* Transformations */
void qfColor::normalize() {
	m_Value.x = glm::clamp(m_Value.x > 1.0f ? m_Value.x / 255.0f : m_Value.x, 0.0f, 1.0f);
	m_Value.y = glm::clamp(m_Value.y > 1.0f ? m_Value.y / 255.0f : m_Value.y, 0.0f, 1.0f);
	m_Value.z = glm::clamp(m_Value.z > 1.0f ? m_Value.z / 255.0f : m_Value.z, 0.0f, 1.0f);
	m_Value.w = glm::clamp(m_Value.w > 1.0f ? m_Value.w / 255.0f : m_Value.w, 0.0f, 1.0f);
}

float& qfColor::r() {
	return m_Value.x;
}

float& qfColor::g() {
	return m_Value.y;
}

float& qfColor::b() {
	return m_Value.z;
}

float& qfColor::a() {
	return m_Value.w;
}

const std::string qfColor::getString() const {
	return fmt::format("qfColor({},{},{},{})", m_Value.x, m_Value.y, m_Value.z, m_Value.w);
}
qfColor::operator ImColor() const {
	return ImColor(m_Value.r, m_Value.g, m_Value.b, m_Value.a);
}