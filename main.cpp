#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std::literals::string_literals;

// Function to perform insertion sort on subarray `a[low…high]`
template <typename T>
void insertionsort(T ary[], size_t low, size_t high) {
	// start from the second element in the subarray
	// (the element at index `low` is already sorted)
	for (auto i_ { low + 1ul }; i_ <= high; ++i_) {
		auto value = ary[i_];
		auto j_ = i_;

		// find index `j` within the sorted subset a[0…i-1]
		// where element a[i] belongs
		while (j_ > low && ary[j_ - 1ul] > value) {
			ary[j_] = ary[j_ - 1ul];
			j_--;
		}

		// Note that the subarray `a[j…i-1]` is shifted to
		// the right by one position, i.e., `a[j+1…i]`

		ary[j_] = value;
	}
}

// Function to partition the array using Lomuto partition scheme
template <typename T>
size_t partition(T ary[], size_t low, size_t high) {
	// Pick the rightmost element as a pivot from the array
	auto pivot = ary[high];

	// elements less than the pivot will be pushed to the left of `pIndex`
	// elements more than the pivot will be pushed to the right of `pIndex`
	// equal elements can go either way
	auto pIndex = low;

	// each time we find an element less than or equal to the pivot, `pIndex`
	// is incremented, and that element would be placed before the pivot.
	for (auto i_ { low }; i_ < high; ++i_) {
		if (ary[i_] <= pivot) {
			std::swap(ary[i_], ary[pIndex]);
			pIndex++;
		}
	}

	// swap `pIndex` with pivot
	std::swap(ary[pIndex], ary[high]);

	// return `pIndex` (index of the pivot element)
	return pIndex;
}

// Quicksort randomized partition to rearrange elements across pivot
template <typename T>
size_t randPartition(T ary[], size_t low, size_t high) {
	// choose a random index between `[low, high]`
	auto pivotIndex = ::rand() % (high - low + 1ul) + low;

	// swap the end element with the element present at a random index
	std::swap(ary[pivotIndex], ary[high]);

	// call the partition procedure
	return partition(ary, low, high);
}

// Function to perform heapsort on the given range of elements
template <typename T>
void heapsort(T * begin, T * end) {
	std::make_heap(begin, end);
	std::sort_heap(begin, end);
}

// Function to perform introsort on the given array
template <typename T>
void introsort(T ary[], T * begin, T * end, size_t maxdepth) {
	// perform insertion sort if partition size is 16 or smaller
	if ((end - begin) < 16ul) {
		insertionsort(ary, begin - ary, end - ary);
	}
	// perform heapsort if the maximum depth is 0
	else if (maxdepth == 0ul) {
		heapsort(begin, end + 1ul);
	}
	else {
		// otherwise, perform Quicksort
		auto pivot = randPartition(ary, begin - ary, end - ary);
		introsort(ary, begin, ary + pivot - 1, maxdepth - 1ul);
		introsort(ary, ary + pivot + 1, end, maxdepth - 1ul);
	}
}

int main(int argc, char const * argv[]) {
  auto ary_show = [](auto const & col, size_t sp = 4ul) {
    std::cout << std::string(sp * 5ul, '-') << '\n';
    for (auto cc { 1ul }, mc { 5ul }; auto const & el : col) {
  		std::cout << std::setw(sp) << el << (cc++ % mc == 0ul ? "\n" : "");
    }
    std::cout << std::endl;
    std::cout << std::string(sp * 5ul, '-') << '\n';
  };

	int ary[] = { 5, 7, -8, 9, 10, 4, -7, 0, -12, 1, 6, 2, 3, -4, -15, 12, };
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

  double sary[] { 3.142, 77.8, -66.6, -4.0e2, 4.0e-2, 4096, 1024, };
  auto sary_sz = sizeof sary / sizeof *sary;

	// get the maximum depth
	maxdepth = static_cast<size_t>(::log(sary_sz)) * 2ul;

  std::cout << std::fixed << std::setprecision(3);
	ary_show(sary, 10ul);
	introsort<double>(sary, sary, sary + sary_sz - 1, maxdepth);
	ary_show(sary, 10ul);

  char cary[] = "a quick brown fox jumps over the lazy dog";
  auto cary_sz = sizeof cary / sizeof *cary;

	// get the maximum depth
	maxdepth = static_cast<size_t>(::log(cary_sz)) * 2ul;

  ary_show(cary, 2ul);
	introsort<char>(cary, cary, cary + cary_sz - 1, maxdepth);
  ary_show(cary, 2ul);

  std::string stary[] {
    "january"s, "february"s, "march"s,     "april"s,   "may"s,      "june"s,
    "july"s,    "august"s,   "september"s, "october"s, "november"s, "december"s,
  };
  auto stary_sz = sizeof stary / sizeof *stary;

	// get the maximum depth
	maxdepth = static_cast<size_t>(::log(stary_sz)) * 2ul;

  ary_show(stary, 12ul);
	introsort<std::string>(stary, stary, stary + stary_sz - 1, maxdepth);
  ary_show(stary, 12ul);

	return 0;
}
