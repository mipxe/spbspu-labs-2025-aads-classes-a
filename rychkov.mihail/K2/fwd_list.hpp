#ifndef BI_LIST_HPP
#define BI_LIST_HPP

#include <cstddef>

namespace rychkov
{
  struct FwdList
  {
    int value;
    FwdList* next = nullptr;
  };
  FwdList* duplicateNode(FwdList* head, size_t id, size_t dups);

  struct forward_list;
  class ForwardIterator
  {
  public:
    ForwardIterator(): node_(nullptr)
    {}

    ForwardIterator& operator++();
    ForwardIterator operator++(int);
    int& operator*() const;
    int* operator->() const;
    bool operator==(const ForwardIterator& rhs) const noexcept;
    bool operator!=(const ForwardIterator& rhs) const noexcept;
  private:
    FwdList* node_;
    ForwardIterator(FwdList* node): node_(node)
    {}
    friend struct rychkov::forward_list;
    friend FwdList* rychkov::duplicateNode(FwdList* head, size_t id, size_t dups);
  };

  struct forward_list
  {
    using value_type = int;
    FwdList* head = nullptr;

    ForwardIterator begin();
    ForwardIterator end();
    ForwardIterator insert_after(ForwardIterator prev, value_type value);
    ForwardIterator erase_after(ForwardIterator prev);
  };
  forward_list convert(const int* arr, size_t size);
  void destroy(FwdList* head);

}

#endif
