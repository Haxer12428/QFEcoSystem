#include "QFCall.h"

namespace qfCall {
	ClassEventSystem::ClassEventSystem() {
		m_EventHandler = std::make_unique<ClassCallback>();
	}

	ClassEventSystem::~ClassEventSystem() = default;

	std::unique_ptr<ClassCallback>& ClassEventSystem::getHandler() {
		return m_EventHandler; 
	}
}