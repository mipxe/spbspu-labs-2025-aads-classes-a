#include "fwd_list.hpp"

rychkov::FwdList* rychkov::convert(const int* arr, size_t size)
{
  if (size == 0)
  {
    return nullptr;
  }

  FwdList* head = new FwdList{arr[0]};
  ForwardIterator temp = head;
  for (size_t i = 1; i < size; i++)
  {
    try
    {
      temp = head->insert_after(temp, arr[i]);
    }
    catch (...)
    {
      destroy(head);
    }
  }
  return head;
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
  rychkov::ForwardIterator i = head->begin(), end = head->end();
  for (size_t j = 0; (i != end) && (j < id); ++i, j++)
  {}
  if (i == end)
  {
    return nullptr;
  }

  FwdList* result = i.node_;
  int value = *i;
  for (size_t j = 0; j < dups; j++)
  {
    try
    {
      i = head->insert_after(i, value);
    }
    catch (...)
    {
      for (; j > 0; j--)
      {
        head->erase_after(result);
      }
      throw;
    }
  }
  return result;
}

rychkov::ForwardIterator rychkov::FwdList::insert_after(ForwardIterator prev, value_type value)
{
  FwdList* newNode = new FwdList{value, prev.node_->next};
  prev.node_->next = newNode;
  return {newNode};
}
rychkov::ForwardIterator rychkov::FwdList::erase_after(ForwardIterator prev)
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
rychkov::ForwardIterator& rychkov::ForwardIterator::operator++()
{
  node_ = node_->next;
  return *this;
}
int& rychkov::ForwardIterator::operator*()
{
  return node_->value;
}
bool rychkov::ForwardIterator::operator==(const ForwardIterator& rhs)
{
  return node_ == rhs.node_;
}
bool rychkov::ForwardIterator::operator!=(const ForwardIterator& rhs)
{
  return node_ != rhs.node_;
}

rychkov::ForwardIterator rychkov::FwdList::begin()
{
  return {this};
}
rychkov::ForwardIterator rychkov::FwdList::end()
{
  return {nullptr};
}
