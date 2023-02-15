// 4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <queue>
#include <condition_variable>
#include <thread>
#include <mutex>

std::condition_variable cv_aet;
std::queue<int> deq_tmp;
std::mutex mt;

int main()
{

  std::thread thread_test1([] {
	while (1) {
		std::lock_guard<std::mutex> lk(mt);
		deq_tmp.push(rand()%100);
		cv_aet.notify_one();
	}
	});

  std::thread thread_test0([] {
	while (true)
	{
	  std::unique_lock<std::mutex> lk(mt);
	  cv_aet.wait(lk, [] {return !deq_tmp.empty(); });
	  auto value = deq_tmp.front();
	  value *= 2;
	  std::cout << value << std::endl;
	  deq_tmp.pop();
	  lk.unlock();
	}});
  if (thread_test0.joinable()) {
	thread_test0.join();
  }

  return 0;
}

