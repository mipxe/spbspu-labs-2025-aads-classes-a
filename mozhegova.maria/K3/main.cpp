#include <iostream>

template< class T >
struct List {
  T data;
  List< T > * next;
};

List< List< int > * > * convert(const int * const * d, size_t m, const size_t * n);

template< class T, class C >
size_t count(const List< List< T > * > * head, C condition);

void deleteArr(int ** arr, size_t count)
{
  for (size_t i = 0; i < count; i++)
  {
    delete[] arr[i];
  }
  delete[] arr;
}

int main()
{
  size_t n = 0;
  std::cin >> n;
  int ** arrays = nullptr;
  size_t i = 0;
  try
  {
    arrays = new int * [n];
    for (; i < n; i++)
    {
      size_t m = 0;
      std::cin >> m;
      int * num = new int[m];
      for (size_t j = 0; j < m; j++)
      {
        int a = 0;
        std::cin >> a;
        num[j] = a;
      }
    }
  }
  catch(...)
  {
    deleteArr(arrays, i);
    std::cerr << "Out of memory\n";
    return 1;
  }
}
