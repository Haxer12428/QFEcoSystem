#pragma once
#include "QFAssert.h"
#include "QFDebug.h"
#include "QFString.h"
#include <functional>
#include <vector>
#include <unordered_map>
#include <typeindex>

/* 
	Callbacking class, 'event systems', timers, callback system 
*/

namespace qfCall {
	class ClassCallback {
	public:
		class Args {
		public:
			Args() = default;
			virtual ~Args() = default;
		};
	public:
		ClassCallback() = default; 

		template <typename _ArgType, typename _Class>
		bool addFunctionToStack(_Class* _ClassInstance, void (_Class::* _FunctionDeclarationPtr)(_ArgType&)) {
			/* Check for base */
			static_assert(std::is_base_of<Args, _ArgType>::value,
				"ArgType must be derived from ClassCallback::Args");
			
			/* Register callback, classtype->func(args: drived from 'Args' class)*/
			m_CallStack[typeid(_ArgType)].emplace_back([_ClassInstance, _FunctionDeclarationPtr](Args& _Arguments) {
				try {
					(_ClassInstance->*_FunctionDeclarationPtr)(
						dynamic_cast<_ArgType&>(_Arguments)
						);
				}
				catch (const std::bad_cast& _Ex) {
					/* Log exception */
					_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugError, _Ex.what()));
				}});
			/* Return result  */
			_qfLogIf(_qfDebugLevelImportant, _qfDebugLog(_qfDebugElevatedMessage, "Registered callback"));
			return true; 
		}

		template<typename _ArgType>
		bool dispatchStack(_ArgType _Args) {
			/* Assert base class */
			static_assert(std::is_base_of<Args, _ArgType>::value,
				"ArgType must be derived from ClassCallback::Args");

			auto callIt = m_CallStack.find(typeid(_ArgType));

			/* Check for existant */
			if (callIt == m_CallStack.end()) {
				_qfLogIf(_qfDebugLevelRegular, _qfDebugLog(_qfDebugMessage, 
					"Failed to find associated callbacks for current type"
				));
				return false; 
			}
			/* Call */
			for (const auto& _CallbackHandler : callIt->second) {
				try {
					_CallbackHandler(_Args);
				}
				catch (const std::exception& ex) {
					/* Log exception on call & return failure */
					_qfLogIf(_qfDebugLevelCritical, 
						_qfDebugLog(_qfDebugError, ex.what()
						));
					return false; 
				}
				 
				_qfLogIf(_qfDebugLevelRegular, _qfDebugLog(_qfDebugElevatedMessage, "Called function"));
			}
			/* Return success */
			return true; 
		}
	private:
		std::unordered_map<std::type_index, std::vector<std::function<void(Args&)>>> m_CallStack;
	};
}