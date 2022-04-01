// test_template.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

class interface {
 public:
  virtual int count() = 0;
};

template <class interface>
class test final {
 public:
  using _T = interface;
  using _TPtr = interface*;

  test() : type_(new _T()) {
  }
  ~test() {
    destroy();
  }
  void destroy() {
    if (type_) {
      delete type_;
      type_ = nullptr;
    }
  }

  test(const test&) = delete;
  test& operator=(const test&) = delete;
  test(const test&&) = delete;

  int count() {
    return type_->count();
  }

 private:
   _TPtr type_;
};

class inter1 : public interface {
 public:
  int count() override { return 1; }
};

class inter2 : public interface {
 public:
  int count() override { return 2; }
};

int main()
{
  test<inter1> test_inter1;
  std::cout << test_inter1.count() << std::endl;

  test<inter2> test_inter2;
  std::cout << test_inter2.count() << std::endl;

    std::cout << "Hello World!\n";
}