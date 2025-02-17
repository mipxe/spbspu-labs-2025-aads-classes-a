#include <iostream>

namespace
{
  template< class T >
  struct List {
    T data;
    List< T > * next;
  };

  void deleteMtx(int** matrix, size_t m)
  {
    for (size_t i = 0; i < m; ++i) 
    {
      delete[] matrix[i];
    }
    delete[] matrix;
  }
}

int main()
{
  int arrays_size = 0;
  size_t created = 0;
  std::cin >> arrays_size;
  if (arrays_size <= 0)
  {
    std::cerr << "No arrays\n";
    return 1;
  }
  int** arrays = new int*[arrays_size];
  size_t* sizes = new size_t[arrays_size];
  for (size_t i = 0; i < size_t(arrays_size); ++i)
  {
    std::cin >> sizes[i];
    try
    {
      arrays[i] = new int[sizes[i]];
    }
    catch (const std::bad_alloc&)
    {
      deleteMtx(arrays, created);
      return 1;
    }
    created++;
    for (size_t j = 0; j < sizes[i]; ++j)
    {
      std:: cin >> arrays[i][j];
    }
  }
  if (!std::cin)
  {
    deleteMtx(arrays, created);
  }
  deleteMtx(arrays, created);
  return 0;
}
