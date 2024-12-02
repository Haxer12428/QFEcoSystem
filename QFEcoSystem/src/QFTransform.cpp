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