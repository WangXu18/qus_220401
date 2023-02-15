#ifndef DL_H
#define DL_H

#include <mutex>

namespace sg1 {

class singleton {
public:
  static singleton* getinstance() {
	if (!singleton_) {
	  singleton_ = new singleton();
	}
	return singleton_;
  }

private:
  singleton(){}
  singleton(const singleton&) {}

private:
  static singleton* singleton_;
};

singleton* singleton::singleton_ = nullptr;

}

namespace sg2 {
std::mutex m;

class singleton {
public:
  static singleton* getinstance() {
	if (singleton_ == nullptr) {
	  std::lock_guard<std::mutex> lk(m);
	  if (singleton_ == nullptr) {
		singleton_ = new singleton();
	  }
	}
	return singleton_;
  }

private:
  singleton() {}
  singleton(const singleton&) {}

  static singleton* singleton_;
};

singleton* singleton::singleton_ = nullptr;
}

namespace sg3 {

static std::mutex m;

class singleton {
public:
  static singleton* getinstance() {
	singleton* tmp = singleton_.load(std::memory_order_relaxed);
	if (!tmp) {
	  std::lock_guard<std::mutex> lk(m);
	  tmp = singleton_.load(std::memory_order_relaxed);
	  if (!tmp) {
		tmp = new singleton();
		atomic_thread_fence(std::memory_order_release);
		singleton_.store(tmp, std::memory_order_relaxed);
	  }
	}

	return tmp;
  }
private:
  singleton() {}
  singleton(const singleton&) {}

  static std::atomic<singleton*> singleton_;
};

std::atomic<singleton*> singleton::singleton_ = nullptr;
}

#endif //DL_H

