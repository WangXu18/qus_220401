#include <iostream>
#include <initializer_list>

int main() {
  auto li = { 1, 2, 3, 4};
  auto li1 = { "a", "e", "t" };

  auto beg = li.begin();
  while (beg != li.end()) {
    std::cout << *beg << std::endl;
    beg++;
  }

  std::cout << "---------------------" << std::endl;

  auto beg1 = li1.begin();
  while (beg1 != li1.end()) {
    std::cout << *beg1 << std::endl;
    beg1++;
  }

  return 0;
}