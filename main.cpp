//  @see: https://en.wikipedia.org/wiki/Introsort
//  @see: https://www.techiedelight.com/introsort-algorithm/

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <cmath>

#include "introsort.h"

using namespace std::literals::string_literals;

void int_array(void);
void double_array(void);
void char_array(void);
void string_array(void);

/*
 *  MARK: Lambda ary_show()
 */
auto ary_show = [](auto const &col, size_t sp = 4ul) {
  std::cout << std::string(sp * 5ul, '-') << '\n';
  for (auto cc{1ul}, mc{5ul}; auto const &el : col) {
    std::cout << std::setw(sp) << el << (cc++ % mc == 0ul ? "\n" : "");
  }
  std::cout << std::endl;
  std::cout << std::string(sp * 5ul, '-') << '\n';
};

/*
 *  MARK:  main()
 */
int main(int argc, char const *argv[]) {
  std::cout << "C++ Version: " << __cplusplus << "\n\n";

  int_array();
  double_array();
  char_array();
  string_array();

  return 0;
}

/*
 *  MARK: int_array()
 */
void int_array(void) {
  std::cout << "In function " << __func__ << "()\n\n";

  int ary[] = {
      5, 7, -8, 9, 10, 4, -7, 0, -12, 1, 6, 2, 3, -4, -15, 12,
  };
  auto ary_sz = sizeof ary / sizeof *ary;
  std::cout << "Before:\n";
  ary_show(ary);

  // get the maximum depth
  auto maxdepth = static_cast<size_t>(::log(ary_sz)) * 2ul;

  // sort the array using introsort the algorithm
  introsort<int>(ary, ary, ary + ary_sz - 1, maxdepth);

  // print the sorted array
  // 	for (auto i_ { 0ul }; i_ < ary_sz; ++i_) {
  // 		std::cout << std::setw(4) << ary[i_];
  // 	}
  // 	std::cout << '\n';
  std::cout << "After:\n";
  ary_show(ary);
  std::cout << std::endl;

  return;
}

/*
 *  MARK: double_array()
 */
void double_array(void) {
  std::cout << "In function " << __func__ << "()\n\n";

  double sary[]{
      3.142, 77.8, -66.6, -4.0e2, 4.0e-2, 4096, 1024,
  };
  auto sary_sz = sizeof sary / sizeof *sary;

  // get the maximum depth
  auto maxdepth = static_cast<size_t>(::log(sary_sz)) * 2ul;

  std::cout << std::fixed << std::setprecision(3);
  std::cout << "Before:\n";
  ary_show(sary, 10ul);
  introsort<double>(sary, sary, sary + sary_sz - 1, maxdepth);
  std::cout << "After:\n";
  ary_show(sary, 10ul);
  std::cout << std::endl;

  return;
}

/*
 *  MARK: char_array()
 */
void char_array(void) {
  std::cout << "In function " << __func__ << "()\n\n";

  char cary[] = "a quick brown fox jumps over the lazy dog";
  auto cary_sz = sizeof cary / sizeof *cary;

  // get the maximum depth
  auto maxdepth = static_cast<size_t>(::log(cary_sz)) * 2ul;

  std::cout << "Before:\n";
  ary_show(cary, 2ul);
  introsort<char>(cary, cary, cary + cary_sz - 1, maxdepth);
  std::cout << "After:\n";
  ary_show(cary, 2ul);
  std::cout << std::endl;

  return;
}

/*
 *  MARK: string_array()
 */
void string_array(void) {
  std::cout << "In function " << __func__ << "()\n\n";

  std::string stary[]{
      "january"s,   "february"s, "march"s,    "april"s,
      "may"s,       "june"s,     "july"s,     "august"s,
      "september"s, "october"s,  "november"s, "december"s,
  };
  auto stary_sz = sizeof stary / sizeof *stary;

  // get the maximum depth
  auto maxdepth = static_cast<size_t>(::log(stary_sz)) * 2ul;

  std::cout << "Before:\n";
  ary_show(stary, 12ul);
  introsort<std::string>(stary, stary, stary + stary_sz - 1, maxdepth);
  std::cout << "After:\n";
  ary_show(stary, 12ul);
  std::cout << std::endl;

  return;
}
