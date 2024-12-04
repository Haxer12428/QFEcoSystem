#pragma once
#include "QFDefines.h"
#include <glm/glm.hpp>
#include <ostream>
#include <imgui.h>

class qfColor {
public:
	qfColor(float _r, float _g, float _b, float _a);
	qfColor(int _r, int _g, int _b, int _a);
	
	void normalize();

	float& r();
	float& g();
	float& b();
	float& a();

	operator ImColor() const; 

	const std::string getString() const; 

	friend std::ostream& operator<<(std::ostream& _Os, const qfColor& _Clr) {
		_Os << _Clr.getString(); return _Os;
	}
private:
	glm::vec<4, float, glm::defaultp> m_Value; 
};