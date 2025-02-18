#include "QFDebug.h"

constexpr const char* _qfAnsiReset = "\033[0m";

/* Staic vars expansion */
std::unordered_map<qfDebug::DebugType, bool> qfDebug::m_DebugTypePrint = {
	{ qfDebug::DebugType::Message, true },
	{ qfDebug::DebugType::Error, true },
	{ qfDebug::DebugType::Warning, true }, 
	{ qfDebug::DebugType::ElevatedMessage, true } 
};

std::unordered_map<qfDebug::DebugType, std::string> qfDebug::m_DebugTypeColor = {
		{ DebugType::Message, "\033[38;5;33m" },        // Light Blue (Text: White)
		{ DebugType::Error, "\033[48;5;124m\033[97m" },  // Bright Red (Text: White)
		{ DebugType::Warning, "\033[48;5;226m\033[30m" },// Bright Yellow (Text: Black)
		{ DebugType::ElevatedMessage, "\033[38;5;130m" },// Peach (Text: White)
};

/* Print */
void qfDebug::print(const DebugType& _Type, const std::string& _What, const std::string& _Function) {
	/* Make this ifdef just in case something isn't using macro for this */
#ifdef _qfDebugBuild
	auto printIt = m_DebugTypePrint.find(_Type);
	_qfAssert(printIt != m_DebugTypePrint.end(), "Print option missing");

	/* Return early if print 'flag' is set to false */
	if (!printIt->second)
		return; 

	auto colorIt = m_DebugTypeColor.find(_Type);
	_qfAssert(colorIt != m_DebugTypeColor.end(), "Color missing");

	const std::string msgColor  = colorIt->second;

	const std::string msgStr = fmt::format(
		"[{}{}{}]:\n"		     // [{color} {where} {reset}] Trace:
		"  -> {}\n\n"			 //		-> {what}.
		,
		msgColor, 
		_Function, 
		_qfAnsiReset,
		_What
		);
	/* Print */
	printf(msgStr.c_str());
#endif // _qfDebugBuild
}

