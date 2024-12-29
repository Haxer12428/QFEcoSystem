#include "QFSystem.h"
#include <windows.h>

/* Clipboard */
const std::string qfSystem::getClipboardData() {
  if (!OpenClipboard(nullptr)) {
    _qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugWarning, "Could not open clipboard"));
    return _qfEmptyString;
  }

  struct ClipboardGuard { ~ClipboardGuard() { CloseClipboard(); } } clipboardGuard;

  /* Get clipboard data */
  HANDLE handleData = GetClipboardData(CF_TEXT);
  if (handleData == nullptr) {
    _qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugWarning, "Could not get clipboard data"));
    return _qfEmptyString;
  }

  /* Lock data & get text ptr */
  char* pszText = static_cast<char*>(GlobalLock(handleData));

  if (pszText == nullptr) {
    _qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugWarning, "Could not lock memory"));
    return _qfEmptyString;
  }
  /* Copy text from clipboard & release locks */
  const std::string clipboardText = pszText;
  GlobalUnlock(handleData);

  

  return clipboardText;
}

const bool qfSystem::setClipboardData(const std::string& _Buffer) {
  /* Open & Empty */
  if (!OpenClipboard(nullptr)) {
    _qfDebugLog(_qfDebugWarning, "could not open clipboard");
    return false; 
  }

  struct ClipboardGuard { ~ClipboardGuard() { CloseClipboard(); } } clipboardGuard;

  const size_t bufferSizeFixed = (_Buffer.size() + 1);

  if (!EmptyClipboard()) {
    _qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugWarning, "Could not empty clipboard"));

    return false;
  }

  /* Allocate memory for buffer */
  HGLOBAL handleGlobal = GlobalAlloc(GMEM_MOVEABLE, bufferSizeFixed);

  if (handleGlobal == nullptr) {
    _qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugWarning, "Could not allocate memory"));

    return false;
  }

  char* pGlobal = static_cast<char*>(GlobalLock(handleGlobal));

  if (pGlobal == nullptr) {
    _qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugWarning, "Could not lock memory"));

    return false;
  }

  /* Write data */
  memcpy(pGlobal, _Buffer.c_str(), bufferSizeFixed);
  /* Unlock */
  GlobalUnlock(handleGlobal);

  /* Place the handle on the clipboard for CF_TEXT format */
  if (SetClipboardData(CF_TEXT, handleGlobal) == nullptr) {
    _qfLogIf(_qfDebugLevelCritical, _qfDebugLog(_qfDebugWarning, "Could not place handle on clipboard"));

    GlobalFree(handleGlobal);
    return false;
  }
  /* Close: RAII */

  _qfLogIf(_qfDebugLevelRegular, _qfDebugLog(_qfDebugMessage, "success"));

  return true;
}

std::vector<char> qfSystem::getImgDataFromEmbeddedResource(const std::string& _ResourceName) {

  HRSRC hResInfo = FindResourceW(NULL,
    std::wstring(_ResourceName.begin(), _ResourceName.end()).c_str(),
    RT_RCDATA
  ); /* Binary type */

  _qfAssert(hResInfo != NULL, "Could not find resource");
  if (hResInfo == NULL) 
    return {};

  DWORD resourceSize = SizeofResource(NULL, hResInfo);

  if (resourceSize == 0)
    return {};

  /* Load resource into memory */
  HGLOBAL resourceHandler = LoadResource(NULL, hResInfo);

  _qfAssert(resourceHandler != NULL, "Failed to load resource");
  if (resourceHandler == NULL)
    return {};
  
  /* Lock resource and extract data from it */
  const char* resourceData = static_cast<const char*>(LockResource(resourceHandler));

  /* Get buffer into a vector */
  std::vector<char> resourceBuffer(resourceData, resourceData + resourceSize);

  return resourceBuffer;
}