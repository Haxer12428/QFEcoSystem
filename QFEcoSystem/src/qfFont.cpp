#include "qfFont.h"

qfFont::qfFont(const std::filesystem::path& _Path, float _Size) {
	_qfAssert(ImGui::GetCurrentContext(), _qfViolationNullptrAccess);

	std::optional<ImFont*> fontFromAtlas = getLoadedFromTTF(_Path, _Size);

	if (fontFromAtlas.has_value()) {
		m_FontLoaded = fontFromAtlas.value();

		_qfLogIf(_qfDebugLevelRegular, _qfDebugLog(_qfDebugMessage,
			fmt::format("Loaded font[{}] from atlas", _Path.string())
			));
		return; 
	}

	ImGuiIO io = ImGui::GetIO();
	
	_qfAssert(std::filesystem::is_regular_file(_Path), fmt::format(
		"Non existing font[{}] file", _Path.string()
	));

	ImFont* fontLoaded = io.Fonts->AddFontFromFileTTF(
		_Path.string().c_str(), _Size, nullptr, io.Fonts->GetGlyphRangesDefault()
	);
	io.Fonts->Build();

	m_FontLoaded = fontLoaded;	

	_qfLogIf(_qfDebugLevelRegular, _qfDebugLog(_qfDebugMessage, fmt::format(
		"Loaded font[{}] from file", _Path.string()
	)));
}

qfFont::~qfFont() = default; 

qfFont::operator ImFont*()  { return m_FontLoaded; }
ImFont* qfFont::getImFont() { return m_FontLoaded; }

qfVec2 qfFont::getTextSize(const std::string& _Text) {
	_qfAssert(m_FontLoaded, "Font not loaded");
	
	ImGui::PushFont(m_FontLoaded);
	qfVec2 tlSize = ImGui::CalcTextSize(_Text.c_str());
	
	ImGui::PopFont();
	return tlSize;
}


std::optional<ImFont*> qfFont::getLoadedFromTTF(const std::filesystem::path& _Path, float _Size) {
	ImGuiIO& io = ImGui::GetIO();

	for (ImFont* _Font : io.Fonts->Fonts) {
		const ImFontConfig* fontConfig = _Font->ConfigData;

		if (fontConfig && fontConfig->SizePixels == _Size 
			&& _Path == fontConfig->Name
			) {
			return _Font; 
		}
	}
	return std::nullopt;
}