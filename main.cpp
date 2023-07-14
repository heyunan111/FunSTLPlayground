#include <iostream>
#include <type_traits>

int main() {
  using Type1 = std::decay_t<int>;         // int
  using Type2 = std::decay_t<int &>;       // int
  using Type3 = std::decay_t<int *>;       // int*
  using Type4 = std::decay_t<const int *>; // const int*
  using Type5 = std::decay_t<int[]>;       // int*
  using Type6 = std::decay_t<int(int)>;    // int(*)(int)

  std::cout << std::is_same_v<int, Type1> << std::endl;          // 输出: 1
  std::cout << std::is_same_v<int, Type2> << std::endl;          // 输出: 1
  std::cout << std::is_same_v<int *, Type3> << std::endl;        // 输出: 1
  std::cout << std::is_same_v<const int *, Type4> << std::endl;  // 输出: 1
  std::cout << std::is_same_v<int *, Type5> << std::endl;        // 输出: 1
  std::cout << std::is_same_v<int (*)(int), Type6> << std::endl; // 输出: 1

  return 0;
}
