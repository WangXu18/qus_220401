// windowsevent.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <windows.h>
#include <Aclapi.h>

SECURITY_ATTRIBUTES* GetSecurityDescriptor(void) {
  static BOOL bInited = FALSE;
  static SECURITY_DESCRIPTOR sd = {0};
  static SECURITY_ATTRIBUTES sa = {0};

  if (!bInited) {
    ::InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
    ::SetSecurityDescriptorDacl(&sd, TRUE, NULL, FALSE);

    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = &sd;

    bInited = TRUE;
  }

  return &sa;
}

//BOOL SetObjectToLowIntegrity(
//    HANDLE hObject,
//    SE_OBJECT_TYPE type /* = SE_KERNEL_OBJECT */) {
//  BOOL bRet = FALSE;
//  DWORD dwErr = ERROR_SUCCESS;
//  PACL pSacl = NULL;
//  BOOL fSaclPresent = FALSE;
//  BOOL fSaclDefaulted = FALSE;
//  PSECURITY_DESCRIPTOR pSD = NULL;
//
//  if (ConvertStringSecurityDescriptorToSecurityDescriptor(
//          LOW_INTEGRITY_SDDL_SACL, SDDL_REVISION_1, &pSD, NULL)) {
//    if (GetSecurityDescriptorSacl(pSD, &fSaclPresent, &pSacl,
//                                  &fSaclDefaulted)) {
//      dwErr = SetSecurityInfo(hObject, type, LABEL_SECURITY_INFORMATION, NULL,
//                              NULL, NULL, pSacl);
//
//      bRet = (ERROR_SUCCESS == dwErr);
//    }
//
//    LocalFree(pSD);
//  }
//
//  return bRet;
//}

#define CREATEEVENT(hEvent, szName)                                      \
  hEvent = ::CreateEvent(GetSecurityDescriptor(), FALSE, FALSE, szName); \
  if (NULL == hEvent)                                                    \
    break;                                                               \
  else                                                                   \
    SetObjectToLowIntegrity(hEvent);

#define EVT_1 L"6F594FDB-A0A2-4B81-A30F-6EB10E76C1BA"
#define EVT_2 L"3DFCC8E2-E792-4543-BA1B-76796093322C"

DWORD WINAPI workthread(LPVOID lpParameter) {
  aet1* ptr = (aet1*)lpParameter;
  ptr->test();
  return 0;
}

class aet1 {
 public:
  aet1() {
    init_evt();
  }

  void start() {
    m_hWordThread = ::CreateThread(NULL, 0, workthread, this, 0, NULL);
    if (NULL == m_hWordThread) {
    }
  }

  void test() {
    std::cout << "test" << std::endl;

    HANDLE szEvent[] = {m_hEvtWorkBrowserHomePageProtectA,
                        m_hEvtWorkBrowserHomepageProtectExitA};

    int nCount = sizeof(szEvent) / sizeof(HANDLE);

    for (;;) {
      DWORD dwRet = WaitForMultipleObjects(nCount, szEvent, FALSE, INFINITE);

      if ((WAIT_OBJECT_0) == dwRet) {
        m_bBrowserHomepageProtectA = TRUE;
        m_hBy3rdBrowserExitTryHomepageProtectThreadA = ::CreateThread(
            NULL, 0, ByBrowserHomepageProtectPaoFunA, this, 0, NULL);
      } else {
        break;
      }
    }

    return 0;
  }

 private:
  void init_evt() {

  }

  HANDLE m_hWordThread;
};

int main()
{
    std::cout << "Hello World!\n";
}
