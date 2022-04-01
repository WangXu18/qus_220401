//#include <iostream>
//
//int main() {
//  int all_days = 0;
//  int temp = 0;
//  std::cin >> all_days;
//
//  int years = all_days / 365;
//  temp %= 365;
//
//  int mons = temp / 30;
//  temp %= 30;
//
//  std::cout << years << "  ano(s)" << std::endl;
//  std::cout << mons << "  mes(es)" << std::endl;
//  std::cout << temp << " dia(s)" << std::endl;
//
//  return 0;
//}

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

int main() {
  int n = 0;
  std::cin >> n;

  using pair_d_s = std::pair<double, std::string>;
  std::map<int, pair_d_s> maps;
  while (n--) {
    int x = 0;
    double y = 0.0;
    std::string z;
    std::cin >> x >> y >> z;

    maps.insert(std::make_pair(x, std::make_pair(y, z)));
    //maps.insert(std::pair<int, pair_d_s>(x, std::make_pair(y, z)));
  }

  auto ite = maps.begin();
  while (ite != maps.end()) {
    std::cout << ite->first << " " << (ite->second).first << " " << (ite->second).second << std::endl;
    ite++;
  }

  std::cout << " " << std::endl;
  return 0;
}