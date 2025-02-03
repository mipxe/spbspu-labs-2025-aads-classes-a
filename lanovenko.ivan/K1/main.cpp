#include <iostream>
#include "bilist.hpp"


BiList* toDoubleLinkedList(int* array, size_t res)
{
  BiList* head = new BiList{ array[0],nullptr, nullptr };
  for (size_t i = 1; i < res; i++)
  {
    head->next = new BiList{ array[i], head, nullptr };
    head = head->next;
  }
  return head;
}

int main()
{
  size_t res = 0;
  int* array = new int[10000];
  int a = 0;
  while (std::cin >> a && !std::cin.eof())
  {
    array[res++] = a;
    if (res >= 10)
    {
      break;
    }
  }
  BiList* buf = toDoubleLinkedList(array, res);
  int b = 0;
  for (size_t i = 0; i < res; i++)
  {
    b = buf->value;
    buf = buf->prev;
    std::cout << b << ' ';
  }
  delete[] array;
}

