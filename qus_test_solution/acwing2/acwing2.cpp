// acwing2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

//void sort_arr(float arr[], int length) {
//  int last_exchange = 0;
//  int sorted_borer = length - 1;
//  for (int i = 0; i < length - 1; ++i) {
//    bool is_sorted = true;
//    for (int j = 0; j < sorted_borer; ++j) {
//      if (arr[j] < arr[j + 1]) {
//        arr[j] = arr[j] + arr[j + 1];
//        arr[j + 1] = arr[j] - arr[j + 1];
//        arr[j] = arr[j] - arr[j + 1];
//        is_sorted = false;
//        last_exchange = j;
//      }
//    }
//    sorted_borer = last_exchange;
//    if (is_sorted) {
//      break;
//    }
//  }
//}
//
//int main()
//{
//  float arr[3] = {0.0};
//  std::cin >> arr[0] >> arr[1] >> arr[2];
//
//  sort_arr(arr, 3);
//  float a = arr[0], b = arr[1], c = arr[2];
//  if (a >= b + c) {
//    std::cout << "NAO FORMA TRIANGULO" << std::endl;
//  } else if (a * a == b * b + c * c) {
//    std::cout << "TRIANGULO RETANGULO" << std::endl;
//  } else if (a * a > b * b + c * c) {
//    std::cout << "TRIANGULO OBTUSANGULO" << std::endl;
//  } else if (a * a < b * b + c * c) {
//    std::cout << "TRIANGULO ACUTANGULO" << std::endl;
//    if (a == b && b == c) {
//      std::cout << "TRIANGULO EQUILATERO" << std::endl;
//    } else if (a == b || b == c) {
//      std::cout << "TRIANGULO ISOSCELES" << std::endl;
//    }
//  }
//  return 0;
//}


//#include <iostream>
//
//void sort_arr(int arr[], int length) {
//  int last_exchange = 0;
//  int sored_border = length - 1;
//
//  for (int i = 0; i < length - 1; ++i) {
//    bool is_sored = true;
//    for (int j = 0; j < sored_border; ++j) {
//      if (arr[j] > arr[j + 1]) {
//        arr[j] = arr[j] + arr[j + 1];
//        arr[j + 1] = arr[j] - arr[j + 1];
//        arr[j] = arr[j] - arr[j + 1];
//        is_sored = false;
//        last_exchange = j;
//      }
//    }
//    sored_border = last_exchange;
//    if (is_sored) {
//      break;
//    }
//  }
//}
//
//int main() {
//  int arr[3] = {0};
//  int a = 0, b = 0, c = 0;
//
//  std::cin >> arr[0] >> arr[1] >> arr[2];
//  a = arr[0];
//  b = arr[1];
//  c = arr[2];
//
//  sort_arr(arr, 3);
//
//  std::cout << arr[0] << std::endl;
//  std::cout << arr[1] << std::endl;
//  std::cout << arr[2] << std::endl;
//  std::cout << std::endl;
//  std::cout << a << std::endl;
//  std::cout << b << std::endl;
//  std::cout << c << std::endl;
//
//  return 0;
//}

//#include <iostream>
//
//int main() {
//  int a = 0, b = 0, sum = 0;
//  std::cin >> a >> b;
//
//  if (a > b) {
//    a = a + b;
//    b = a - b;
//    a = a - b;
//  }
//
//  for (int i = a + 1; i < b; ++i) {
//    if (i & 1) {
//      sum += i;
//    }
//  }
//
//  std::cout << sum << std::endl;
//
//  return 0;
//}

//#include <iostream>
//
//int main() {
//  int n = 0, m = 0, start = 1;
//  std::cin >> n >> m;
//
//  for (int i = 0; i < n; ++i) {
//    for (int j = start; j <= start + m - 1; ++j) {
//      if (j < start + m - 1) {
//        std::cout << j << " ";
//      } else {
//        std::cout << "PUM" << std::endl;
//        start = j + 1;
//        break;
//      }
//    }
//  }
//
//  return 0;
//}

//#include <cstdio>
//#include <iostream>
//
//int main() {
//  int n = 0;
//  std::cin >> n;
//
//  int arr[3] = {0};
//  while (n--) {
//    int count = 0;
//    char ch;
//    //scanf("%d%c", &count, &ch);
//    std::cin >> count >> ch;
//
//    if (ch == 'C') {
//      arr[0] += count;
//    } else if (ch == 'R') {
//      arr[1] += count;
//    } else if (ch == 'F') {
//      arr[2] += count;
//    }
//  }
//
//  int total = arr[0] + arr[1] + arr[2];
//  std::cout << "Total: " << total << " animals" << std::endl;
//  std::cout << "Total coneys: " << arr[0] << std::endl;
//  std::cout << "Total rats: " << arr[1] << std::endl;
//  std::cout << "Total frogs: " << arr[2] << std::endl;
//  printf("Percentage of coneys: %.2lf \%\n",
//         arr[0] / static_cast<double>(total));
//  printf("Percentage of rats: %.2lf \%\n", arr[1] / static_cast<double>(total));
//  printf("Percentage of frogs: %.2lf \%\n",
//         arr[2] / static_cast<double>(total));
//
//  return 0;
//}

//#include <iostream>
//#include <vector>
//
//int main() {
//  int m = 0, n = 0;
//
//  std::vector<int> vec;
//  while (std::cin >> m >> n, (m != 0) && (n != 0)) {
//    if (m > n) {
//      m = m + n;
//      n = m - n;
//      m = m - n;
//    }
//
//    vec.emplace_back(m);
//    vec.emplace_back(n);
//  }
//
//  for (int i = 0; i < vec.size(); i += 2) {
//    int sum = 0;
//    for (int j = vec[i]; j <= vec[i + 1]; ++j) {
//      sum += j;
//      std::cout << j << " ";
//    }
//    std::cout << "Sum=" << sum << std::endl;
//  }
//
//  return 0;
//}

//#include <iostream>
//
//class a {
// public:
//   void fun1() { std::cout << "121" << std::endl;}
//};
//
//int main() {
//  /*a* test = nullptr;
//  test->fun1();*/
//  /*void * b = nullptr;
//  ((a*)b)->fun1();*/
//  std::move(1);
//}

//#include <string>
//#include <windows.h>
//
//class Solution {
// public:
//  int strToInt(std::string str) {
//    int k = 0;
//    while (k < str.size() && str[k] == ' ') {
//      k++;
//    }
//
//    long long number = 0;
//    bool flag = false;
//    if (str[k] == '+') {
//      k++;
//    } else if (str[k] == '-') {
//      k++;
//      flag = true;
//    }
//
//    while (k < str.size() && str[k] >= '0' && str[k] <= '9') {
//      number = number * 10 + str[k] - '0';
//      k++;
//    }
//
//    if (flag) {
//      number *= -1;
//    }
//    if (number > INT_MAX) {
//      number = INT_MAX;
//    }
//    if (number < INT_MIN) {
//      number = INT_MIN;
//    }
//    return (int)number;
//  }
//};
//
//int main() {
//  Solution test;
//  auto a = FAILED(-1);
//  std::cout << test.strToInt("9223372036854775808") << std::endl;
//  
//}

//#include <iostream>
//#include <vector>
//
//int getMissingNumber(std::vector<int>& nums) {
//  size_t n = nums.size() + 1;
//  if (n == 1) {
//    return 0;
//  }
//  int sum = 0;
//  size_t i = 0;
//  for (; i < n-1; ++i) {
//    sum += nums[i];
//    int res = i * (i + 1) / 2;
//    if (res < sum) {
//      return i;
//    }
//  }
//  return i;
//}
//
//int main() {
//  std::vector<int> vec = {0,1,2,3,4};
//  std::cout << getMissingNumber(vec) << std::endl;
//}


//#include <stack>
//#include <vector>
//#include <algorithm>
//class MyQueue {
// public:
//  /** Initialize your data structure here. */
//  MyQueue() { }
//
//  /** Push element x to the back of queue. */
//  void push(int x) {
//    if (stack1.empty()) {
//      stack1.push(x);
//    } else {
//      while (!stack1.empty()) {
//        stack2.push(stack1.top());
//        stack1.pop();
//      }
//      stack1.push(x);
//      while (!stack2.empty()) {
//        stack1.push(stack2.top());
//        stack2.pop();
//      }
//    }
//  }
//
//  /** Removes the element from in front of queue and returns that element. */
//  int pop() {
//    int temp = stack1.top();
//    stack1.pop();
//    return temp;
//  }
//
//  /** Get the front element. */
//  int peek() {
//    return stack1.top();
//  }
//
//  /** Returns whether the queue is empty. */
//  bool empty() { return stack1.empty(); }
//
// private:
//  std::stack<int> stack1, stack2;
//  bool flag;
//};
//
//int main() {
//  MyQueue que;
//  que.push(27);
//  std::cout << que.peek() << std::endl;
//  std::cout << que.peek() << std::endl;
//  std::cout << que.empty() << std::endl;
//  que.push(24);
//  que.push(24);
//  std::cout << que.peek() << std::endl;
//  std::cout << que.peek() << std::endl;
//  std::cout << que.empty() << std::endl;
//  que.pop();
//
//  std::vector<int>  vec;
//  sort(vec.begin(), vec.end(),vec);
//
//  return 0;
//}

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue obj = MyQueue();
 * obj.push(x);
 * int param_2 = obj.pop();
 * int param_3 = obj.peek();
 * bool param_4 = obj.empty();
 */


//#include <vector>
//#include <algorithm>
//
//std::vector<int> getLeastNumbers_Solution(std::vector<int> input, int k) {
//  sort(input.begin(), input.end(), [](int* a, int * b) {});
//  std::vector<int> res;
//  for (int i = 0; i < k; ++k) {
//    res.push_back(input[i]);
//  }
//  return res;
//}
//
//int main() {
//  std::vector<int> vec = {1,2,3,5,3,4,5,6};
//  auto temp = getLeastNumbers_Solution(vec, 4);
//
//  return 0;
//}

//int parti(std::vector<int>& vec, int start, int end) {
//  int item = vec[start];
//  int left = start, right = end;
//
//  while (left != right) {
//    while (left < right && vec[right] > item) {
//      right--;
//    }
//    while (left < right && vec[left] <= item) {
//      left++;
//    }
//    if (left < right) {
//      vec[left] = vec[left] + vec[right];
//      vec[right] = vec[left] - vec[right];
//      vec[left] = vec[left] - vec[right];
//    }
//  }
//
//  vec[start] = vec[left];
//  vec[left] = item;
//  return left;
//}
//
//void quick_sort(std::vector<int>& vec, int l, int r) {
//  if (l >= r) {
//    return;
//  }
//
//  int index = parti(vec, l, r);
//  quick_sort(vec, l, index - 1);
//  quick_sort(vec, index + 1, r);
//}
//
//int main() {
//  std::vector<int> vec = {1,3,4,56,7,54,2};
//
//  quick_sort(vec, 0, vec.size()-1);
//
//  std::cout << " " <<std::endl;
//  return 0;
//}