#pragma once
#include <iostream>
#include <windows.h>
#include <chrono>

void set_color() {
  HANDLE handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(handle, FOREGROUND_INTENSITY | FOREGROUND_RED);
}

void clear_color() {
  HANDLE handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(handle, 7);
}

void print_duration(std::chrono::steady_clock::time_point start,
                    std::chrono::steady_clock::time_point end) {
  /*auto duration =
      std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
  auto res = double(duration.count()) * std::chrono::microseconds::period::num /
             std::chrono::microseconds::period::den;*/
  //auto res = std::chrono::duration<double, std::micro>(end-start).count();
  auto res = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
  std::cout << "BubbleSort 花费时间   ";
  set_color();
  std::cout << res;
  clear_color();
  std::cout << "   微秒。" << std::endl;
}