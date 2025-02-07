#include "QFNetwork.h"
#include <fstream>

size_t _qfNetworkEasyFileDownloadInternalCallback(
	void* _Content, size_t _Size, size_t _NMemB, void* _UserP
) {
	const size_t finalSize = (_Size * _NMemB);

	std::ofstream* file = static_cast<std::ofstream*>(_UserP);
	file->write(static_cast<char*>(_Content), finalSize); 

	return finalSize;
}

bool _qfNetworkEasyFileDownload(const std::string& _Url, const std::filesystem::path& _Path) {
	/* Init curl & open file */
	CURL* curl = curl_easy_init();

	_qfAssert(curl, "Failed to initialzie curl");
	if (!curl) {
		return false; 
	}

	std::ofstream file(_Path, std::ios::binary);
	_qfAssert(file, "Could not perform open operation on file");
	if (!file) {
		return false; 
	}
	/* Setup curl params:
		URL, WRITE_CALLBACK, WRITE_WHERE(file& in this case)
	*/
	curl_easy_setopt(curl, CURLOPT_URL, _Url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _qfNetworkEasyFileDownloadInternalCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);

	/* Perform & check result */
	CURLcode result = curl_easy_perform(curl);

	_qfAssert(result == CURLE_OK, curl_easy_strerror(result));
	if (result != CURLE_OK)
		return false; 
	/* cleanup file + curl */
	curl_easy_cleanup(curl);
	file.close();

	return true; 
}