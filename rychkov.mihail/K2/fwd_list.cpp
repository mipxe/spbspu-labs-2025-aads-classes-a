#include "fwd_list.hpp"

rychkov::FwdList* rychkov::convert(const int* arr, size_t size)
{
  if (size == 0)
  {
    return nullptr;
  }

  FwdList* head = new FwdList{arr[0]};
  FwdList* temp = head;
  for (size_t i = 1; i < size; i++)
  {
    try
    {
      temp = insert(temp, arr[i]);
    }
    catch (...)
    {
      destroy(head);
    }
  }
  return head;
}
rychkov::FwdList* rychkov::insert(FwdList* prev, int value)
{
  FwdList* newNode = new FwdList{value, prev->next};
  prev->next = newNode;
  return newNode;
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

rychkov::ForwardIterator& rychkov::ForwardIterator::operator++()
{
  node_ = node_->next;
  return *this;
}
int& rychkov::ForwardIterator::operator*()
{
  return node_->value;
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
