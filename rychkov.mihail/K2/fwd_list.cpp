#include "fwd_list.hpp"

#include <memory>
#include <stdexcept>

rychkov::forward_list rychkov::convert(const int* arr, size_t size)
{
  if (size == 0)
  {
    return {nullptr};
  }

  forward_list result = {new FwdList{arr[0]}};
  ForwardIterator temp = result.begin();
  for (size_t i = 1; i < size; i++)
  {
    try
    {
      temp = result.insert_after(temp, arr[i]);
    }
    catch (...)
    {
      destroy(result.head);
      throw;
    }
  }
  return result;
}
void rychkov::destroy(FwdList* head)
{
  while (head != nullptr)
  {
    FwdList* temp = head->next;
    delete head;
    head = temp;
  }
}
rychkov::FwdList* rychkov::duplicateNode(FwdList* head, size_t id, size_t dups)
{
  forward_list list{head};
  ForwardIterator i = list.begin(), end = list.end();
  for (size_t j = 0; (i != end) && (j < id); ++i, j++)
  {}
  if (i == end)
  {
    throw std::out_of_range("invalid list node id");
  }

  FwdList* result = i.node_;
  int value = *i;
  for (size_t j = 0; j < dups; j++)
  {
    try
    {
      i = list.insert_after(i, value);
    }
    catch (...)
    {
      for (; j > 0; j--)
      {
        list.erase_after(result);
      }
      throw;
    }
  }
  return result;
}

rychkov::ForwardIterator& rychkov::ForwardIterator::operator++()
{
  node_ = node_->next;
  return *this;
}
rychkov::ForwardIterator rychkov::ForwardIterator::operator++(int)
{
  ForwardIterator temp(*this);
  node_ = node_->next;
  return temp;
}
int& rychkov::ForwardIterator::operator*() const
{
  return node_->value;
}
int* rychkov::ForwardIterator::operator->() const
{
  return std::addressof(node_->value);
}
bool rychkov::ForwardIterator::operator==(const ForwardIterator& rhs) const noexcept
{
  return node_ == rhs.node_;
}
bool rychkov::ForwardIterator::operator!=(const ForwardIterator& rhs) const noexcept
{
  return node_ != rhs.node_;
}

rychkov::ForwardIterator rychkov::forward_list::insert_after(ForwardIterator prev, value_type value)
{
  FwdList* newNode = new FwdList{value, prev.node_->next};
  prev.node_->next = newNode;
  return {newNode};
}
rychkov::ForwardIterator rychkov::forward_list::erase_after(ForwardIterator prev)
{
  if ((prev.node_ == nullptr) || (prev.node_->next == nullptr))
  {
    return nullptr;
  }
  FwdList* toDelete = prev.node_->next;
  prev.node_->next = toDelete->next;
  delete toDelete;
  return prev.node_->next;
}
rychkov::ForwardIterator rychkov::forward_list::begin()
{
  return {head};
}
rychkov::ForwardIterator rychkov::forward_list::end()
{
  return {nullptr};
}
