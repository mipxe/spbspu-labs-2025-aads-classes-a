#include <iostream>
#include <cstddef>

template< class T >
struct List
{
  T data;
  List< T > * next;
};
template< class T, class C >
size_t count(const List< List< T > * > * head, C condition)
{}
List< List< int > * > * convert(const int * const * d, size_t m, const size_t * n);
void deleteArray(int ** array, size_t numArray)
{
  for (size_t i = 0; i < numArray; ++i)
  {
    delete[] array[i];
  }
  delete[] array;
}

int main()
{
  size_t numArray = 0;
  size_t numElements = 0;
  if (!(std::cin >> numArray))
  {
    std::cerr << "error input number of arrays\n";
    return 1;
  }
  int ** array = new int*[numArray];
  for (size_t i = 0; i < numArray; i++)
  {
    if (!(std::cin >> numElements))
    {
      std::cerr << "error input\n";
      deleteArray(array, i);
      return 1;
    }
    try
    {
      array[i] = new int[numElements];
    }
    catch (const std::bad_alloc & e)
    {
      std::cerr << "memory error\n";
      deleteArray(array, i);
      return 1;
    }
    for (size_t j = 0; j < numElements; j++)
    {
      if (!(std::cin >> array[i][j]))
      {
        std::cerr << "error input\n";
        deleteArray(array, i);
        return 1;
      }
    }
  }
  deleteArray(array, numArray);
}
