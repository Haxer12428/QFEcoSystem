#pragma once
#include <unordered_map>
#include "QFDefines.h"
#include "QFAssert.h"
#include <fmt/core.h>
#include <cstdlib>
#include <string>

class qfDebug {
public:
	enum class DebugType : uint16_t {
		Error,
		Warning,
		Message,
		ElevatedMessage
	};

private:
	static std::unordered_map<DebugType, bool> m_DebugTypePrint; 
	static std::unordered_map<DebugType, std::string> m_DebugTypeColor; 
	static bool m_PrintColor;
public: 
	static void print(const DebugType& _Type, const std::string& _What, const std::string& _Function);

};

/* Debug defines */
#ifdef _qfDebugBuild
	#define _qfDebugLog(type, what) qfDebug::print(type, what, __FUNCTION__);
#else 
	#define _qfDebugLog(type, what) void(0)
#endif

#define _qfDebugError qfDebug::DebugType::Error
#define _qfDebugElevatedMessage qfDebug::DebugType::ElevatedMessage 
#define _qfDebugMessage qfDebug::DebugType::Message
#define _qfDebugWarning qfDebug::DebugType::Warning 


