// test_230202.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <initializer_list>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <tuple>
#include <functional>
#include <numeric>
#include <mutex>
#include <future>
#include <thread>

class test1 {
public:
  virtual void test() {
	std::cout << "this is a test function" << std::endl;
  }
  int a_{10};
};

void print_mutil_param(int err_code, std::initializer_list<std::string> sli) {
  std::cout << "error code is : " << err_code << ". Other info is : ";
  for (auto& parm : sli) {
	std::cout << std::setw(8) << parm << " ";
  }
  std::cout << std::endl;
}

class CSB;
class CSA {
public:
  std::shared_ptr<CSB> ptr_;
  ~CSA() {
	std::cout << "csa is deleted" << std::endl;
  }
};

class CSB {
public:
  std::shared_ptr<CSA> ptr_;
  ~CSB() {
	std::cout << "csb is deleted" << std::endl;
  }
};

class CTestRef {
public:
  int Add1(int a, int b)& {
	return a + b;
  }

  int Add2(int a, int b)&& {
	return a + b;
  }
};

class CMoveTest {
public:
  CMoveTest() {
	std::cout << "constructor" << std::endl;
  }

  CMoveTest(const CMoveTest& tmp) {
	std::cout << "copy constructor" << std::endl;
  }

  CMoveTest(const CMoveTest&& tmp) {
	std::cout << "move constructor" << std::endl;
  }
};

template<typename...Args>
void change_args_test(Args...args) {
  auto size = sizeof...(args);
  std::cout << sizeof...(Args) << std::endl;
  std::cout << sizeof...(args) << std::endl;

  auto tp = std::forward_as_tuple(args...);
}

class base1 {
public:
  base1() = default;
  base1(const std::string& tmp) {}
};
class base2 {
public:
  base2() = default;
  base2(const std::string& tmp) {}
};
class dd : public base1, public base2 {
public:
  dd() = default;
  using base1::base1;
  using base2::base2;

  dd(const std::string& str) : base1(str),base2(str) {}
  [[deprecated]] void test() {}
};

class CVarTest {
public:
  static int i;
};

class CVarTest1 {
public:
#if _HAS_CXX17
  static inline int i = 0;
#endif
};

int future_test() {
  std::cout << "future_test before sleep 1 min" << std::endl;
  std::this_thread::sleep_for(std::chrono::duration<long long>(60));
  std::cout << "future_test after sleep 1 min" << std::endl;
  return 10;
}

class basee {
public:
  virtual void test() {}
};

class basee1 {
public:
  virtual void test1() {}
};

class drii : public basee {
public:
  void te() {}
  virtual void dd(int i) {}
};

class drii1 : public basee, public basee1 {
public:
  void te1() {}
  virtual void dd1(int i) {}
};

class cvt1 {};
class cvt2 {
public:
  int a;
};
class cvt3 {
  int a;
  virtual void f() {}
};

template<class T>
class cvt_helper : T {
  virtual void test() {}
};

template<class T>
bool has_virtualfunc(T&) {
  return sizeof(T) == sizeof(cvt_helper<T>);
}

int main(int argc, char* argv[]) {

  int i = 0;
  // 判断类有没有虚函数
  /*cvt1 t1;
  cvt2 t2;
  cvt3 t3;
  std::cout << has_virtualfunc(t1) << std::endl;
  std::cout << has_virtualfunc(t2) << std::endl;
  std::cout << has_virtualfunc(t3) << std::endl;*/
  
  //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  /*basee dr;
  drii dr1;*/

  // future
  /*auto f = std::async(std::launch::async,future_test);
  std::cout << "main before sleep 10 s" << std::endl;
  std::this_thread::sleep_for(std::chrono::duration<long long>(10));
  std::cout << "main after sleep 10 s" << std::endl;
  auto res = f.get();
  std::cout << res << std::endl;*/

  // mutex
  /*std::mutex  mt;
  std::lock_guard<std::mutex> gd(mt);*/

  // string c_str data
  /*std::string test{ "1231adada" };
  auto t1 = test.c_str();
  auto t2 = test.data();
  std::cout << t1 << std::endl;
  std::cout << t2 << std::endl;
  std::cout << sizeof(t1) << std::endl;
  std::cout << sizeof(t2) << std::endl;*/

  // lambda 初始化变量
  /*int x = 1;
  auto y = [&r = x, x = x*2]() mutable {
	std::cout << x << std::endl;
	std::cout << r << std::endl;
	x += 2;
	std::cout << x << std::endl;
	r += 2;
	std::cout << r << std::endl;
  };
  y();
  std::cout << x << std::endl;*/

  // lambda 捕获用 move
  /*std::unique_ptr<char> a(new char);
  *a = 'a';
  auto lambd = [capture = std::move(a)](char) {
	*capture = 'b';
	std::cout << *capture << std::endl;
  };
  lambd('a');*/

  // accumulate
  /*std::vector<int> _Vec_int = { 1,2,3,4 };
  std::vector<std::string> _Vec_string = { "red","blue","yellow" };
  auto add = [](auto lhs, auto rhs) { return lhs - rhs; };
  std::cout << std::accumulate(_Vec_int.begin(), _Vec_int.end(), 100, add) << std::endl;*/
  //std::cout << std::accumulate(_Vec_string.begin(), _Vec_string.end(), std::string(), add1) << std::endl;
  
  // mem_fn
  //auto f = std::mem_fn(&std::string::empty);
  
  // 多重继承
  //dd d;

  // 可变模板参数
  //change_args_test(1, "hello", 2.3, 'a');

  // std::move
  // 先把传给它的参数转换成一个模板类型特化的右值引用的对象
  // 然后用static_cast显示把这个对象转换为remove_reference_t模板特化类型的右值引用，再return出去
  /*CMoveTest refTest;
  CMoveTest refTest1 = std::move(refTest);*/

  // std::forward
  // 先把传给它的参数隐式转换为一个remove_reference_t模板特化的引用类型的对象
  // 然后把这个对象用static_cast显示转化为模板类型的右值引用类型

  // 引用限定
  /*CTestRef ref;
  int a = 1, b = 2;
  std::cout << ref.Add1(a, b) << std::endl;
  std::cout << std::move(ref).Add2(a, b) << std::endl;*/

  //// 右值引用
  //int&& a = 10;
  //std::cout << &a << std::endl;
  //int&& b = static_cast<int&&>(a);
  //std::cout << &b << std::endl;
  //int&& b1 = std::move(a);
  //std::cout << &b1 << std::endl;

  //weak_ptr shared_ptr
  // good↓
  /*std::shared_ptr<int> pA{ new int{999} };
  std::cout << pA.use_count() << std::endl;
  std::shared_ptr<int> pB = pA;
  std::cout << pA.use_count() << std::endl;
  pA.reset();
  std::cout << pA.use_count() << std::endl;*/
  // bad↓
  void* addr;
  {
	std::shared_ptr<CSA> pCSA{ new CSA };
	std::shared_ptr<CSB> pCSB{ new CSB };
	std::cout << "first--->" << std::endl;
	std::cout << pCSA.use_count() << std::endl;
	std::cout << pCSB.use_count() << std::endl;
	pCSA->ptr_ = pCSB;
	std::cout << "second--->" << std::endl;
	std::cout << pCSA.use_count() << std::endl;
	std::cout << pCSB.use_count() << std::endl;
	pCSB->ptr_ = pCSA;
	std::cout << "third--->" << std::endl;
	std::cout << pCSA.use_count() << std::endl;
	std::cout << pCSB.use_count() << std::endl;
	std::cout << "delete pCSA" << std::endl;
	addr = pCSA.get();
  }
  std::cout << ((CSA*)addr)->ptr_ << std::endl;

  // lambda
  /*int a = 0;
  int b = 1;
  auto f = [](int a, int b)->int { return a + b; };
  auto g = [a, b]() { return a + b; };
  auto g1 = [&]() { a = 1; b = 2; return a + b; };
  auto h = [](int i) { 
	if (i < 0) { 
	  return -i; } 
	else 
	  return i; 
  };
  std::cout << f(1, 2) << std::endl;
  std::cout << g1() << std::endl;
  std::vector<int> vec{ 1,2,-1,-2,3,4,5,-3,-5,6 };
  std::transform(vec.begin(), vec.end(), vec.begin(), h);*/


  // initializer_list
  /*print_mutil_param(11, { "aaa", "bbb" });
  print_mutil_param(22, { "aa", "bb", "cc" });
  print_mutil_param(33, { "aabb", "110", "333ssss" });*/
  
  // sizeof
  //std::cout << sizeof(test1) << std::endl;

  // byte length
  /*std::cout << sizeof(char) << std::endl;
  std::cout << sizeof(short) << std::endl;
  std::cout << sizeof(int) << std::endl;
  std::cout << sizeof(long) << std::endl;
  std::cout << sizeof(long long) << std::endl;
  std::cout << sizeof(float) << std::endl;
  std::cout << sizeof(double) << std::endl;
  std::cout << sizeof(long double) << std::endl;*/

  // static_cast 转void*
  /*int a = 19;
  int* b = &a;
  auto c = static_cast<void*>(b);
  std::cout << b << "   " << c << std::endl;*/

  // dynamic_cast
  /*test1 t1;
  auto pt1 = dynamic_cast<void*>(&t1);
  std::cout << pt1 << std::endl;
  std::cout << "force change pt1: " << ((test1*)pt1)->a_ << std::endl;
  ((test1*)pt1)->test();*/


  // reinterpret_cast question
  /*int a = 0x111111;
  std::cout << "a's value is:" << a << std::endl;
  auto a_test = reinterpret_cast<char*>(&a);
  std::cout << "a's address is :" << &a << std::endl;
  std::cout << "a_test's address is :" << &a_test << std::endl;
  std::cout << "a's value is:" << a_test << std::endl;*/

  // 底层const
  /*int test = 10;
  const int* a = &test;

  std::cout << *a << std::endl;
  int test1 = 20;
  a = &test1;
  std::cout << *a << std::endl;*/

  // 顶层const
  /*int test2 = 30;
  int* const b = &test2;
  std::cout << "*b is: " <<  *b << std::endl;
  *b = 40;
  std::cout << "*b is: " << *b << std::endl;*/


  return 0;
}

