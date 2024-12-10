#include "QFFileSystem.h"
#include "QFTransform.h"
#include <Windows.h>

namespace fs = std::filesystem;

namespace qfFileSystem {
	/* Constructors */
	Path::Path(const std::string& _P) : fs::path{ _P } {};
	Path::Path(const char* _P) : fs::path{ _P } {};
	Path::Path(const std::filesystem::path& _P) : fs::path{ _P } {};

	/* Checks */
	const bool Path::isReservedDeviceName() const {
		/* Goofy thing */
		try {
			bool regularFile = fs::is_regular_file(this->string());
			return false; 
		}
		catch (fs::filesystem_error&) { 
#if _qfDebugLevel <= _qfDebugLevelRegular
			_qfDebugLog(_qfDebugMessage, fmt::format("path[{}] is reserved device name", this->string()));
#endif 
			return true; 
		}
		return false; 
	}
	
	const bool Path::isSpecialDir() const {
		HANDLE hFile = CreateFileA(
			this->string().c_str(),
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_BACKUP_SEMANTICS,
			NULL
		);

		if (hFile == INVALID_HANDLE_VALUE) {
#if _qfDebugLevel <= _qfDebugLevelRegular
			_qfDebugLog(_qfDebugMessage, fmt::format("path[{}] is special dir", this->string()));
#endif 
			return true;
		}

		CloseHandle(hFile);
		return false;
	}

	const std::string Path::getWithPrintFormat() const {
		return fmt::format("_qfFileSystem::Path[{}]", this->string());
	}

}