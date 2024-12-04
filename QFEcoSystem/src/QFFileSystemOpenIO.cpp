#include "QFFileSystem.h"
#include <fstream>
#include <optional>
#include <vector>
#include "QFEncryption.h"

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

	const bool Open::IO::writeBufferString(BufferString _Buffer, bool _ChecksumsSha256) {
		std::ofstream file(m_Path, std::ios::out | std::ios::binary);

		if (!file || !file.is_open()) {
			_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugError, "Failed to open a file"));
			return false; 
		}

		const std::string& bufferString = _Buffer.getString();
		file.write(bufferString.c_str(), bufferString.size());
		
		if (!file) {
			_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugError, "Error occured during write"));
			return false; 
		}
		/* Close: needed for sha256 checksums */
		file.close();

		if (!_ChecksumsSha256) {
			return true; /* No checksums validation required */
		}
		/* Sha 256 checksums */
		auto fileContent = readBufferString(_Buffer.getEOLFlag(), _Buffer.getVectorString().size());

		if (!fileContent.has_value()) {
			_qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugError, "Couldn't read file content"));
			return false; 
		}

		const std::string fileContentString = fileContent->getString();
		
		std::optional<std::string> fileContentHash = qfEncryption::Hash::sha256(fileContentString);
		std::optional<std::string> bufferHash = qfEncryption::Hash::sha256(bufferString);

		/* Empty buffer string, no value expected */
		if (!bufferHash.has_value()) return true; 
		/* Empty content hash, checksums failed */
		if (!fileContentHash.has_value()) return false; 

		/* Checksums */
		const bool checksumsResult = (*fileContentHash == *bufferHash);

		/* Return result */
		_qfAssert(checksumsResult, "Sha256 checksums failed");
		return checksumsResult;
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