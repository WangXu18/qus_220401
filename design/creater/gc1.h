#ifndef _GC1_H
#define _GC1_H

#include <iostream>

namespace gc1 {
enum class test_type : int {
  enum_test_type_a,
  enum_test_type_b,
  enum_test_type_c,
  enum_test_type_d,
  enum_test_type_e,
};

class test {
 public:
  virtual void create() = 0;
};

class test_a : public test {
public:
  // from test
  void create() override {
	std::cout << "test_a" << std::endl;
  }
};

class test_b : public test {
public:
  explicit test_b(int value) {}

  // from test
  void create() override {
	std::cout << "test_b" << std::endl;
  }
};


class manager_base {
public:
  virtual test* create(test_type flag) = 0;
};

class manager_test {
public:
  virtual test_a* create_a() = 0;
  virtual test_b* create_b() = 0;
};

class manager_impl : public manager_base {
public:
  test* create(test_type flag) override {
	switch (flag) {
	case test_type::enum_test_type_a: {
	  return new test_a(); 
	}
	case test_type::enum_test_type_b: {
	  return new test_b(static_cast<int>(test_type::enum_test_type_b));
	}
	default:
	  break;
	}
  }
};

class manager_impl_test : public manager_test {
public:
  // from manager_test
  test_a* create_a() override {
	return dynamic_cast<test_a*>(impl_.create(test_type::enum_test_type_a));
  }

  test_b* create_b() override {
	return dynamic_cast<test_b*>(impl_.create(test_type::enum_test_type_b));
  }

private:
  manager_impl impl_;
};
}

namespace gc2 {

}

#endif // _GC1_H