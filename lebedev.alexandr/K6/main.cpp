#include <iostream>

template< class T >
struct BiTree
{
  T data;
  BiTree *left, *right, *parent;
};

int main()
{
  size_t size = 0;
  std::cin >> size;
  int* arr = new int[size];
  for (size_t i = 0; i < size; i++)
  {
    if (!(std::cin >> arr[i]))
    {
      delete[] arr;
      std::cerr << "Incorrect input!\n";
      return 1;
    }
  }
}
