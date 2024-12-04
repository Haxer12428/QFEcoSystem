#include "QFFileSystem.h"
#include "QFTransform.h"
#include <iostream>
namespace fs = std::filesystem;

namespace qfFileSystem {
	ConfigSystem::ConfigSystem(const Path& _FilePath) 
		: m_FilePath{_FilePath}
	{
		/* Check for file existnace */
		if (!fs::is_regular_file(_FilePath)) {
			_qfLogIf(_qfDebugLevelImportant, _qfDebugLog(_qfDebugWarning, 
				fmt::format("Path is non regular file: {}", _FilePath.getWithPrintFormat())
			)); }
	}

	const bool ConfigSystem::loadCache() {
		Open::IO fileIO = Open::IO(m_FilePath);
		
		auto fileIOResult = fileIO.readBufferString(Open::IO::BufferString::FlagEOL::NONE);

		_qfAssert(fileIOResult.has_value(), "Could not load config value");
		if (!fileIOResult.has_value()) {
			return false; 
		}
		const std::string fileContent = (*fileIOResult).getString();

		try {
			qfJson jsContent = qfJson::parse(fileContent);
			m_JsonCache = jsContent;

			_qfAssert(!m_JsonCache.empty(), "Empty cache loaded");
			return true; 
		}
		catch (const qfJson::parse_error& _Msg) {
			_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugError,
				_Msg.what()
			));
			return false;
		};
	}

	const bool ConfigSystem::isCacheLoaded() const {
		return !m_JsonCache.empty();
	}

	void ConfigSystem::swapCache(const qfJson& _New) {
		m_JsonCache = _New;
	}

	qfJson& ConfigSystem::getCache(bool _AutoLoad) {
		_qfAssert((_AutoLoad || isCacheLoaded()), "Cache isn't loaded ");

		/* Not loaded cache case */
		if (!isCacheLoaded() && _AutoLoad) {
			const bool loadStatus = loadCache();
			_qfAssert(loadStatus, "cache failed to load");
		}
		
		return m_JsonCache;
	}

	const bool ConfigSystem::writeCache(int _Dump, Open::IO::BufferString::FlagEOL _EOL) {
		_qfAssert(isCacheLoaded(), "Cache not loaded");

		/* Prepare content for write */
		const std::string cacheContentStr = m_JsonCache.dump(_Dump);
		std::vector<std::string> cacheContentVectorStr = qfTransform::stringToVectorStr(cacheContentStr);

		Open::IO::BufferString cacheContentToWrite{cacheContentVectorStr, _EOL};
		/* Write */
		Open::IO fileIO = Open::IO(m_FilePath);
		const bool fileWriteResult = fileIO.writeBufferString(cacheContentToWrite);

		/* Result */
		_qfAssert(fileWriteResult, "Couldn't write file");
		return fileWriteResult; 
	}

	const bool ConfigSystem::createFile() {
		if (fs::is_regular_file(m_FilePath)) return true; 
		return Open(m_FilePath).makeFile(true);
	}
}