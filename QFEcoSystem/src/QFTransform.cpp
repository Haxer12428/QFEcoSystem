#include "QFTransform.h"

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