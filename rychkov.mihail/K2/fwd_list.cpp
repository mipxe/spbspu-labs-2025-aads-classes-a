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
