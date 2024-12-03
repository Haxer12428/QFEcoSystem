#include "QFAssert.h"
#include "QFDebug.h"
#include "QFDefines.h"
#include <filesystem>
#include <array>
#include <vector>
#include <optional>

namespace qfFileSystem {
	class Path : public std::filesystem::path {
	public:
		Path(const char* _Path); 
		Path(const std::string& _Path);
		Path(const std::filesystem::path& _Path);

		const bool isReservedDeviceName() const; 
		const bool isSpecialDir() const; 
		const std::string getWithPrintFormat() const;
	};

	class Open {
	public:
		class IO {
		public:
			class BufferString {
			public:
				enum class FlagEOL : uint16_t {
					CR = 0, 
					CRLF = 1, 
					LF = 2
				};
			public:
				BufferString(const std::vector<std::string>& _BufferVector, const FlagEOL& _EOLFlag);
				
				const std::vector<std::string>& getVectorString();
				const std::string getString(); 

				static const std::string getEOL(FlagEOL _Flag);
			private:
				FlagEOL m_EOLFlag; 
				std::vector<std::string> m_BufferVector; 
				std::string m_BufferString; 
			};
		public:
			IO(const Path& _Path);
		
			/* Bulk reading */
			std::optional<BufferString> readBufferString(BufferString::FlagEOL _EOL, uint64_t _EstimatedLineCount = 0);
			const bool writeBufferString(BufferString _Buffer);

		private:
			Path m_Path; 
		};
	public:
		Open(const Path& _Path);

		const bool makeDir(bool _RecursiveCreation); 
		const bool makeFile(bool _MakeDirs = false, bool _Override = false);
	private:
		Path m_Path;
	};
};