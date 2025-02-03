#include <iostream>
#include "bi_list.hpp"

int main()
{
  size_t nEntered = 0;
  constexpr size_t maxEntered = 10;
  int arr[maxEntered] = {};
  for (; (nEntered < maxEntered) && (std::cin >> arr[nEntered]); nEntered++)
  {}

  rychkov::BiList* tail = nullptr;
  try
  {
    tail = rychkov::convert(arr, nEntered);
  }
  catch (...)
  {
    return 2;
  }
  if (tail)
  {
    std::cout << tail->value;
  }
  for (rychkov::BiList* node = tail->prev; node != nullptr; node = node->prev)
  {
    std:: cout << ' ' << node->value;
  }
  std::cout << '\n';
  rychkov::destroy(tail);
}
