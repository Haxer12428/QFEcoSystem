#pragma once
#include <type_traits>
#include "QFAssert.h"

class qfCompare {
public:
	/* Use this only on enum classes */
	template<typename _Class> 
	static const bool flagIsInEnumClassPool(_Class _Pool, _Class _Var) {
		_qfAssert(std::is_enum<_Class>::value, "Type must be enum class");
		
		return (
			static_cast<std::underlying_type<_Class>::type>(_Pool)
			&
			static_cast<std::underlying_type<_Class>::type>(_Var)
		);
	}
};
