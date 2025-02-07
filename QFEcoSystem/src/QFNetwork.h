#pragma once
#include <curl/curl.h>
#include "QFAssert.h"
#include <filesystem>

bool _qfNetworkEasyFileDownload(const std::string& _Url, const std::filesystem::path& _Path);