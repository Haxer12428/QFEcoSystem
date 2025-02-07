#pragma once
#include "QFAssert.h"
#include "QFDebug.h"
#include "QFString.h"
#include <functional>
#include <vector>
#include <unordered_map>
#include <typeindex>
#include "QFIDManager.h"
#include <fmt/core.h>
#include <memory>
#include <utility>

/* 
	Callbacking class, 'event systems', timers, callback system 
*/


/* 
	There is not and there probably wont be a timer class here, 
	timers should be written in main application struct, cause timer thats threadsafe 
	requires a main loop. Both types of timers(detached, mainloop) you can eaisly write 
	without any problems and those will be integrated specificly with your needs. In my opinion 
	there isn't 'universal' solution for this problem
*/

/* Destructor wrap */
struct _qfCallOnDestructWrap {
	_qfCallOnDestructWrap(const std::function<_qfInternalVoid()>& _Func) : m_Callback{ _Func } {};
	~_qfCallOnDestructWrap() { m_Callback(); }

	std::function<_qfInternalVoid()> m_Callback;
};

namespace qfCall {

	class ClassCallback {
	public:
		class Args {
		public:
			Args() = default;
			virtual ~Args() = default;

			void stopDispatch() {
				m_DispatchStopped = true; 
			}
			bool isDispatchStopped() {
				return m_DispatchStopped;
			}
		private:
			bool m_DispatchStopped = false; 
		};
	public:
		ClassCallback() = default; 

		template <typename _ArgType, typename _Class>
		uint64_t addFunctionToStack(_Class* _ClassInstance, void (_Class::* _FunctionDeclarationPtr)(_ArgType&)) {
			/* Check for base */
			static_assert(std::is_base_of<Args, _ArgType>::value,
				"ArgType must be derived from ClassCallback::Args");
			
			const uint64_t generatedID = m_IdManager->generate();

			/* Register callback, classtype->func(args: drived from 'Args' class)*/
			m_CallStack[typeid(_ArgType)].insert({ generatedID, [_ClassInstance, _FunctionDeclarationPtr](Args& _Arguments) {
				try {
					(_ClassInstance->*_FunctionDeclarationPtr)(
						dynamic_cast<_ArgType&>(_Arguments)
						);
				}
				catch (const std::bad_cast& _Ex) {
					/* Log exception */
					_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugError, _Ex.what()));
				}} });
			/* Return result  */
			_qfLogIf(_qfDebugLevelImportant, _qfDebugLog(_qfDebugElevatedMessage, "Registered callback"));
			return generatedID; 
		}

		template<typename _ArgType>
		uint64_t addFunctionToStack(const std::function<void(_ArgType&)>& _Function) {
			static_assert(std::is_base_of<Args, _ArgType>::value,
				"ArgType must be derived from ClassCallback::Args");

			const uint64_t generatedId = m_IdManager->generate();

			m_CallStack[typeid(_ArgType)].insert({ generatedId, [_Function](Args& _Arguments) {
				_Function(dynamic_cast<_ArgType&>(_Arguments));
				}});
			return generatedId;
		}

		template<typename _ArgType> 
		bool destroyFunction(uint64_t _ID) {
			/* Assert base class */
			static_assert(std::is_base_of<Args, _ArgType>::value,
				"ArgType must be derived from ClassCallback::Args");

			auto callStackIt = m_CallStack.find(typeid(_ArgType));

			/* Could not find callstack case */
			if (callStackIt == m_CallStack.end()) {
				_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugError,
					fmt::format("Could not find callstack for given typeid: {}", typeid(_ArgType).name())
				));
				return false; 
			}

			/* Could not find callback case */
			if (callStackIt->second.find(_ID) == callStackIt->second.end()) {
				_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugError,
					fmt::format("Could not find callback with id: {}", std::to_string(_ID))
				));
				return false; 
			}
			/* Erase it */
			const bool functionEraseResult = (callStackIt->second.erase(_ID) > 0);

			/* Return result */
			_qfAssert(functionEraseResult, "Failed to erase element");
			return functionEraseResult;
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
					if (reinterpret_cast<Args*>(&_Args)->isDispatchStopped()) {
						return true; 
					}

					_CallbackHandler.second(_Args);
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
		std::unique_ptr<qfIdManager> m_IdManager = std::make_unique<qfIdManager>(0);
		std::unordered_map<std::type_index, std::unordered_map<uint64_t, std::function<void(Args&)>>> m_CallStack;
	};

	class ClassEventSystem {
	public:
		class Event : public ClassCallback::Args {
		public:
			Event() = default; 
			virtual ~Event() = default;		
		};
	public:
		ClassEventSystem(); 
		virtual ~ClassEventSystem();

		std::unique_ptr<ClassCallback>& getHandler();
	private:
		std::unique_ptr<ClassCallback> m_EventHandler; 
	};

	/* Simple tasking */
	class TaskPool {
	public:
		struct Task {
			std::function<bool()> m_Function; 
			uint64_t m_Id;
		};
	public:
		TaskPool() = default; 

		template<typename... _Args>
		uint64_t addTask(std::function<bool(_Args...)> _Function, _Args&&... _Arguments) {
			const uint64_t generatedId = m_TaskIdManager->generate();

			Task currentTask; 
			currentTask.m_Id = generatedId;

			currentTask.m_Function = std::function<bool()>([_Function, _Arguments...]() -> bool {
				return _Function(_Arguments...); // Use the original function with forwarded args
			});

			/* Insert task */
			m_Pool.emplace_back(currentTask);

			/* Log status */
			_qfLogIf(_qfDebugLevelRegular, _qfDebugLog(
				_qfDebugElevatedMessage, fmt::format("Pushed task, id: {}", generatedId)
				));

			return generatedId;
		}

		std::unordered_map<uint64_t, bool> runTasks(uint64_t _Count) {
			uint64_t tasksRan = 0; 
			std::unordered_map<uint64_t, bool> tasksResults;

			while (!m_Pool.empty() && tasksRan < _Count) {
				Task& currentTask = m_Pool.front();
				const bool taskResult = currentTask.m_Function();

				tasksResults.insert(
					{ currentTask.m_Id, taskResult }
					);
				tasksRan++;
				/* Erase from stack */
				m_Pool.erase(m_Pool.begin());
			}

#ifdef _qfDebugBuild
			/* Tasks ran are less than count, just log it  */
			if (tasksRan < _Count) {
				_qfLogIf(_qfDebugLevelImportant,
					_qfDebugLog(_qfDebugWarning, "Task's ran < _Count, not enought task's in a pool")
					);
			}
#endif
			return tasksResults;
		}

		const bool isFinished() const {
			return m_Pool.empty();
		}

		const size_t getTasksCount() const {
			return m_Pool.size();
		}

		std::vector<Task>& getTasks() {
			return m_Pool; 
		}

	private:
		std::unique_ptr<qfIdManager> m_TaskIdManager = std::make_unique<qfIdManager>(0);

		std::vector<Task> m_Pool;
	};
}