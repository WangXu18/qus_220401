// t1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cctype>
#include <vector>
// 2[a]1[bc]
// 2[e2[d]]
// 3[abc]2[cd]ff

int digit(const std::string str) {
  for (size_t i = 0; i < str.size(); ++i) {
    if (isdigit(str[i])) {
      return i;
    }
  }
  return -1;
}

std::string cvt_real(const std::string str, int index) {
   std::string temp = str;
  int number = atoi(&str[index]);
  std::vector<int> vec_l, vec_r;

  for (int i = index+1; i < temp.size(); ++i) {
    if (temp[i] == '[') {
      vec_l.emplace_back(i);
    } else if (temp[i] == ']') {
      vec_r.emplace_back(i);
    }
  }

  int l_index = vec_l[0], r_index = 0;
  if (vec_l.size() > 1) {
    if (vec_l[1] > vec_r[0]) {
      r_index = vec_r[0];
    } else {
      r_index = vec_r[vec_r.size() - 1];
    }
  } else {
    r_index = vec_r[0];
  }

  std::string prefix_str = str.substr(0, index);
  std::string sub_str = str.substr(l_index+1, r_index-l_index-1);
  std::string suffix_str = str.substr(r_index+1, str.size()-r_index-1);
  std::string res_mid;
  for (int i = 0; i < number; ++i) {
    res_mid += sub_str;
  }
  return prefix_str + res_mid + suffix_str;
}

std::string cvt(const std::string str) {
  std::string temp = str;
  int index = digit(temp);
   while (index != -1) {
    temp = cvt_real(temp, index);
    index = digit(temp);
  }
  return temp;
}

int main() {
  std::string str = "3[abc]2[cd]ff";//abcabcabcdcdff
  //std::string str = "2[e2[d]]";
  //std::string str = "2[a]1[bc]";

  std::string output = cvt(str);
  std::cout << output << std::endl;

  return 0;
}