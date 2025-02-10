#include <iostream>
#include "fwd_list.hpp"

int main()
{
  int startArr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  rychkov::FwdList* head = rychkov::convert(startArr, sizeof(startArr) / sizeof(int));

  size_t id = 0, dups = 0;
  while (std::cin >> id >> dups)
  {
    try
    {
      rychkov::FwdList* found = rychkov::duplicateNode(head, id - 1, dups);
      if (!found)
      {
        rychkov::destroy(head);
        return 1;
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
  std::cout << '\n';
  rychkov::destroy(head);
}
