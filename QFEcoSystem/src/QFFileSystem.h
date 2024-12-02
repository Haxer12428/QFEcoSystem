#include "QFAssert.h"
#include "QFDebug.h"
#include "QFDefines.h"
#include <filesystem>
#include <array>

namespace qfFileSystem {
	class Path : public std::filesystem::path {
	public:
		Path(const char* _Path); 
		Path(const std::string& _Path);
		Path(const std::filesystem::path& _Path);

		const bool isReservedDeviceName() const; 
		const bool isSpecialDir() const; 
	public:
		 
	};

};