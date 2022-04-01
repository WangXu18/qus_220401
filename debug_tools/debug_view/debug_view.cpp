// debug_view.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "Windows.h"
#include <iostream>

int main() {
  while (true) {
    OutputDebugString(L"abcdabcde");
  }

  return 0;
}

