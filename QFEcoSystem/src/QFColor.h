#pragma once
#include "QFDefines.h"
#include <glm/glm.hpp>
#include <ostream>
#include <imgui.h>
#include <vector>

class qfColor {
public:
	qfColor();
	qfColor(float _r, float _g, float _b, float _a);
	qfColor(int _r, int _g, int _b, int _a);
	qfColor(const std::vector<float>& _Vec);

	void normalize();

	float& r();
	float& g();
	float& b();
	float& a();

	operator ImColor() const; 
	operator ImU32() const; 
	operator std::vector<float>() const; 

	const std::string getString() const; 

	friend std::ostream& operator<<(std::ostream& _Os, const qfColor& _Clr) {
		_Os << _Clr.getString(); return _Os;
	}
private:
	glm::vec<4, float, glm::defaultp> m_Value; 
};