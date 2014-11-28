#ifndef COMMON_CAN_SORT_H_
#define COMMON_CAN_SORT_H_

#include<assert.h>
#include<iostream>

namespace can { namespace common {

template<typename T>
int partition(T* base, const int left, const int right, int (*cmp)(const T&, const T&))
{
  assert(base && cmp);
  int low = left - 1;
  for(int high = left; high < right; ++high)
  {
    if(cmp(base[high], base[right]) < 0)
    {
      ++low;
      // swap
      T tmp      = base[low];
      base[low]  = base[high];
      base[high] = tmp;
    }
  }
  // the following swap make it unstable
  T tmp = base[low + 1];
  base[low + 1] = base[right];
  base[right]   = tmp;
  return (low + 1);
}

/**
  find the nth element of the array
  time complexity: O(lgn)
**/
template<typename T>
T* findnth(
    T*        base,
    const int left,       // left most element
    const int right,      // right most element
    const int nth,        // start from 0
    int (*cmp)(const T&, const T&))
{
  assert(base && cmp && nth <= (right - left));
  int lhs = left;
  int rhs = right;
  int pivot = left;
  do
  {
    pivot = partition(base, lhs, rhs, cmp);
    int pos = pivot - left;
    if(pos == nth)
      break;
    if(pivot > nth)
    {
      rhs = pivot - 1;
    }
    else
    {
      lhs = pivot + 1;
    }
  } while(true);
  return (base + pivot);
} // findnth

/**
  Avery efficient with "divide and conquer" unstable sort algorithm
  time complexity: O(nlogn)
**/
template<typename T>
void qsort(T* base, int left, int right, int (*cmp)(const T&,const T&))
{
  if(base == NULL || cmp == NULL || left < 0 || left > right)
    return ;
  // first should partition the array
  int pivot = partition(base, left, right, cmp);
  qsort(base, left, pivot - 1, cmp);
  qsort(base, pivot + 1, right, cmp);
} // qsort

/**
  stable sort algorithm
  time complexity: O(n^2)
**/
template<typename T>
void insertion_sort(T* base, int len, int (*cmp)(const T& lhs, const T& rhs))
{
  assert(base && len > 0);
  int forward = 1;
  for(; forward < len; ++forward)
  {
    T key = base[forward];
    int backward = forward - 1;
    while(backward >= 0 && (cmp(base[backward], key) > 0))
    {
      base[backward + 1] =  base[backward];
      --backward;
    }
    base[backward + 1] = key;
  }
} // insertion sort

}}  // ::can::common

#endif // COMMON_CAN_SORT_H_

