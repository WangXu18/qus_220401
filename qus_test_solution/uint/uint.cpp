// uint.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main() {
  uint8_t test = 0x80;

  uint8_t a = static_cast<uint8_t>(0) | test;
  uint8_t b = static_cast<uint8_t>(1) | test;
  uint8_t c = static_cast<uint8_t>(2) | test;

  std::cout << test << std::endl;
  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << c << std::endl;

  return 0;
}