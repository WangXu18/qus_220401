// creater.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "gc1.h"
#include "dl.h"

int main()
{


  // sg1-3
  auto singleton = sg1::singleton::getinstance();
  if (singleton) {
	auto tmp = sg1::singleton::getinstance();
  }
  auto temp = sg2::singleton::getinstance();
  auto tmp = sg2::singleton::getinstance();
  auto res = sg3::singleton::getinstance();
  auto a = sg::instance();

  // gc1
  /*gc1::manager_impl mng;
  auto test = mng.create(gc1::test_type::enum_test_type_a);
  if (test) {
	test->create();
  }

  test = mng.create(gc1::test_type::enum_test_type_b);
  if (test) {
	test->create();
  }

  gc1::manager_impl_test mng_t;
  test = mng_t.create_a();
  if (test) {
	test->create();
  }

  test = mng_t.create_b();
  if (test) {
	test->create();
  }*/

  return 0;
}

