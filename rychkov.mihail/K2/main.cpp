#include <iostream>
#include "fwd_list.hpp"

int main()
{
  int startArr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  rychkov::FwdList* head = rychkov::convert(startArr, sizeof(startArr) / sizeof(int));

  int id = 0;
  size_t dups = 0;
  while (std::cin >> id >> dups)
  {
    try
    {
      for (size_t i = 0; i < dups; i++)
      {

      }
    }
    catch (...)
    {
      rychkov::destroy(head);
      return 2;
    }
  }

  std::cout << head->value;
  for (int& i : *(head->next))
  {
    std::cout << ' ' << i;
  }
  rychkov::destroy(head);
}
