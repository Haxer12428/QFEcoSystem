#pragma once
#include "QFAssert.h"
#include "QFDebug.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include <filesystem>
#include <optional>
#include "QFVec2.h"


class qfFont {
public: 
	qfFont(const std::filesystem::path& _Path, float _Size);
	~qfFont();

	operator ImFont*(); 
	ImFont* getImFont(); 
	qfVec2 getTextSize(const std::string& _Str);
private:
	std::optional<ImFont*> getLoadedFromTTF(const std::filesystem::path& _Path, float _Size);

private:

	ImFont* m_FontLoaded; 
};
