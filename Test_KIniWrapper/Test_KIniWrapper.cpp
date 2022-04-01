// Test_KIniWrapper.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "ini.h"

int main()
{
  cf::ini::KIniWrapper iniWarp;
  iniWarp.Parse(L"[test] aet=2");
  DWORD res = iniWarp.Read(L"test", L"aet", 0);

  std::cout << res << std::endl;

  return 0;
}
