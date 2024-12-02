#include "QFSystem.h"
#include <windows.h>

/* Clipboard */
const std::string qfSystem::gClipboardData() {
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

  _qfLogIf(_qfDebugLevelRegular, _qfDebugLog(_qfDebugMessage, "success"));

  return clipboardText;
}

const bool qfSystem::sClipboardData(const std::string& _Buffer) {
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