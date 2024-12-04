#include "QFEncryption.h"
#include "openssl/sha.h"


namespace qfEncryption {
	/* Sha256 */
	std::optional<std::array<unsigned char, SHA256_DIGEST_LENGTH>> Hash::sha256Raw(const std::string& _Data) {
		/* Empty data case */
		if (_Data.empty()) {
			_qfLogIf(_qfDebugLevelImportant, 
				_qfDebugLog(_qfDebugWarning, "Data is empty")
				);
			return std::nullopt;
		}
		/* Computate hash */
		std::array<unsigned char, SHA256_DIGEST_LENGTH> hash;
		SHA256(reinterpret_cast<const unsigned char*>(_Data.c_str()), _Data.size(), hash.data());
		
		/* Return casted */
		return hash;
	}

	std::optional<const std::string> Hash::sha256(const std::string& _Data) {
		auto hashedSha256Raw = sha256Raw(_Data);

		/* No value case, debug was logged in function before */
		if (!hashedSha256Raw.has_value()) {
			return std::nullopt;
		}
		/* Convert to hexa dec */
		std::ostringstream resultOSS; 

		resultOSS << std::hex << std::setfill('0');
		for (unsigned char _Char : *hashedSha256Raw) {
			resultOSS << std::setw(2) << static_cast<int>(_Char);
		}
		/* Return converted */
		return resultOSS.str();
	}
}