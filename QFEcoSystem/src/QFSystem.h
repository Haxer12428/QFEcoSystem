#pragma once
#include "QFDefines.h"
#include "QFAssert.h"
#include "QFDebug.h"

class qfSystem {
public:
	static const std::string getClipboardData();
	static const bool setClipboardData(const std::string& _New);
	static std::vector<char> getImgDataFromEmbeddedResource(const std::string& _ResourceName);
};