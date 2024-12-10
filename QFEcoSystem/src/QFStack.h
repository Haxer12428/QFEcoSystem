#pragma once 
#include "QFDebug.h"
#include "QFAssert.h"
#include <vector>
#include <memory>

namespace qfStack {
	template<typename _Class> 
	class UniquePtr {
	public:
		UniquePtr() = default; 
		~UniquePtr() = default;

		void assignAll() {
			for (auto& _Element : m_AssignmentStack) {
				m_Stack.push_back(std::move(_Element));
			}
			m_AssignmentStack.clear();
		}

		void pushToAssignmentStack(std::unique_ptr<_Class> _Ptr) {
			m_AssignmentStack.push_back(std::move(_Ptr));
		}

		std::vector<std::unique_ptr<_Class>>& getAssignmentStack() { return m_AssignmentStack; }
		std::vector<std::unique_ptr<_Class>>& getStack() { return m_Stack;  }
	private:
		std::vector<std::unique_ptr<_Class>> m_Stack;
		std::vector<std::unique_ptr<_Class>> m_AssignmentStack;
	};
};