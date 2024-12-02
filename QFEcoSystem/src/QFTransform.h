#pragma once
#include <string>
#include <algorithm>

class qfTransform {
public:
	static const std::string stringToUppercase(const std::string& _Str); 
	static const std::string stringReplaceChar(const std::string& _Str, char _What, char _With);

};