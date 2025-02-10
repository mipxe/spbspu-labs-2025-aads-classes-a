#ifndef BI_LIST_HPP
#define BI_LIST_HPP

#include <cstddef>

namespace rychkov
{
  struct FwdList;
  FwdList* duplicateNode(FwdList* head, size_t id, size_t dups);
  class ForwardIterator
  {
  public:
    ForwardIterator(): node_(nullptr)
    {}
    ForwardIterator(FwdList* node): node_(node)
    {}

    ForwardIterator& operator++();
    int& operator*();
    bool operator==(const ForwardIterator& rhs);
    bool operator!=(const ForwardIterator& rhs);
  private:
    FwdList* node_;
    friend struct FwdList;
    friend FwdList* rychkov::duplicateNode(FwdList* head, size_t id, size_t dups);
  };

  struct FwdList
  {
    using value_type = int;

    value_type value;
    FwdList* next = nullptr;

    ForwardIterator begin();
    ForwardIterator end();
    ForwardIterator insert_after(ForwardIterator prev, value_type value);
    ForwardIterator erase_after(ForwardIterator prev);
  };
  FwdList* convert(const int* arr, size_t size);
  void destroy(FwdList* tail);

}

#endif
