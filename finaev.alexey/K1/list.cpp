#include "list.hpp"
#include <iostream>

finaev::BiList* finaev::convertToList(int* arr, int count)
{
  BiList* head = nullptr;
  try
  {
    head = new BiList{ arr[0], nullptr, nullptr };
  }
  catch (std::bad_alloc&)
  {
    std::cerr << "Bad alloc!\n";
    throw;
  }
  BiList* p = head;
  for (int i = 1; i < count; ++i)
  {
    try
    {
      p->next = new BiList{ arr[i], p, nullptr };
    }
    catch (std::bad_alloc& e)
    {
      std::cerr << "Bad alloc!\n";
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
  while (p != nullptr)
  {
    out << p->value << " ";
    p = p->prev;
  }
}
