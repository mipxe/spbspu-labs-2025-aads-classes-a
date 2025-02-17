#include <iostream>
#include <stdexcept>
#include "fwd_list.hpp"

int main()
{
  int startArr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  rychkov::forward_list list;
  try
  {
    list = rychkov::convert(startArr, sizeof(startArr) / sizeof(int));
  }
  catch (...)
  {
    return 2;
  }

  size_t id = 0, dups = 0;
  while (std::cin >> id >> dups)
  {
    try
    {
      rychkov::duplicateNode(list.head, id - 1, dups);
    }
    catch (const std::out_of_range&)
    {
      rychkov::destroy(list.head);
      return 1;
    }
    catch (...)
    {
      rychkov::destroy(list.head);
      return 2;
    }
  }

  char delim[] = "\0";
  for (int& i : list)
  {

    std::cout << delim << i;
    delim[0] = ' ';
  }
  std::cout << '\n';
  rychkov::destroy(list.head);
}
