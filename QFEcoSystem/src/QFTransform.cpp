#include "QFTransform.h"
#include <immintrin.h>  // AVX2 intrinsics
#include <bitset>
#include "QFDefines.h"

const std::string qfTransform::stringToUppercase(const std::string& _String) {
	std::string strCopy = _String;
	/* Simple std:: transformation of whole string */
	std::transform(
		strCopy.begin(), strCopy.end(), strCopy.begin(), ::toupper
		);
	return strCopy;
}

const std::string qfTransform::stringReplaceChar(const std::string& _String, char _What, char _With) {
	std::string strCopy = _String;
	
	std::replace(
		strCopy.begin(), strCopy.end(), _What, _With
		);
	return strCopy;
}

std::string qfTransform::stringReplaceString(const std::string& _String, const std::string& _What, const std::string& _With) {
	if (_What.empty() || _String.empty() || _What == _With) return _String;

	std::string result;
	result.reserve(_String.size()); // Optimistically reserve original size

	size_t lastPos = 0, pos = _String.find(_What);
	while (pos != std::string::npos) {
		result.append(_String, lastPos, pos - lastPos); // Copy before match
		result.append(_With); // Replace match
		lastPos = pos + _What.length();
		pos = _String.find(_What, lastPos);
	}

	result.append(_String, lastPos); // Append remaining part
	return result;
}

std::string qfTransform::multiplyString(const std::string& _Str, size_t _Times) {
	std::string result; 
	for (size_t _At = 0; _At < _Times; _At++) {
		result += _Str;
	};
	return result;
}

const std::vector<std::string> qfTransform::stringToVectorStr(const std::string& _Str) {
	/* Empty str case */
	if (_Str.empty()) {};

	std::stringstream ss(_Str);

	std::vector<std::string> resultBuffer;
	std::string currentBuffer; 
	/* Transform */
	while (std::getline(ss, currentBuffer)) {
		resultBuffer.push_back(currentBuffer);
	}
	return resultBuffer;
}

const std::string qfTransform::vectorStringToString(const std::vector<std::string>& _Vec, const std::string& _EOL) {
	if (_Vec.empty()) return _qfEmptyString;

	std::ostringstream output;
	for (size_t i = 0; i < _Vec.size(); ++i) {
		output << _Vec[i];
		if (i != _Vec.size() - 1) {
			output << _EOL;
		}
	}

	return output.str();
}