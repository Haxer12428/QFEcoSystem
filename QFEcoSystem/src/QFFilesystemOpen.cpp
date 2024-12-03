#include "QFFileSystem.h"
#include <fstream>

namespace fs = std::filesystem;

namespace qfFileSystem {
	Open::Open(const Path& _Path)
		: m_Path{ _Path } {};

	/* Make */
	const bool Open::makeDir(bool _RecursiveCreation) {
		if (fs::exists(m_Path)) {
			_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugWarning,
				fmt::format("Path already exists: {}", m_Path.string())));
			return true; 
		}

		bool output = false; 
		if (_RecursiveCreation) {
			output = fs::create_directories(m_Path);
		}
		else {
			if (std::filesystem::exists(m_Path.parent_path())) {
				output = fs::create_directory(m_Path);
			}
		}

		if (output) {
			_qfLogIf(_qfDebugLevelRegular, 
				_qfDebugLog(_qfDebugMessage, fmt::format("Created path[{}]", m_Path.string()))
				);
		}
		else {
			_qfLogIf(_qfDebugLevelCritical,
				_qfDebugLog(_qfDebugError, fmt::format("Failed to create path[{}]", m_Path.string()))
				);
		}

		return output; 
	}

	const bool Open::makeFile(bool _MakeDirs, bool _Override) {
		const std::string pathObjStr = m_Path.getWithPrintFormat();
		const bool pathExists = fs::exists(pathObjStr);

		if (pathExists && std::filesystem::is_directory(m_Path)) {
			_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugError,
				fmt::format("Already exists as a directory; path: {}", pathObjStr)));
			return false; 
		}

		if (pathExists && !_Override) {
			_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugWarning,
				fmt::format("Already exists, _Override == false; path: {}", pathObjStr)));
			return false; 
		}

		Path parentPath = m_Path.parent_path();

		if (parentPath.empty()) {
			_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugError, 
				fmt::format("parent path empty for {}", pathObjStr)));
			return false;
		}

		const bool parentPathValidDir = fs::is_directory(parentPath);
		
		if (!parentPathValidDir && !_MakeDirs) {
			_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugError, 
				fmt::format("No parent path, _MakeDirs == false; path: ", pathObjStr)));
			return false; 
		}

		if (!parentPathValidDir && !fs::create_directories(parentPath)) {
			_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugError,
				fmt::format("Failed to create directories for: {}", pathObjStr)));
			return false; 
		}
		
		std::ofstream fileObject(m_Path.string());
		if (!fileObject) {
			_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugError,
				fmt::format("Failed creating file: ", pathObjStr)));
			return false; 
		}

		if (!fs::is_regular_file(m_Path)) {
			_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugError,
				fmt::format("Created file, still doesn't exist; path: {}", pathObjStr)));
			return false; 
		}
		_qfLogIf(_qfDebugLevelRegular, _qfDebugLog(_qfDebugMessage,
			fmt::format("Created file: {}", pathObjStr)));

		return true; 
	}
}