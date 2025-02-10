#ifndef BI_LIST_HPP
#define BI_LIST_HPP

#include <cstddef>

namespace rychkov
{
  struct BiList {
    int value;
    BiList* prev = nullptr;
    BiList* next = nullptr;
  };
  BiList* convert(const int* arr, size_t size);
  void destroy(BiList* tail);
}

#endif
