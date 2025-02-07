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
			for (std::unique_ptr<_Class>& _Element : m_AssignmentStack) {
				if (_Element.get() != nullptr)
					m_Stack.push_back(std::move(_Element));
			}
			m_AssignmentStack.clear();
		}

		void disassignAll() {
			while (!m_DisassignmentStack.empty()) {
				for (size_t _It = 0; _It < m_Stack.size(); _It++) {
					_Class* assignedObject = m_Stack[_It].get();

					/* Erase elem from assigned */
					if (assignedObject == m_DisassignmentStack.front()) {
						m_Stack.erase((
							m_Stack.begin() + _It
							));
						/* Log info */
						_qfLogIf(_qfDebugLevelRegular, _qfDebugLog(_qfDebugMessage,
							fmt::format("Erased object from stack, iterator[{}]", _It)));
					}}
				/* Erase elem from disassigned */
				m_DisassignmentStack.erase(m_DisassignmentStack.begin());
			}
		}

		void pushToAssignmentStack(std::unique_ptr<_Class> _Ptr) {
			m_AssignmentStack.push_back(std::move(_Ptr));
		}

		void pushToDisassignmentStack(std::unique_ptr<_Class>& _Ptr) {
			if (!_Ptr) return;

			m_DisassignmentStack.push_back(_Ptr.get());
		}
		void pushToDisassignmentStack(_Class* _Ptr) { 
			if (!_Ptr) return; 
			m_DisassignmentStack.push_back(_Ptr); 
		}

		std::vector<std::unique_ptr<_Class>>& getAssignmentStack() { return m_AssignmentStack; }
		std::vector<_Class*>& getDisassignmentStack() { return m_DisassignmentStack; }
		std::vector<std::unique_ptr<_Class>>& getStack() { return m_Stack;  }
	private:
		std::vector<std::unique_ptr<_Class>> m_Stack;
		std::vector<std::unique_ptr<_Class>> m_AssignmentStack;
		std::vector<_Class*> m_DisassignmentStack;
	};
};