// priority_queue.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <queue>

int main()
{
    std::priority_queue<int> test;
    int k = 4;
    //std::priority_queue<int, std::vector<int>, std::less<int> > a;

    for (int i = 0; i < 10; ++i) {
      test.push(i);
      if (test.size() > k) {
        test.pop();
      }
    }

    while (!test.empty()) {
      std::cout << test.top() << std::endl;
      test.pop();
    }

    return 0;
}

