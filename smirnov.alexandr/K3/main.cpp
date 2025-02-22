#include <iostream>
#include <cstddef>
#include <stdexcept>

template< class T >
struct List
{
  T data;
  List< T > * next;
};

void deleteArrays(int ** arrays, size_t numArrays)
{
  for (size_t i = 0; i < numArrays; ++i)
  {
    if (arrays[i])
    {
      delete[] arrays[i];
    }
  }
  delete[] arrays;
}

int main()
{
  int ** arrays = nullptr;
  size_t * sizes = nullptr;
  size_t numArrays = 0;
  try
  {
    std::cin >> numArrays;
    if (!std::cin)
    {
      std::cerr << "Input error\n";
      return 1;
    }
    arrays = new int * [numArrays];
    sizes = new size_t[numArrays];
    for (size_t i = 0; i < numArrays; ++i)
    {
      size_t arraySize;
      std::cin >> arraySize;
      if (!std::cin)
      {
        std::cerr << "Input error\n";
        return 1;
      }
      arrays[i] = new int[arraySize];
      sizes[i] = arraySize;
      for (size_t j = 0; j < arraySize; ++j)
      {
        std::cin >> arrays[i][j];
        if (!std::cin)
        {
          std::cerr << "Input error\n";
          return 1;
        }
      }
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    deleteArrays(arrays, numArrays);
    delete[] sizes;
    return 1;
  }
}
