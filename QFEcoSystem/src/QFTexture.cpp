#include "QFTexture.h" 
#include <SOIL2/SOIL2.h>

#define STB_IMAGE_IMPLEMENTATION

qfTexture::qfTexture(const std::filesystem::path& _Path, qfTexture::Flags _Flags)
	: m_Flags{_Flags}
{
	if (qfCompare::flagIsInEnumClassPool(
		m_Flags, Flags::LoadWithSOIL2
	)) {
		loadFromFileSOIL2(_Path);
		return;
	}

	if (qfCompare::flagIsInEnumClassPool(
		m_Flags, Flags::LoadWithSTB
	)) {
		loadFromFileSTB(_Path);
		return;
	}

	_qfAssert(false, "Invaild loading flag");
}

qfTexture::qfTexture(const unsigned char _Data[], const unsigned int _Len, qfTexture::Flags _Flags)
	: m_Flags{_Flags}
{
	if (qfCompare::flagIsInEnumClassPool(_Flags, Flags::LoadWithSOIL2)) {
		loadFromMemorySOIL2(_Data, _Len); return;
	}
	_qfAssert(false, "Invaild|Unsupported loading flag");
}

qfTexture::~qfTexture() {
	/* Clear on destruction */
	glGenTextures(1, &m_TextureId);
}

void qfTexture::loadFromMemorySOIL2(const unsigned char _Data[], const unsigned int _Len) {
	m_TextureId = SOIL_load_OGL_texture_from_memory(
		reinterpret_cast<const unsigned char*>(_Data),
		_Len,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	_qfAssert(m_TextureId != 0, "SOIL2: Failed to load texture [LATE]");
}

void qfTexture::loadFromFileSTB(const std::filesystem::path& _Path) {
	int width, height, channels;

	// Load the image using stb_image
	unsigned char* data = stbi_load(_Path.string().c_str(), &width, &height, &channels, 0);

	// Assert that the image loaded successfully
	_qfAssert(data, "STB: Failed to load image");
	if (!data) return;

	// Load texture using SOIL from memory (pass stb_image's data)
	m_TextureId = SOIL_load_OGL_texture_from_memory(
		reinterpret_cast<const unsigned char*>(data), 
		width * height * channels, 
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	// Free the image memory from stb_image
	stbi_image_free(data);

	// Assert that the texture was created successfully
	_qfAssert(m_TextureId != 0, "STB: Failed to load texture [Late]");
}

void qfTexture::loadFromFileSOIL2(const std::filesystem::path& _Path) {
	m_TextureId = SOIL_load_OGL_texture(
		_Path.string().c_str(),                 // Path to the image file
		SOIL_LOAD_AUTO,           // Automatically determine format
		SOIL_CREATE_NEW_ID,       // Generate a new OpenGL texture ID
		SOIL_FLAG_MIPMAPS
	);

	GLenum glError = glGetError();
	_qfAssert(glError == GL_NO_ERROR, "OpenGL error occured when loading texture");

	//glBindTexture(GL_TEXTURE_2D, m_TextureId);

	_qfAssert(m_TextureId, fmt::format("SOIL2 could not load img[{}] as texture", _Path.string()));
}

GLuint qfTexture::getGLTextureId() const { return m_TextureId; }