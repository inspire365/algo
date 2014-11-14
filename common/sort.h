#ifndef COMMON_CAN_SORT_H_
#define COMMON_CAN_SORT_H_

namespace can { namespace common {

template<typename T>
int hoare_partition(T* base, int left, int right, int (*cmp)(const T&, const T&))
{
  // TODO
}

template<typename T>
int partition(T* base, int left, int right, int (*cmp)(const T&, const T&))
{
  T pivot = base[right];
  int low = left - 1;
  for(int high = left; high < right; ++high)
  {
    if(cmp(base[high], pivot) <= 0)
    {
      ++low;
      // swap
      T tmp      = base[low];
      base[low]  = base[high];
      base[high] = tmp;
    }
  }
  T tmp = base[low + 1];
  base[low + 1] = base[right];
  base[right]   = tmp;
  return (low + 1);
}

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
}

}}  // ::can::common

#endif // COMMON_CAN_SORT_H_

