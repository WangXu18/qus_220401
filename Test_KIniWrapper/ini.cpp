#include "ini.h"

namespace cf {
namespace ini {
KIniWrapper::KIniWrapper() {}

KIniWrapper::~KIniWrapper() {}

BOOL KIniWrapper::LoadFileToBuffer(LPCTSTR szFileName, LPVOID* ppBuffer,
                                  DWORD& dwSize) {
  BOOL bReturn = FALSE;
  BOOL bRetCode = FALSE;
  HANDLE hFile = INVALID_HANDLE_VALUE;
  PBYTE pBuffer = NULL;

  hFile = ::CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
                       OPEN_EXISTING, 0, NULL);
  if (hFile == INVALID_HANDLE_VALUE) goto Exit0;

  DWORD dwFileSizeHigh = 0;
  DWORD dwFileSizeLow = 0;

  dwFileSizeLow = ::GetFileSize(hFile, &dwFileSizeHigh);
  if (dwFileSizeHigh || dwFileSizeLow > 2 * 1024 * 1024) goto Exit0;

  pBuffer = new BYTE[dwFileSizeLow + 2];

  DWORD dwReaded = 0;
  bRetCode = ReadFile(hFile, pBuffer, dwFileSizeLow, &dwReaded, NULL);
  if (!bRetCode || dwReaded != dwFileSizeLow) goto Exit0;

  pBuffer[dwReaded] = 0;
  pBuffer[dwReaded + 1] = 0;
  *ppBuffer = pBuffer;
  dwSize = dwFileSizeLow;

  bReturn = TRUE;
Exit0:
  if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

  return bReturn;
}

void KIniWrapper::ReleaseBuffer(LPVOID pBuffer) {
  if (pBuffer) {
    PBYTE pByteBuffer = (PBYTE)pBuffer;
    delete[] pByteBuffer;
  }
}

BOOL KIniWrapper::LoadFile(LPCTSTR szFileName,
                          int emIniEncode /* = emIniEncodingUnicode */,
                          BOOL bCreateIfNotExists /* = FALSE*/) {
  BOOL bReturn = FALSE;
  BOOL bRetCode = FALSE;
  LPBYTE pBuffer = NULL;
  DWORD dwSize = 0;
  CStringW strBuffer;

  if (bCreateIfNotExists && !::PathFileExists(szFileName)) {
    return SUCCEEDED(CreateNewFile(szFileName));
  }

  this->Clear();

  bRetCode = LoadFileToBuffer(szFileName, (LPVOID*)&pBuffer, dwSize);
  if (!bRetCode || !pBuffer /*|| dwSize < 3*/) goto Exit0;

  switch (emIniEncode) {
    case emIniEncodingAnsi:
      strBuffer = (LPCSTR)pBuffer;
      break;

    case emIniEncodingUnicode:
      strBuffer.Append((LPCWSTR)pBuffer);
      break;

    case emIniEncodingUtf8:
      strBuffer = CA2W((LPCSTR)(pBuffer), CP_UTF8);
      break;
  }

  /*if (strBuffer.IsEmpty())
          goto Exit0;*/

  strBuffer.Replace(L'\r', L'\n');
  /*bReturn = */ Parse(strBuffer);
  bReturn = TRUE;

Exit0:
  ReleaseBuffer(pBuffer);
  return bReturn;
}

BOOL KIniWrapper::Parse(LPCWSTR szString) {
  BOOL bReturn = FALSE;
  BOOL bRetCode = FALSE;
  BOOL bEnd = FALSE;
  CStringW strLine;
  LPCWSTR pOffset = szString;

  pOffset = wcschr(szString, L'[');
  if (!pOffset) goto Exit0;

  do {
    bEnd = GetLine(pOffset, strLine);
    pOffset += strLine.GetLength();

    bRetCode = ProcessLine(strLine);
    if (!bRetCode) goto Exit0;

  } while (!bEnd);

  bReturn = TRUE;

Exit0:
  return bReturn;
}

BOOL KIniWrapper::GetLine(LPCWSTR szBuffer, CStringW& strLine) {
  BOOL bEnd = FALSE;

  // strLine.Empty();

  LPCTSTR szFound = _tcschr(szBuffer, L'\n');
  if (!szFound) {
    strLine = szBuffer;
    // strLine.Append(szBuffer);
    bEnd = TRUE;
  } else {
    strLine.SetString(szBuffer, static_cast<int>(szFound - szBuffer + 1));
    // strLine.Append(szBuffer, static_cast<int>(szFound - szBuffer + 1));
  }

  return bEnd;
}

BOOL KIniWrapper::ProcessLine(CStringW& strLine) {
  BOOL bReturn = TRUE;

  strLine.Trim();
  strLine.TrimLeft(L' ');
  strLine.TrimRight(L' ');

  if (!strLine.IsEmpty()) {
    CStringW strAppName;
    CStringW strKeyName;
    CStringW strValue;

    bReturn = ParseLine(strLine, strAppName, strKeyName, strValue);
    if (!bReturn) goto Exit0;

    if (strAppName.IsEmpty() && strKeyName.IsEmpty()) {
      bReturn = FALSE;
      goto Exit0;
    }

    if (!strAppName.IsEmpty()) m_strCurrentAppName = strAppName;

    if (!strKeyName.IsEmpty()) {
      AddItem(m_strCurrentAppName, strKeyName, strValue);
    }
  }

Exit0:
  return bReturn;
}

BOOL KIniWrapper::ParseLine(CStringW& strLine, CStringW& strAppName,
                           CStringW& strKeyName, CStringW& strValue) {
  BOOL bReturn = FALSE;

  strAppName.Empty();
  strKeyName.Empty();
  strValue.Empty();

  if (strLine.GetAt(0) == L'[' &&
      strLine.GetAt(strLine.GetLength() - 1) == L']') {
    strAppName = strLine.Mid(1, strLine.GetLength() - 2);
    strAppName.TrimLeft(L' ');
    strAppName.TrimRight(L' ');

    if (strAppName.IsEmpty()) goto Exit0;
  } else {
    int nPos = strLine.Find(L'=');
    if (nPos == -1) goto Exit0;

    strKeyName = strLine.Left(nPos);
    strValue = strLine.Right(strLine.GetLength() - nPos - 1);

    strKeyName.TrimRight(L' ');
    strValue.TrimLeft(L' ');

    if (strKeyName.IsEmpty()) goto Exit0;
  }

  bReturn = TRUE;

Exit0:
  return bReturn;
}

BOOL KIniWrapper::AddItem(CStringW& strAppName, CStringW& strKeyName,
                         LPCWSTR szValue) {
  std::map<CStringW, std::map<CStringW, CStringW>>::iterator iterApp;
  std::map<CStringW, CStringW>::iterator iterKey;

  strAppName.MakeLower();
  strKeyName.MakeLower();

  iterApp = m_mapIniData.find(strAppName);
  if (iterApp != m_mapIniData.end()) {
    std::map<CStringW, CStringW>& mapKeys = iterApp->second;

    iterKey = mapKeys.find(strKeyName);
    if (iterKey != mapKeys.end()) {
      iterKey->second = szValue;
    } else {
      mapKeys.insert(std::make_pair(strKeyName, szValue));
    }
  } else {
    std::map<CStringW, CStringW> mapKeys;
    mapKeys.insert(std::make_pair(strKeyName, szValue));
    m_mapIniData.insert(std::make_pair(strAppName, mapKeys));
  }

  return TRUE;
}

void KIniWrapper::Clear() { m_mapIniData.clear(); }

int KIniWrapper::Read(LPCWSTR szAppName, LPCWSTR szKeyName, int nDefault) {
  int nReturn = nDefault;
  CStringW strAppName(szAppName);
  CStringW strKeyName(szKeyName);
  std::map<CStringW, CStringW>::iterator iterKey;
  std::map<CStringW, std::map<CStringW, CStringW>>::iterator iterApp;

  strAppName.MakeLower();
  strKeyName.MakeLower();

  iterApp = m_mapIniData.find(strAppName);
  if (iterApp != m_mapIniData.end()) {
    std::map<CStringW, CStringW>& mapKeys = iterApp->second;

    iterKey = mapKeys.find(strKeyName);
    if (iterKey != mapKeys.end()) {
      nReturn = _wtoi(iterKey->second);
    }
  }

  return nReturn;
}

BOOL KIniWrapper::Write(LPCWSTR szAppName, LPCWSTR szKeyName, int nValue) {
  CStringW strAppName(szAppName);
  CStringW strKeyName(szKeyName);
  CStringW strValue;

  strValue.Format(_T("%d"), nValue);

  return AddItem(strAppName, strKeyName, strValue);
}

LPCWSTR KIniWrapper::Read(LPCWSTR szAppName, LPCWSTR szKeyName,
                         LPCWSTR szDefault) {
  LPCWSTR lpszReturn = szDefault;
  CStringW strAppName(szAppName);
  CStringW strKeyName(szKeyName);
  std::map<CStringW, CStringW>::iterator iterKey;
  std::map<CStringW, std::map<CStringW, CStringW>>::iterator iterApp;

  strAppName.MakeLower();
  strKeyName.MakeLower();

  iterApp = m_mapIniData.find(strAppName);
  if (iterApp != m_mapIniData.end()) {
    std::map<CStringW, CStringW>& mapKeys = iterApp->second;

    iterKey = mapKeys.find(strKeyName);
    if (iterKey != mapKeys.end()) {
      lpszReturn = (LPCWSTR)iterKey->second;
    }
  }

  return lpszReturn;
}

BOOL KIniWrapper::Write(LPCWSTR szAppName, LPCWSTR szKeyName, LPCWSTR szValue) {
  CStringW strAppName(szAppName);
  CStringW strKeyName(szKeyName);

  return AddItem(strAppName, strKeyName, szValue);
}

const std::map<CStringW, std::map<CStringW, CStringW>>& KIniWrapper::ReadAll(
    void) {
  return m_mapIniData;
}

BOOL KIniWrapper::SaveFile(LPCTSTR szFileName, int emIniEncode) {
  BOOL bReturn = FALSE;
  BOOL bRetCode = FALSE;
  HANDLE hFile = INVALID_HANDLE_VALUE;
  DWORD dwWrited = 0;
  CStringW strBuffer;
  CStringA strBufferA;
  PBYTE pBuffer = NULL;
  DWORD dwBufferSize = 0;

  hFile = ::CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL,
                       CREATE_ALWAYS, 0, NULL);
  if (hFile == INVALID_HANDLE_VALUE) goto Exit0;

  ToString(strBuffer);

  switch (emIniEncode) {
    case emIniEncodingAnsi: {
      USES_CONVERSION;
      strBufferA = W2A(strBuffer);
      pBuffer = (PBYTE)(LPCSTR)strBufferA;
      dwBufferSize = strBufferA.GetLength();
    } break;

    case emIniEncodingUtf8: {
      BYTE szUtf8Header[3] = {0xEF, 0xBB, 0xBF};
      bRetCode = WriteFile(hFile, szUtf8Header, 3, &dwWrited, NULL);
      if (!bRetCode || dwWrited != 3) goto Exit0;

      USES_CONVERSION;
      strBufferA = W2A_CP(strBuffer, CP_UTF8);
      pBuffer = (PBYTE)(LPCSTR)strBufferA;
      dwBufferSize = strBufferA.GetLength();
    } break;
    case emIniEncodingUnicode: {
      BYTE szUnicodeHeader[2] = {0xFF, 0xFE};
      bRetCode = WriteFile(hFile, szUnicodeHeader, 2, &dwWrited, NULL);
      if (!bRetCode || dwWrited != 2) goto Exit0;

      pBuffer = (PBYTE)(LPCWSTR)strBuffer;
      dwBufferSize = strBuffer.GetLength() * sizeof(WCHAR);
    } break;
  }

  bRetCode = WriteFile(hFile, pBuffer, dwBufferSize, &dwWrited, NULL);
  if (!bRetCode || dwWrited != dwBufferSize) goto Exit0;

  bReturn = TRUE;
Exit0:
  if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);

  return bReturn;
}

BOOL KIniWrapper::ToString(CStringW& strBuffer) {
  std::map<CStringW, std::map<CStringW, CStringW>>::const_iterator iterApp;
  std::map<CStringW, CStringW>::const_iterator iterKey;

  strBuffer.Empty();
  for (iterApp = m_mapIniData.begin(); iterApp != m_mapIniData.end();
       iterApp++) {
    const std::map<CStringW, CStringW>& mapKeys = iterApp->second;

    strBuffer.AppendChar(L'[');
    strBuffer += iterApp->first;
    strBuffer.AppendChar(L']');
    strBuffer.Append(L"\r\n");
    for (iterKey = mapKeys.begin(); iterKey != mapKeys.end(); iterKey++) {
      strBuffer += iterKey->first;
      strBuffer.AppendChar(L'=');
      strBuffer += iterKey->second;
      strBuffer.Append(L"\r\n");
    }
  }

  return TRUE;
}

BOOL KIniWrapper::HasApp(LPCWSTR lpszApp) const {
  CString strNoCaseAppName = lpszApp;
  strNoCaseAppName.MakeLower();
  return m_mapIniData.find(strNoCaseAppName) != m_mapIniData.end();
}

DWORD KIniWrapper::Read(LPCTSTR szAppName, LPCTSTR szKeyName, LPBYTE pBuffer,
                       DWORD dwSize) {
  DWORD dwRetSize = 0;
  CStringW strAppName(szAppName);
  CStringW strKeyName(szKeyName);
  std::map<CStringW, CStringW>::iterator iterKey;
  std::map<CStringW, std::map<CStringW, CStringW>>::iterator iterApp;

  strAppName.MakeLower();
  strKeyName.MakeLower();

  iterApp = m_mapIniData.find(strAppName);
  if (iterApp != m_mapIniData.end()) {
    std::map<CStringW, CStringW>& mapKeys = iterApp->second;

    iterKey = mapKeys.find(strKeyName);
    if (iterKey != mapKeys.end()) {
      CStringW& strBinStr = iterKey->second;
      dwRetSize = strBinStr.GetLength() / 2;
      if (dwRetSize <= dwSize) {
        if (!StringToBinary(strBinStr, pBuffer, dwRetSize)) dwRetSize = 0;
      }
    }
  }

  return dwRetSize;
}

BOOL KIniWrapper::Write(LPCTSTR szAppName, LPCTSTR szKeyName, LPBYTE pBuffer,
                       DWORD dwSize) {
  CStringW strAppName(szAppName);
  CStringW strKeyName(szKeyName);
  CStringW strValue;

  BinaryToString(pBuffer, dwSize, strValue);

  return AddItem(strAppName, strKeyName, strValue);
}

BOOL KIniWrapper::BinaryToString(LPBYTE pBuffer, DWORD dwSize,
                                CStringW& strBinStr) {
  WCHAR szBuffer[5];

  strBinStr.Empty();

  for (DWORD i = 0; i < dwSize; i++) {
    swprintf(szBuffer, L"%02x", pBuffer[i]);
    strBinStr += szBuffer;
  }

  return TRUE;
}

BOOL KIniWrapper::StringToBinary(CStringW& strBinStr, LPBYTE pBuffer,
                                DWORD dwSize) {
  BOOL bReturn = FALSE;

  if (strBinStr.GetLength() % 2 != 0 || strBinStr.GetLength() / 2 > (int)dwSize)
    goto Exit0;

  LPCTSTR pString = strBinStr;
  BYTE btTemp;

  for (int i = 0; i < strBinStr.GetLength(); i++) {
    if (pString[i] >= L'0' && pString[i] <= L'9')
      btTemp = static_cast<BYTE>(pString[i] - L'0');
    else if (pString[i] >= L'a' && pString[i] <= L'f')
      btTemp = static_cast<BYTE>(pString[i] - L'a' + 10);
    else if (pString[i] >= L'A' && pString[i] <= L'F')
      btTemp = static_cast<BYTE>(pString[i] - L'A' + 10);
    else
      goto Exit0;

    pBuffer[i / 2] = btTemp << 4;

    i++;
    if (pString[i] >= L'0' && pString[i] <= L'9')
      btTemp = static_cast<BYTE>(pString[i] - L'0');
    else if (pString[i] >= L'a' && pString[i] <= L'f')
      btTemp = static_cast<BYTE>(pString[i] - L'a' + 10);
    else if (pString[i] >= L'A' && pString[i] <= L'F')
      btTemp = static_cast<BYTE>(pString[i] - L'A' + 10);
    else
      goto Exit0;

    // pBuffer[i / 2] += btTemp;
    pBuffer[i / 2] = pBuffer[i / 2] + btTemp;
  }

  bReturn = TRUE;
Exit0:
  return bReturn;
}

HRESULT KIniWrapper::CreateNewFile(LPCTSTR szFileName) {
  if (NULL == szFileName) {
    return E_INVALIDARG;
  }

  std::wstring strSrcPath(szFileName);
  std::wstring::size_type stIndex = strSrcPath.rfind(L'\\');
  if (std::wstring::npos != stIndex) {
    int nRet = ::SHCreateDirectoryExW(
        NULL, strSrcPath.substr(0, stIndex).c_str(), NULL);
    if (ERROR_SUCCESS != nRet && ERROR_FILE_EXISTS != nRet &&
        ERROR_ALREADY_EXISTS != nRet) {
      return HRESULT_FROM_WIN32(nRet);
    }

    HANDLE hFile =
        ::CreateFileW(strSrcPath.c_str(), GENERIC_READ | GENERIC_WRITE,
                      FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_NEW,
                      FILE_ATTRIBUTE_NORMAL, NULL);
    if (INVALID_HANDLE_VALUE == hFile) {
      return HRESULT_FROM_WIN32(::GetLastError());
    } else {
      CloseHandle(hFile);
      return S_OK;
    }
  } else {
    return E_INVALIDARG;
  }
}

BOOL KIniWrapper::ReadSection(const CStringW& strSecName,
                             std::map<CStringW, CStringW>& mapOut) {
  std::map<CStringW, std::map<CStringW, CStringW>>::const_iterator iterMap;
  CStringW strNoCaseSecName = strSecName;
  strNoCaseSecName.MakeLower();
  iterMap = m_mapIniData.find(strNoCaseSecName);
  if (m_mapIniData.end() != iterMap) {
    mapOut = iterMap->second;
    return TRUE;
  }

  return FALSE;
}

void KIniWrapper::EraseSection(LPCTSTR szAppName) {
  CString strNoCaseAppName = szAppName;
  strNoCaseAppName.MakeLower();
  std::map<CStringW, std::map<CStringW, CStringW>>::const_iterator iterMap =
      m_mapIniData.find(strNoCaseAppName);
  if (iterMap == m_mapIniData.end()) {
    return;
  }

  m_mapIniData.erase(strNoCaseAppName);
}

void KIniWrapper::EraseKey(LPCTSTR szAppName, LPCTSTR szkeyName) {
  if (NULL == szAppName || NULL == szkeyName) {
    return;
  }

  CString strNoCaseAppName = szAppName;
  strNoCaseAppName.MakeLower();
  CString strNoCaseKeyName = szkeyName;
  strNoCaseKeyName.MakeLower();
  std::map<CStringW, std::map<CStringW, CStringW>>::iterator iterLevelOne =
      m_mapIniData.find(strNoCaseAppName);
  if (iterLevelOne == m_mapIniData.end()) {
    return;
  }

  std::map<CStringW, CStringW>::iterator iterLevelTwo =
      iterLevelOne->second.find(strNoCaseKeyName);
  if (iterLevelTwo == iterLevelOne->second.end()) {
    return;
  }

  iterLevelOne->second.erase(iterLevelTwo);
  if (iterLevelOne->second.empty()) {
    m_mapIniData.erase(iterLevelOne);
  }
}
}  // namespace ini
}  // namespace cf
