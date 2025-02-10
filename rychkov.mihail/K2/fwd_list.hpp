#ifndef BI_LIST_HPP
#define BI_LIST_HPP

#include <cstddef>

namespace rychkov
{
  struct FwdList;
  class ForwardIterator
  {
  public:
    ForwardIterator(): node_(nullptr)
    {}
    ForwardIterator(FwdList* node): node_(node)
    {}

    ForwardIterator& operator++();
    int& operator*();
    bool operator!=(const ForwardIterator& rhs);
  private:
    FwdList* node_;
  };

  struct FwdList
  {
    int value;
    FwdList* next = nullptr;
    ForwardIterator begin();
    ForwardIterator end();
  };
  FwdList* convert(const int* arr, size_t size);
  FwdList* insert(FwdList* prev, int value);
  void destroy(FwdList* tail);

}

#endif
