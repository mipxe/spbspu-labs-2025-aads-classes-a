#include <iostream>
#include "fwd_list.hpp"

int main()
{
  int startArr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  rychkov::FwdList* head = rychkov::convert(startArr, sizeof(startArr) / sizeof(int));
  rychkov::destroy(head);
}
