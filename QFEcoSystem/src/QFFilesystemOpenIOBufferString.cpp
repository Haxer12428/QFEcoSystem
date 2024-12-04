#include "QFFileSystem.h"

namespace qfFileSystem {
	/* Constructor */
	Open::IO::BufferString::BufferString(
		const std::vector<std::string>& _BufferVector, const FlagEOL& _EOLFlag
		) : m_BufferVector{_BufferVector}, m_EOLFlag{_EOLFlag} {}

	/* Get's -> Public */
	const std::vector<std::string>& Open::IO::BufferString::getVectorString() {
		return m_BufferVector;
	}

	Open::IO::BufferString::FlagEOL Open::IO::BufferString::getEOLFlag() {
		return m_EOLFlag;
	}

	const qfString Open::IO::BufferString::getString() {
		/* Return cached string if already calculated or buffer is empty */
		if (m_BufferVector.empty() || !m_BufferString.empty()) return m_BufferString;
		const std::string currentEOL = getEOL(m_EOLFlag);

		/* Get Str */
		for (const std::string& _Segment : m_BufferVector) {
			m_BufferString += (_Segment + currentEOL);
		}
		if (m_BufferString.empty()) return _qfEmptyString;
		/* Delete last endline of text */
		const size_t bufferStringPositionWithoutLastEOL = m_BufferString.length() - currentEOL.length();

		m_BufferString = m_BufferString.substr(
			0, bufferStringPositionWithoutLastEOL
			);

		/* Return result */
		return m_BufferString;
	}

	/* Get's -> Private */
	const qfString Open::IO::BufferString::getEOL(FlagEOL _EOLFlag) {
		return (_EOLFlag == FlagEOL::CR) ? "\r"    :
			(_EOLFlag == FlagEOL::LF)      ? "\n"    :
			(_EOLFlag == FlagEOL::CRLF)    ? "\r\n"  :
			""; 
		/* Default case */
	}
}