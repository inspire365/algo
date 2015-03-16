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
      // swap, may make it unstable
      T tmp      = base[low];
      base[low]  = base[high];
      base[high] = tmp;
    }
  }
  // the following swap may make it unstable
  T tmp = base[low + 1];
  base[low + 1] = base[right];
  base[right]   = tmp;
  return (low + 1);
} // partition

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
    // we must call partiion at least once
    // otherwise it's out of order, makes no
    // sense to find the right position
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



/**
 * counting sort: stable, time complexity: O(n)
 * @param in input array
 * @param out output array
 * @param len arary length of in & out
 * @param range interger range is 0 ~ range
*/
void counting_sort(int* in, int* out, const int len, const int range)
{
  assert(in && out && len > 0 && range >= 0);
  int r = range + 1;  // one more space for 0
  int* pt = (int*)calloc(r, sizeof(int));
  for(int i = 0; i < len; ++i)
  {
    // contains the number of elements equal to in[i]
    pt[in[i]] = pt[in[i]] + 1;
  }

  for(int i = 1; i < r; ++i)
  {
    // contains the number of elements less than or equal to i
    pt[i] = pt[i] + pt[i-1];
  }

  for(int i = len - 1; i >= 0; --i)
  {
    // to make it clear, draw a picture
    out[pt[in[i]] - 1] = in[i];
    pt[in[i]] = pt[in[i]] - 1;
  }
  free(pt);
}

}}  // ::can::common

#endif // COMMON_CAN_SORT_H_

