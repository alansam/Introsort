//  @see: https://en.wikipedia.org/wiki/Introsort
//  @see: https://www.techiedelight.com/introsort-algorithm/

#pragma once
#ifndef INTROSORT_H
#define INTROSORT_H

#include <algorithm>

// Function to perform insertion sort on subarray `a[low…high]`
template <typename T>
void insertionsort(T ary[], size_t low, size_t high) {
  // start from the second element in the subarray
  // (the element at index `low` is already sorted)
  for (auto i_{low + 1ul}; i_ <= high; ++i_) {
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
  for (auto i_{low}; i_ < high; ++i_) {
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
void heapsort(T *begin, T *end) {
  std::make_heap(begin, end);
  std::sort_heap(begin, end);
}

// Function to perform introsort on the given array
template <typename T>
void introsort(T ary[], T *begin, T *end, size_t maxdepth) {
  if ((end - begin) < 16ul) {
    // perform insertion sort if partition size is 16 or smaller
    insertionsort(ary, begin - ary, end - ary);
  }
  else if (maxdepth == 0ul) {
    // perform heapsort if the maximum depth is 0
    heapsort(begin, end + 1ul);
  }
  else {
    // otherwise, perform Quicksort
    auto pivot = randPartition(ary, begin - ary, end - ary);
    introsort(ary, begin, ary + pivot - 1, maxdepth - 1ul);
    introsort(ary, ary + pivot + 1, end, maxdepth - 1ul);
  }
}

#endif /* INTROSORT_H */
