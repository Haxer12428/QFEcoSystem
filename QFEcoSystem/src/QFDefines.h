#pragma once
#include <type_traits>
#include <chrono>

#ifndef NDEBUG
	#define _qfDebugBuild
#endif // !NDEBUG

/* Uncomment this for better debugging */
#define _qfShutdownWithRuntimeError

/* 
	QF Debug Levels 0 - 3: 
		0: Every shit is here, unreadable console 
		1: More important shit is here like, togging a switch 
		2: Even more important stuff, for example: constructor || destructor calls
		3: Most important shit, for example suggestions
*/
#define _qfDebugLevelAll 0
#define _qfDebugLevelRegular 1
#define _qfDebugLevelImportant 2
#define _qfDebugLevelCritical 3

#define _qfDebugLevel _qfDebugLevelImportant

/* WARNING: prints self and upper levels -> Should not use this anymore!
	If u see something like this in the code change this to _qfLogIf -> newer, clearer version of this
*/
#ifdef _qfDontUseThis_IfUSeeThisChangeItToNewerVersionDescribedBelowAs_qfLogIf
	#if _qfDebugLevel <= _qfDebugLevelRegular
		// log something using the old method (deprecated)
	#endif 
#endif 

/* Thing from comment above is obselete, this is new way of logging with level  */
#ifdef _qfDebugBuild
	#define _qfLogIf(level, action) \
			do { \
					if (_qfDebugLevel <= (level)) { action; } \
			} while (false)
#else 
		#define _qfLogIf(level, action) ((void)(level), void(0))
#endif

/* Fancy string */
#define _qfEmptyString ""

/* Qf Error codes: basic */
static constexpr const char* _qfViolationNullptrAccess = "Violation: Tried to access nullptr";
static constexpr const char* _qfViolationNullptrArg    = "Violation: Tried to pass nullptr argument";

/* Uncomment this for extended features */
//#define _qfDebugExtededFeatures 

#define _qfDontCareInt -3014
constexpr const int _qfUnassignedInt = -1; 

#ifdef _qfBestPractises 
	/* Using things like std::find, std::remove instead of for loops etc whenever I can, its not error prone
		guarnatees good preformance, its actually easier to write, debug, and maintain 
		It should be used like this from what im aware. Its also very easy to read and change to something else 
		later on
	*/
#endif 

/* qf Quality-Of-Life defines  */
#define _qfQOL

/* its quality of life but important to whole gui engine */
template <typename T>
constexpr T _qfSafeClamp(const T & _Value, const T & _Min, const T & _Max) {
	static_assert(std::is_arithmetic_v<T>, "T must be a number type.");
	return (_Value < _Min) ? _Min : (_Value > _Max) ? _Max : _Value;
}


/* qf Read-Helper defines */
#define _qfInternalVoid void

#ifdef _qfQOL 
#include <memory>
#include <functional>
	using qfMs = std::chrono::milliseconds;

	template <typename _Type> std::unique_ptr<_Type> 
	_qfCloneUniquePtr(std::unique_ptr<_Type>&_Original) {
		if (!_Original) return nullptr; 
		return std::make_unique<_Type>(*_Original);
	}
#endif 

/* Enum class bitwise operators */
template <typename Enum>
constexpr std::enable_if_t<std::is_enum_v<Enum>, Enum>
operator|(Enum lhs, Enum rhs) {
	using Underlying = std::underlying_type_t<Enum>;
	return static_cast<Enum>(static_cast<Underlying>(lhs) | static_cast<Underlying>(rhs));
}

