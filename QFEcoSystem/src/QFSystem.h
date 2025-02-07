#pragma once
#include "QFDefines.h"
#include "QFAssert.h"
#include "QFDebug.h"
#include "QFRect.h"
#include <windows.h>
#define NOMINMAX

class qfSystem {
public:
	struct AppBarInfo {
		HWND m_HWND; 
		qfRect m_Rect; 
	};

	static const std::string getClipboardData();
	static const bool setClipboardData(const std::string& _New);
	static std::vector<char> getImgDataFromEmbeddedResource(const std::string& _ResourceName);

	static AppBarInfo getAppBarInfo();
};