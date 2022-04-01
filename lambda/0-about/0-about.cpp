#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <thread>

// 在数理逻辑或计算机科学领域中，lambda被用来表达一种匿名函数
// 这种匿名函数代表了一种所谓λ演算。

// 语法：
// []() mutable -> return_type { /*do someting*/ }
// 
// 最简洁的lambda表达式：[]{};
// 
// [] 捕获列表
// () 参数列表
// mutable
//    默认情况下，lambda总是一个const函数，含义应该和如下面的函数get_a一样，函数后面加了const，表示改函数不会修改类成员变量
//    但是加了mutable，就可以对类成员变量进行操作了。
//    没有加这个关键字的时候，默认是捕获行为，加了这个之后，参数列表就不允许忽略了
// 返回类型，可以省略，编译器会进行类型返回类型推导
// 函数体 和普通函数的函数体类似，可以使用传进来的参数，还能使用捕获到的变量。

// 可调用对象:
// 1. 函数
// 2. 函数指针
// 3. lambda表达式
// 4. bind创建的对象
// 5. 重载了函数调用操作符()的类
// 对于这些可调用对象，可以用function类模板进行结合使用，如函数function_test

// 1. lambda函数在C++11标准中是默认内联的。

int add(int a, int b) {
  return a + b;
}

class CTest {
 public:
  int get_a() const { return a_; }
  //int get_a_err() const { a_ = 1; return a_; }

  int get_b() const { b_ = 1; return b_; }

  void function_test() {
    std::function<int(int, int)> f0 = add;
    std::function<int(int, int)> f1 = [](int i, int j) { return i*j; };
    std::cout << f0(1,2) << std::endl;
    std::cout << f1(1,2) << std::endl;
  }

 private:
  int a_{0};
  mutable int b_{0};
};

// 值捕获和引用捕获
// 1.
// 对于值捕获的方式来讲，传递的值在lambda定义的时候就是确定的了，值传递意味着位逐次拷贝
// 2. 对于引用捕获的方式而言，捕获的值是在lambda调用的时候确定的。

class CTest1 {
 public:
  void test() {
    int a = 0;

    auto test_value = [=]() {
      return a + 1;
    };
    /*auto test_value = [=, &a]() {
      return a + 1;
    };*/

    auto test_ref = [&]() {
      return a + 1;
    };

    std::cout << test_value() << std::endl;
    std::cout << test_ref() << std::endl;
    a++;
    std::cout << test_value() << std::endl;
    std::cout << test_ref() << std::endl;
  }
};

// 总结捕获规则:
// [] 空捕获列表，lambda不能使用所在函数中的变量
// [names] names是一个逗号分隔的名字列表，都是lambda所在函数的局部变量
// [&] 隐式引用捕获方式，lambda中所使用的和来自所占函数的实体都采用引用的方式使用
// [=] 隐式值捕获方式，lambda体将拷贝所使用的来自所在函数的实体的值
// [&, identifier_list] identifier_list显式列出来的变量采用值捕获的方式，其他隐式捕获的变量都采用引用捕获的方式
//                      identifier_list的名字前面不能使用&
// [=, identifier_list] identifier_list显示列出来的采用引用捕获的方式，其他隐式捕获的变量都采用值捕获的方式
//                      identifier_list中的名字不能包括this，且这些名字必须使用&（上面注释的test_value引用捕获）

class CTest2 {
 public:
  void test() {
    int i = 0;
    int j = 1;
    std::string str;

    auto a = [&, i]() mutable{
      // 以值捕获的方式显式捕获i,只能用它的值,而不能修改它
      i++;

      // i是值捕获，j,str是引用捕获
      /*j += 2;
      str = "age";*/
    };

    auto b = [&j, &str]() {
      // 以引用捕获的方式显式捕获j,str，修改它的值是对外部变量的修改
      j++;
      str = "name";

      // i是值捕获,对i修改，发现改不了
      //i = 1;
    };

    a();
    b();
    std::cout << i << std::endl;
    std::cout << j << std::endl;
    std::cout << str << std::endl;
  }
};

// 与STL的结合
void test_stl() {
  std::vector<int> vec { 10, -299,212, -90, 12};
  transform(vec.begin(), vec.end(), vec.begin(), [](int i) { if(i < 0) return -i; else return i;});
  for (auto item : vec) {
    std::cout << item << std::endl;
  }
}

// 用于启动线程
static int g_i = 0;
void test_thread() {
  std::thread my_thread([] {
    for (int i = 0; i < 100; ++i) {
      g_i += i;
    }
  });

  my_thread.join();
  if (!my_thread.joinable()) {
    std::cout << g_i << std::endl;
  }
}

// C++14 泛型lambda表达式
void test_lambda14_1() {
  auto lambda = [](auto lhs, auto rhs) { return lhs+rhs;};
  std::cout << lambda(1, 2) << std::endl;
  std::cout << lambda(1.0, 3.2) << std::endl;
}

// C++14 在lambda中使用std::move()
void test_lambda14_2() {
  std::unique_ptr<char> al(new char);
  *al = 's';

  auto lambda = [capture = std::move(al)]() {std::cout << *capture << std::endl;};
  lambda();

  std::cout << *al << std::endl;
}

// C++14 初始化lambda捕获列表
void test_lambda14_3() {
  int x = 10;
  auto y = [&r = x]()->int { r += 10; return r;};
  std::cout << y() << std::endl;
  std::cout << x << std::endl;
}

int main() {
  /*auto res = [](int a, int b) -> int { return a+b; };
  std::cout << res(1, 2) << std::endl;*/

  /*CTest1 tes;
  tes.test();*/

  /*CTest2 tes;
  tes.test();*/

   //与STL的结合
  //test_stl();

  // 用于启动线程
  //test_thread();

  // C++14 泛型lambda表达式
  //test_lambda14_1();

  // C++14 在lambda中使用std::move()
  //test_lambda14_2();

  // C++14 初始化lambda捕获列表
  test_lambda14_3();
}
