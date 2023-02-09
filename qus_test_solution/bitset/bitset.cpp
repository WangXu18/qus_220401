#include <iostream>
#include <bitset>

int main() {
  std::bitset<32> test(123);
  std::cout << test << std::endl;
  std::cout << test.count() << std::endl;

  if (test.any()) {
    std::cout << "true binary bit" << std::endl;
  }

  std::cout << test.size() << std::endl;
  std::cout << test.to_ulong() << std::endl;
  std::cout << test.to_ullong() << std::endl;
  std::cout << test.to_string() << std::endl;
  std::cout << test.to_string('a', 'b') << std::endl;

  /*std::bitset<64> test("0001");
  std::cout << test.count() << std::endl;
  std::cout << test.size() << std::endl;
  auto res = test.test(0);
  if (res) {
    std::cout << "true" << std::endl;
  } else {
    std::cout << "false" << std::endl;
  }

  test = test.flip();
  std::cout << "按位取反之后：" << std::endl;
  std::cout << test.count() << std::endl;
  std::cout << test.size() << std::endl;
  auto res1 = test.test(0);
  if (res1) {
    std::cout << "true" << std::endl;
  } else {
    std::cout << "false" << std::endl;
  }*/

  return 0;
}