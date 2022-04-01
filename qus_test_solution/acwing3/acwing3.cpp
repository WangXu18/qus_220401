// acwing3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//#include <iostream>
//
//int get_count(int n, int i, int mid) {
//  return n - 2 * abs(mid - i);
//}
//
//int get_start(int count, int mid) {
//  return mid - count/2;
//}
//
//int main() {
//  int n = 0;
//  std::cin >> n;
//
//  int mid = (n + 1) / 2;
//  int count = 0, start = 0;
//  for (int i = 1; i <= n; ++i) {
//    count = get_count(n, i, mid);
//    start = get_start(count, mid);
//    for (int j = 1; j <= n; ++j) {
//      if (j < start || j > start + count - 1) {
//        std::cout << " ";
//      } else {
//        std::cout << "*";
//      }
//    }
//    std::cout << std::endl;
//  }
//
//  return 0;
//}

//#include <iostream>
//
//int main() {
//  int arr[10] = {0};
//  int i = 0;
//  while (std::cin >> arr[i], i++, i < 10)
//    ;
//
//  std::cout << "" << std::endl;
//
//  return 0;
//}

//#include <iostream>
//#include <vector>
//
//void print_arr(int input) {
//  
//
//  std::cout << " s" << std::endl;
//
//
//  //while (count--) {
//  //  for (int i = 0; i < input; ++i) {
//  //    for (int j = 0; j < input; ++j) {
//  //      if (i >= count && i <= input - count && j >= count &&
//  //          j <= input - count) {
//  //        arr[i][j] = start;
//  //      }
//  //    }
//  //  }
//  //  //start++;
//  //}
//
//  /*for (int i = 0; i < input; ++i) {
//    for (int j = 0; j < input; ++j) {
//      std::cout << arr[i][j] << " ";
//    }
//    std::cout << std::endl;
//  }*/
//  //std::cout << std::endl;
//}
//
//int main() {
//  int n = 0;
//  std::vector<int> vec;
//  while (std::cin >> n, n > 0) {
//    vec.emplace_back(n);
//  }
//
//  for (auto item : vec) {
//    print_arr(item);
//  }
//
//  return 0;
//}

//#include <iostream>
//
//int main() {
//  int n = 0, item = 0, min = 0, index = 0, count = 0;
//  std::cin >> n;
//
//  while (std::cin >> item, n--) {
//    if (count == 0) {
//      min = item;
//      index = 0;
//    } else {
//      if (min > item) {
//        min = item;
//        index = count;
//      }
//    }
//    count++;
//  }
//
//  std::cout << "Minimum value: " << min << std::endl;
//  std::cout << "Position: " << index << std::endl;
//
//  return 0;
//}


//#include <iostream>
//
//class Obj {
// public:
//  void func1() { std::cout << "func1" << std::endl;}
//  virtual void func2() { std::cout << "func2" << std::endl; }
//
// private:
//  int test_;
//};
//
//int main() {
//  Obj* o = NULL;
//
//  o->func1();
//  o->func2();
//  //o->test_;
//
//  return 0;
//}

//#include <iostream>
//
//int main() {
//  int n = 0;
//  std::cin >> n;
//  while (n--) {
//    std::string str1, str2;
//    std::cin >> str1 >> str2;
//
//    if (str1.compare(str2) == 0) {
//      std::cout << "Tie" << std::endl;
//    } else if ((str1.compare("Hunter") == 0 && str2.compare("Gun") == 0) ||
//               (str1.compare("Gun") == 0 && str2.compare("Bear") == 0) ||
//               (str1.compare("Bear") == 0 && str2.compare("Hunter") == 0)) {
//      std::cout << "Player1" << std::endl;
//    } else {
//      std::cout << "Player2" << std::endl;
//    }
//  }
//
//  return 0;
//}

//#include <iostream>
//
//int main() {
//  std::string str;
//  std::cin >> str;
//
//  int arr[26] = {0};
//  int index[26] = {0};
//  int count = 0;
//  for (auto ch : str) {
//    if (arr[ch - 'a'] == 0) {
//      index[ch - 'a'] = count;
//    }
//
//    arr[ch - 'a']++;
//    count++;
//  }
//
//  char ch;
//  int min_index = 0;
//  bool start = true;
//  for (int i = 0; i < 26; ++i) {
//    if (arr[i] == 1 && start) {
//      min_index = index[i];
//      start = false;
//    } else if (arr[i] == 1 && !start) {
//      if (min_index > index[i]) {
//        min_index = index[i];
//      }
//    }
//  }
//
//  bool flag = true;
//  for (int i = 0; i < 26; ++i) {
//    if (arr[i] >= 1 && ((arr[i] & 1) == 1)) {
//      flag = false;
//      break;
//    }
//  }
//
//  if (flag) {
//    std::cout << "no" << std::endl;
//  } else {
//    std::cout << str[min_index] << std::endl;
//  }
//
//  return 0;
//}

//#include <iostream>
//#include <string>
//
//int main() {
//  std::string str;
//  getline(std::cin, str);
//
//  for (int i = 0; i < str.size(); ++i) {
//    if (islower(str[i])) {
//      str[i] = (str[i] + 1 > 122) ? 97 : str[i]+1;
//    } else if (isupper(str[i])) {
//      str[i] = (str[i] + 1 > 90) ? 65 : str[i]+1;
//    }
//  }
//
//  std::cout << str << std::endl;
//
//  return 0;
//}

//#include <iostream>
//// #include <string>
//
//int main() {
//  int count = 0;
//  std::cin >> count;
//
//  char ch_his;
//  int num_his = 0;
//  while (count--) {
//    std::string str;
//    std::cin >> str;
//
//    char ch = str[0];
//    int num = 0;
//    for (size_t i = 0; i < str.size(); ++i) {
//      if (str[i] == ch) {
//        num++;
//        if (num > num_his) {
//          ch_his = ch;
//          num_his = num;
//        }
//      } else {
//        if (num > num_his) {
//          ch_his = ch;
//          num_his = num;
//        }
//        ch = str[i];
//        num = 1;
//      }
//    }
//
//    std::cout << ch_his << " " << num_his << std::endl;
//    num_his = 0;
//  }
//
//  return 0;
//}

//#include <iostream>
//#include <string>
//
//int main() {
//  std::string str;
//  getline(std::cin, str);
//
//  std::string str_his;
//  int start = 0;
//  for (size_t i = 0; i < str.size(); ++i) {
//    if (isblank(str[i]) && i == 0) {
//      start = i + 1;
//    } else if (isblank(str[i]) || str[i] == '.') {
//      std::string temp = str.substr(start, i - start);
//      if (temp.size() > str_his.size()) {
//        str_his = temp;
//      }
//      start = i + 1;
//    }
//  }
//
//  std::cout << str_his << std::endl;
//
//  return 0;
//}

//#include <iostream>
//#include <vector>
//#include <string>
//
//int main() {
//  std::string str;
//  getline(std::cin, str);
//
//  std::vector<std::string> vec;
//  int start = 0;
//  for (size_t i = 0; i < str.size(); ++i) {
//    /*if (i == str.size() - 1) {
//      vec.emplace_back(str.substr(start, i - start + 1));
//      start = i + 1;
//      i = start;
//    }*/
//    if (isblank(str[i])) {
//      vec.emplace_back(str.substr(start, i - start));
//      start = i + 1;
//      i = start;
//    }
//
//    if (i + 1 == str.size()) {
//      vec.emplace_back(str.substr(start, i - start + 1));
//    }
//  }
//
//  auto rite = vec.rbegin();
//  while (rite != vec.rend()) {
//    std::cout << *rite << " ";
//    rite++;
//  }
//
//  return 0;
//}

//#include <iostream>
//#include <vector>
//#include <string>
//
//std::string get_find(const std::string str) {
//  std::string res;
//
//  std::vector<int> vec;
//  for (size_t i = 1; i <= str.size(); ++i) {
//    if (str.size() % i == 0) {
//      vec.emplace_back(i);
//    }
//  }
//
//  int max = vec[0];
//  for (auto item : vec) {
//    int len = str.size() / item;
//    std::string temp = str.substr(0, len);
//    std::string temp_res;
//    for (int i = 0; i < item; ++i) {
//      temp_res += temp;
//    }
//    if (temp_res.size() > str.size()) {
//      continue;
//    }
//    if (temp_res.compare(str) == 0) {
//      if (max < item) {
//        max = item;
//      }
//    }
//  }
//  res = str.substr(0, str.size()/max);
//
//  return res;
//}
//
//int get_count(const std::string str) {
//  int res = 0;
//  /*int count_arr[26] = {0};
//  for (auto ch : str) {
//    count_arr[ch - 'a']++;
//  }
//
//  int count = 0;
//  for (int i = 0; i < 26; ++i) {
//    if (count_arr[i] > 0) {
//      count++;
//    }
//  }
//
//  if (count == 1) {
//    res = str.size();
//  } else if (count == str.size()) {
//    res = 1;
//  } else {
//    std::string find = get_find(str);
//    res = str.size() / find.size();
//  }*/
//
//  std::string find = get_find(str);
//  res = str.size() / find.size();
//
//  return res;
//}
//
//int main() {
//  std::string str;
//  while (std::cin >> str, str.compare(".") != 0) {
//    int count = get_count(str);
//    std::cout << count << std::endl;
//  }
//
//  return 0;
//}

//#include <iostream>
//#include <string>
//
//int main() {
//  std::string str, str1, str2, str3;
//  std::cin >> str;
//
//  int start = 0;
//  int index = str.find(",", start);
//  str1 = str.substr(start, index - start);
//  start = index + 1;
//  index = str.find(",", start);
//  str2 = str.substr(start, index - start);
//  start = index + 1;
//  str3 = str.substr(start, str.size() - start);
//
//  return 0;
//}

//#include <iostream>
//#include <vector>
//
//int main() {
//  int n = 0;
//
//  while (std::cin >> n, n > 0) {
//    
//    std::vector<std::string> vec;
//    std::string str;
//    while (n--) {
//      std::cin >> str;
//      vec.emplace_back(str);
//    }
//
//    size_t min_size = vec[0].size();
//    std::string str_start = vec[0];
//    for (auto item : vec) {
//      if (item.size() < min_size) {
//        min_size = item.size();
//        str_start = item;
//      }
//    }
//
//    int count = 0;
//    int start = 0;
//    char ch = str_start[str_start.size() - 1];
//    for (size_t i = 0; i < min_size; ++i) {
//      bool flag = true;
//      for (auto str : vec) {
//        if (str[str.size() - 1 - start] != ch) {
//          flag = false;
//          break;
//        }
//      }
//
//      if (flag) {
//        count++;
//        start++;
//        int s = str_start.size();
//        if (s - 1 - start >= 0) {
//          ch = str_start[s - 1 - start];
//        }
//      } else {
//        break;
//      }
//    }
//
//    std::cout << str_start.substr(str_start.size() - count, count)
//              << std::endl;
//  }
//
//  return 0;
//}

//#include <iostream>
//
//void print2D(int a[][100], int row, int col) {
//  for (int i = 0; i < row; ++i) {
//    for (int j = 0; i < col; ++j) {
//      std::cout << a[i][j] << " ";
//    }
//    std::cout << std::endl;
//  }
//}
//
//int main() {
//  int row = 0, col = 0;
//  std::cin >> row >> col;
//
//  int arr[100][100] = {0};
//  for (int i = 0; i < row; ++i) {
//    for (int j = 0; j < col; ++j) {
//      std::cin >> arr[i][j];
//    }
//  }
//
//  print2D(arr, row, col);
//
//  return 0;
//}

//#include <iostream>
//
//int main() {
//  int x = 0, y = 0, size = 0;
//  std::cin >> x >> y >> size;
//  int n[100] = {0}, m[100] = {0};
//
//  int temp = x;
//  while (temp--) {
//    std::cin >> n[x - temp - 1];
//  }
//  temp = y;
//  while (temp--) {
//    std::cin >> m[y - temp - 1];
//  }
//
//  for (int i = 0; i < size; ++i) {
//    m[i] = n[i];
//  }
//
//  for (int i = 0; i < y; ++i) {
//    std::cout << m[i] << " ";
//  }
//
//  return 0;
//}


//#include <iostream>
//
//int x = 0;
//
//void dfs(int r, int nums[], bool flags[]) {
//  if (r > x) {
//    for (int i = 1; i <= x; ++i) {
//      std::cout << nums[i] << " ";
//    }
//    std::cout << std::endl;
//  } else {
//    for (int i = 1; i <= x; ++i) {
//      if (flags[i] == false) {
//        flags[i] = true;
//        nums[r] = i;
//        dfs(r + 1, nums, flags);
//        flags[i] = false;
//      }
//    }
//  }
//}
//
//int main() {
//  std::cin >> x;
//
//  int nums[10] = {0};
//  bool flags[10] = {false};
//  dfs(1, nums, flags);
//
//  return 0;
//}

//#include <iostream>
//#include <string>
//
//size_t get_index(std::string str, int start, bool& flag) {
//  int index = -1;
//  for (int i = start; i < str.size() - 1; ++i) {
//    if (str[i] != ' ') {
//      if (str[i] == '+') {
//        index = i + 1;
//        break;
//      } else if (str[i] == '-') {
//        flag = false;
//        index = i + 1;
//        break;
//      } else if (str[i] >= '0' && str[i] <= '9') {
//        index = i;
//        break;
//      }
//    }
//  }
//  return index;
//}
//
//int main() {
//  std::string str;
//  getline(std::cin, str);
//  str += '\0';
//
//  //size_t index = 0;
//  
//  
//  
//  //
//
//  //size_t start = index;
//  int start = 0;
//  int end = 0;
//  std::string res;
//  bool flag1 = true;
//  while (start < str.size()-1) {
//    bool flag = true;
//    start = get_index(str, start, flag);
//    if (start < 0) {
//      break;
//    }
//    flag1 = flag;
//    for (int i = start; i < str.size(); ++i) {
//      if (str[i] < '0' || str[i] > '9' || str[i] == '\0') {
//        end = i;
//        break;
//      }
//    }
//
//    if (end > start) {
//      std::string temp = str.substr(start, end-start);
//      if (res.size() < temp.size()) {
//        res += temp;
//      }
//    } else {
//      break;
//    }
//
//    start = end;
//    /*for (size_t i = start; i < str.size()-1; ++i) {
//      if (str[i] != ' ' && (str[i] == '+' || str[i] == '-' ||
//                            (str[i] >= '0' && str[i] <= '9'))) {
//        start = i;
//        break;
//      }
//    }*/
//  }
//  
//  int count = res.size();
//  int number = 0;
//  for (size_t i = 0; i < count; ++i) {
//    number += (res[i]-'1'+1) * pow(10, count-1-i);
//  }
//
//  if (!flag1) {
//    number = -number;
//  }
//
//  if (number > INT_MAX) {
//    std::cout <<INT_MAX << std::endl;
//  } else if (number < INT_MIN) {
//    std::cout << INT_MIN << std::endl;
//  } else {
//    std::cout << number << std::endl;
//  }
//
//  std::cout << " " << std::endl;
//
//  return 0;
//}

//#include <iostream>
//#include <string>
//
//int get_index(std::string str, int start) {
//  int index = -1;
//  for (int i = start; i < static_cast<int>(str.size()) - 1; ++i) {
//    if (str[i] != ' ') {
//      index = i;
//      break;
//    }
//  }
//  return index;
//}
//
//int main() {
//    std::string str;
//    getline(std::cin, str);
//    str += '\0';
//    int start = 0;
//    int end = 0;
//    bool flag = true;
//    std::string res;
//    start = get_index(str, start);
//          
//    int number = 0;
//    while (start != -1) {
//      if (str[start] == '-') {
//        flag = false;
//        start++;
//        start = get_index(str, start);
//        continue;
//      } else if (str[start] == '+') {
//        start++;
//        start = get_index(str, start);
//        continue;
//      } else if (str[start] >= '0' && str[start] <= '9') {
//        int end = 0;
//        for (size_t i = start; i < str.size(); ++i) {
//          if (str[i] < '0' || str[i] > '9' || str[i] == '\0') {
//            end = i;
//            break;
//          }
//        }
//        if (end > start) {
//          res = str.substr(start, end - start);
//        }
//
//        int count = res.size();
//        for (int i = 0; i < count; ++i) {
//          if (!flag) {
//            number += -((int)(res[i] - '1') + 1) * pow(10, count - 1 - i);
//          } else {
//            number += ((int)(res[i] - '1') + 1) * pow(10, count - 1 - i);
//          }
//          
//          if (number > INT_MAX) {
//            number = INT_MAX;
//            break;
//          } else if (number < INT_MIN) {
//            number = INT_MIN;
//            break;
//          }
//        }
//
//        break;
//      } else {
//        break;
//      }
//    }
//
//    std::cout << number << std::endl;
//
//  return 0;
//}
