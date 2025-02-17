#include <iostream>

namespace rychkov
{
  template< class T >
  struct List
  {
    T data;
    List< T >* next = nullptr;
  };

  void destroy(List< List< int >* >* head)
  {
    while (head != nullptr)
    {
      for (auto i = head->data; i != nullptr; i = i->next)
      {
        delete i;
      }
      auto temp = head;
      head = head->next;
      delete temp;
    }
  }
  void destroy(int** arr, size_t height)
  {
    while (height > 0)
    {
      delete[] arr[--height];
    }
    delete[] arr;
  }
}

int main()
{
  size_t height = 0;
  if (!(std::cin >> height))
  {
    std::cerr << "failed to read arrays count\n";
    return 1;
  }
  int** arr = nullptr;
  try
  {
    arr = new int*[height];
  }
  catch (...)
  {
    return 2;
  }

  for (size_t i = 0; i < height; i++)
  {
    size_t width = 0;
    if (!(std::cin >> width))
    {
      std::cerr << "failed to read array (#" << i + 1 << ") length\n";
      rychkov::destroy(arr, i);
      return 1;
    }

    try
    {
      arr[i] = new int[width];
    }
    catch (...)
    {
      rychkov::destroy(arr, i);
      return 2;
    }

    for (size_t j = 0; j < width; j++)
    {
      if (!(std::cin >> arr[i][j]))
      {
        std::cerr << "failed to read value[" << i << "][" << j << "]\n";
        rychkov::destroy(arr, i + 1);
        return 1;
      }
    }
  }
  rychkov::destroy(arr, height);
}
