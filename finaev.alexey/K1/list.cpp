#include "list.hpp"
#include <iostream>

finaev::BiList* finaev::convertToList(const int* arr, const size_t count)
{
  BiList* head = nullptr;
  try
  {
    head = new BiList{ arr[0], nullptr, nullptr };
  }
  catch (const std::bad_alloc&)
  {
    throw;
  }
  BiList* p = head;
  for (size_t i = 1; i < count; ++i)
  {
    try
    {
      p->next = new BiList{ arr[i], p, nullptr };
    }
    catch (const std::bad_alloc&)
    {
      deleteList(p);
      throw;
    }
    p = p->next;
  }
  return p;
}

void finaev::deleteList(finaev::BiList* p)
{
  while (p != nullptr)
  {
    finaev::BiList* back = p->prev;
    delete p;
    p = back;
  }
}

void finaev::printList(std::ostream& out, const finaev::BiList* p)
{
  out << p->value;
  p = p->prev;
  while (p != nullptr)
  {
    out << " " << p->value;
    p = p->prev;
  }
}
