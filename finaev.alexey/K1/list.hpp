#ifndef LIST_HPP
#define LIST_HPP

#include <fstream>

namespace finaev
{
  struct BiList
  {
    int value;
    BiList* prev, * next;
  };
  BiList* convertToList(int* arr, int count);
  void deleteList(BiList* p);
  void printList(std::ostream& out, const BiList* p);
}

#endif
