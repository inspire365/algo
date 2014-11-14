
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
  int sample[] = {2, 8, 7, 1, 3, 5, 6, 4};
  cout << "sample values: " << endl;
  int size = sizeof(sample)/sizeof(int);
  cout << "sample size: " << size << "   values: " << endl;
  for(int i = 0; i < size; ++i)
  {
    cout << sample[i] << endl;
  }
  cout << "------------------------------" << endl;

  ::can::common::qsort(sample, 0, size -1, compare);

  for(int i = 0; i < size; ++i)
  {
    cout << sample[i] << endl;
  }
  return 0;
}

