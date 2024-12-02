#pragma once
#include "QFDefines.h"
#include "QFAssert.h"
#include "QFDebug.h"

class qfSystem {
public:
	static const std::string gClipboardData();
	static const bool sClipboardData(const std::string& _New);
};