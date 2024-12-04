#pragma once
#include <string>
#include <optional>
#include <openssl/sha.h>
#include "QFDebug.h"
#include <ostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <array>

namespace qfEncryption {
	class Hash {
	public:
		static std::optional<std::array<unsigned char, SHA256_DIGEST_LENGTH>> sha256Raw(const std::string& _Data);
		static std::optional<const std::string> sha256(const std::string& _Data);
	};
};