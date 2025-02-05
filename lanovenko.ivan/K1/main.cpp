#include "bilist.hpp"
#include <iostream>

void deleteList(BiList* tail)
{
  while (tail != nullptr)
  {
    BiList* temporary = tail;
    tail = tail->prev;
    delete temporary;
  }
}

BiList* toDoubleLinkedList(int* array, size_t res)
{
  if (res == 0)
  {
    return nullptr;
  }
  BiList* head = nullptr;
  BiList* tail = nullptr;
  try
  {
    head = new BiList{ array[0], nullptr, nullptr };
    tail = head;
    BiList* temporary = head;
    for (size_t i = 1; i < res; i++)
    {
      temporary->next = new BiList{ array[i], temporary, nullptr };
      tail = temporary->next;
      temporary = temporary->next;
    }
  }
  catch (const std::bad_alloc& e)
  {
    deleteList(tail);
    throw;
  }
  return tail;
}

int main()
{
  size_t res = 0;
  int* array = new int[10];
  int a = 0;
  while (std::cin >> a && !std::cin.eof())
  {
    array[res++] = a;
    if (res >= 10)
    {
      break;
    }
  }
  BiList* buf = nullptr;
  try
  {
    buf = toDoubleLinkedList(array,res);
  }
  catch (const std::bad_alloc& e)
  {
    deleteList(buf);
    throw;
  }
  BiList* temporary = buf;
  if (temporary == nullptr)
  {
    throw;
  }
  int b = temporary->value;
  std::cout << b;
  for (size_t i = 1; i < res; i++)
  {
    temporary = temporary->prev;
    b = temporary->value;
    std::cout << " " << b;
  }
  std::cout << '\n';
  delete[] array;
  deleteList(buf);
  return 0;
}
