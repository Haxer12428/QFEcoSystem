#include "QFFileSystem.h"
#include <fstream>
#include <optional>
#include <vector>

namespace qfFileSystem
{
	Open::IO::IO(const Path& _Path) : m_Path{ _Path } {
		if (!std::filesystem::is_regular_file(_Path)) {
			/* Simple warning */
			_qfLogIf(_qfDebugLevelCritical, 
				_qfDebugLog(_qfDebugWarning, 
				fmt::format("Non existant path: ", _Path.getWithPrintFormat())
				));
		}
	};

	const bool Open::IO::writeBufferString(BufferString _Buffer) {
		std::ofstream file(m_Path, std::ios::out | std::ios::binary);

		if (!file) {
			_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugError, "Failed to write to a file"));
			return false; 
		}

		const std::string& bufferString = _Buffer.getString();
		file.write(bufferString.c_str(), bufferString.size());
		/* RAII close */
		if (!file) {
			_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugError, "Error occured during write"));
			return false; 
		}

		return true; 
	}

	std::optional<Open::IO::BufferString> Open::IO::readBufferString(BufferString::FlagEOL _EOL, uint64_t _EstimatedLineCount) {
		std::ifstream fileObject(m_Path, std::ios::in);

		if (!fileObject) {
			_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(
				_qfDebugError, fmt::format("Failed to open file for read: {}", m_Path.getWithPrintFormat())
			));
			return std::nullopt;
		}
		/* Collect buffer */
		std::string currentBuffer; 
		std::vector<std::string> bufferVectorStr;

		if (_EstimatedLineCount > 0) { /* Reserve */
			bufferVectorStr.reserve(_EstimatedLineCount);
		}

		while (std::getline(fileObject, currentBuffer)) {
			bufferVectorStr.emplace_back(std::move(currentBuffer));
		}
		/* Read check */
		if (fileObject.bad()) {
			_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(
				_qfDebugError, fmt::format("Error occurred while reading: {}", m_Path.getWithPrintFormat())
			));
			return std::nullopt;
		}

		/* Return: RAII CLOSE */
		_qfLogIf(_qfDebugLevelRegular, _qfDebugLog(_qfDebugMessage, "Successfully read"));
		return BufferString(bufferVectorStr, _EOL);
	}

	
}