#pragma once
#include "GL/glew.h"
#include "imgui.h"
#include "QFCompare.h"
#include <filesystem>
#include "stb_image.h"


class qfTexture {
public:
	enum class Flags {
		LoadWithSOIL2 = 1 << 0, 
		LoadWithSTB = 1 << 1
	};

	qfTexture(const std::filesystem::path& _Path, Flags _Flags);
	qfTexture(const unsigned char _Data[], const unsigned int _Len, Flags _Flags);
	~qfTexture();

	GLuint getGLTextureId() const; 
private:
	void loadFromFileSOIL2(const std::filesystem::path& _Path);
	void loadFromFileSTB(const std::filesystem::path& _Path);

	void loadFromMemorySOIL2(const unsigned char _Data[], const unsigned int _Len);
private:
	GLuint m_TextureId; 
	Flags m_Flags; 
};