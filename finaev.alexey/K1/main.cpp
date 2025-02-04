#include <iostream>
#include "list.hpp"

int main()
{
  int* arr = nullptr;
  try
  {
    arr = new int[10];
  }
  catch (std::bad_alloc& e)
  {
    std::cerr << "Bad alloc!\n";
    return 1;
  }
  int a = 0;
  size_t count = 0;
  while (!std::cin.eof())
  {
    if (count == 10)
    {
      break;
    }
    std::cin >> a;
    if (std::cin.fail())
    {
      break;
    }
    else
    {
      arr[count++] = a;
    }
  }
  if (count == 0)
  {
    std::cerr << "uncorrect str!\n";
    delete[] arr;
    return 1;
  }
  finaev::BiList* p = nullptr;
  try
  {
    p = finaev::convertToList(arr, count);
  }
  catch (std::bad_alloc& e)
  {
    std::cerr << "Bad alloc!\n";
    return 1;
  }
  finaev::printList(std::cout, p);
  std::cout << "\n";
  finaev::deleteList(p);
  delete[] arr;
}
