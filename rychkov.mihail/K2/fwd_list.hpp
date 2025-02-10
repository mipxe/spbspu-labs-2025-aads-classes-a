#ifndef BI_LIST_HPP
#define BI_LIST_HPP

#include <cstddef>

namespace rychkov
{
  struct FwdList {
    int value;
    FwdList* next = nullptr;
  };
  FwdList* convert(const int* arr, size_t size);
  FwdList* insert(FwdList* prev, int value);
  void destroy(FwdList* tail);
}

#endif
