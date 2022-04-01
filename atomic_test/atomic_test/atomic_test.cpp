//// atomic_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
////
//
//#include <iostream>
//#include <atomic>
//#include <vector>
//#include <thread>
//
//std::atomic<bool> ready(false);
//std::atomic_flag winner = ATOMIC_FLAG_INIT;
//
//void test(int i) {
//  while (!ready);
//  for (int i = 0; i < 1000000000; i++);
//  if (!winner.test_and_set()) {
//    std::cout << "winner is : " << i << std::endl;
//  }
//}
//
//int main()
//{
//  std::vector<std::thread> theads;
//  for (int i = 0; i < 10; i++) {
//    theads.push_back(std::thread(test, i));
//  }
//
//  ready = true;
//
//  for (int i = 0; i < 10; i++) {
//    theads[i].join();
//  }
//
//  return 0;
//}
//


//#include <iostream>
//#include <atomic>
//#include <vector>
//#include <thread>
//#include <sstream>
//
//std::atomic<int> foo(0);
//
//void set_foo(int x)
//{
//  foo = x;
//}
//
//void print_foo()
//{
//  while (foo == 0)
//  {
//    std::this_thread::yield();
//  }
//  std::cout << "x: " << foo << std::endl;
//}
//int main()
//{
//  std::thread print_th(print_foo);
//  std::thread set_th(set_foo, 10);
//  print_th.join();
//  set_th.join();
//  return 0;
//}

#include <iostream>
#include <cassert>
#include <atomic>
#include <vector>
//#include <unistd.h>
#include <synchapi.h>
#include <thread>
#include <sstream>

std::atomic<int> foo(0);
std::atomic_flag lock = ATOMIC_FLAG_INIT;

void add_foo()
{
  while (1)
  {
    foo++;
    // foo = foo + 1;
    while (lock.test_and_set());
    std::cout << "add: " << foo << std::endl;
    lock.clear();
    Sleep(1000);
  }
}

void sub_foo()
{
  while (1)
  {
    foo--;
    // foo = foo - 1;
    while (lock.test_and_set());
    std::cout << "sub: " << foo << std::endl;
    lock.clear();
    Sleep(1000);
  }
}
int main()
{
  std::thread th2 = std::thread(add_foo);
  std::thread th1 = std::thread(sub_foo);
  th1.join();
  th2.join();
  return 0;
}