#include <iostream>

void deleteArr(int* arr[], size_t size)
{
  for (size_t i = 0; i <= size; ++i)
  {
    delete[] arr[i];
  }
  delete[] arr;
}

int main()
{
  size_t capacity = 0;
  std::cin >> capacity;
  if (!std::cin.good())
  {
    std::cerr << "uncorrect input\n";
    return 1;
  }
  int ** arr = nullptr;
  try
  {
    arr = new int*[capacity];
  }
  catch(const std::bad_alloc&)
  {
    std::cerr << "bad alloc!\n";
    return 1;
  }
  size_t size = 0;
  while(std::cin)
  {
    for (size_t i = 0; i < capacity; ++i)
    {
      std::cin >> size;
      if (!std::cin.good())
      {
        deleteArr(arr, i);
        std::cerr << "uncorrect input\n";
        return 1;
      }
      try
      {
        arr[i] = new int[size];
      }
      catch(const std::bad_alloc&)
      {
        deleteArr(arr, i);
        std::cerr << "bad_alloc\n";
        return 1;
      }
      for (size_t j = 0; j < size; ++j)
      {
        int temp = 0;
        std::cin >> temp;
        if (!std::cin.good())
        {
          deleteArr(arr, i);
          std::cerr << "uncorrect input\n";
          return 1;
        }
        arr[i][j] = temp;
      }
    }
  }
}
