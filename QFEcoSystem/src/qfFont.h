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

	void reload();
	/* Requires reload */
	void setSize(float _New);


	qfVec2 getCharSize(char _Char);
private:
	std::optional<ImFont*> getLoadedFromTTF(const std::filesystem::path& _Path, float _Size);

	void loadFromTTF(const std::filesystem::path& _Path, float _Size);

private:
	float m_Size; 
	const std::filesystem::path m_Path;

	ImFont* m_FontLoaded; 
};
