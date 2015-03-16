#include <iostream>
#include "sort.h"

using namespace std;

int compare(const int& lhs, const int& rhs)
{
  int ret = 0;
  if(lhs < rhs)
  {
    ret = - 1;
  }
  else if(lhs > rhs)
  {
    ret = 1;
  }
  return ret;
}

int main(int argc, char** argv)
{
  int sample[] = {2, 2, 4, 8, 0, 7, 1, 0, 5, 6, 4};
  cout << "sample values: " << endl;
  int size = sizeof(sample)/sizeof(int);
  cout << "sample size: " << size << "   values: " << endl;
  for(int i = 0; i < size; ++i)
  {
    cout << sample[i] << endl;
  }
  cout << "------------------------------" << endl;

  // quick sort
  // ::can::common::qsort(sample, 0, size -1, compare);
  //int pos = 10;
  //int* val = ::can::common::findnth(sample, 0, 10, pos, compare);
  //cout << pos << " th:" << *val << endl << endl;

  // insertion sort
  //::can::common::insertion_sort(sample, size, compare);

  int out[20] = {0};
  ::can::common::counting_sort(sample, out, size, 8);
  for(int i = 0; i < size; ++i)
  {
    cout << out[i] << endl;
  }
  return 0;
}

