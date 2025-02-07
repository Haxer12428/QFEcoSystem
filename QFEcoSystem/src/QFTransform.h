#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include "QFDefines.h"


class qfTransform {
public:
	static const std::string stringToUppercase(const std::string& _Str); 
	static const std::string stringReplaceChar(const std::string& _Str, char _What, char _With);
	static const std::vector<std::string> stringToVectorStr(const std::string& Str);
	static std::string stringReplaceString(const std::string& _Str, const std::string& _What, const std::string& _With);
	static std::string multiplyString(const std::string& _Str, size_t _Times);
	static const std::string vectorStringToString(const std::vector<std::string> &_Vec, const std::string& _EOL);

	template<typename T> static bool lookupVectorValue(const std::vector<T>& _Vec, T _Val) {
		return std::find(_Vec.begin(), _Vec.end(), _Val) != _Vec.end();
	}

	template<typename T> static std::vector<T> insertVectorToVector(const std::vector<T>& _To, const std::vector<T>& _What, const size_t& _Where) {
		_qfAssert(_To.size() >= _Where, "_Where cannot be higher than .size()");

		std::vector<T> toCopy = _To;
		auto insertAt = (toCopy.begin() + _Where);

		toCopy.insert(insertAt, _What.begin(), _What.end());

		return toCopy;
	}

	static std::string stringInsertStrAtPos(const std::string& _String, const std::string& _Element, size_t _Where) {
		const std::string sub1 = _String.substr(0, _Where);
		const std::string sub2 = _String.substr(_Where);
		
		const std::string result = (sub1 + _Element + sub2);
	
		return result;	 
	}

	static std::string stringDeletePos(const std::string& _String, size_t _Where, size_t _Len = 1) {
		const std::string sub1 = _String.substr(0, (_Where - 1));
		const std::string sub2 = _String.substr(_Where + (_Len - 1));

		return (sub1 + sub2);
	}
};