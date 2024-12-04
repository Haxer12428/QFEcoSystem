#pragma once
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>

class qfTransform {
public:
	static const std::string stringToUppercase(const std::string& _Str); 
	static const std::string stringReplaceChar(const std::string& _Str, char _What, char _With);
	static const std::vector<std::string> stringToVectorStr(const std::string& Str);
};