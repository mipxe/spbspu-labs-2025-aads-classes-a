#include <iostream>
#include "bilist.hpp"


BiList* toDoubleLinkedList(int* array, size_t res)
{
  BiList* head = new BiList{ array[0],nullptr, nullptr };
  BiList* tail = head;
  BiList* temporary = head;
  for (size_t i = 1; i < res; i++)
  {
    temporary->next = new BiList{ array[i], temporary, nullptr };
    temporary = temporary->next;
    tail = temporary;
  }
  return tail;
}

void toDeleteList(BiList* head)
{
  BiList* current = head;
  while(current != nullptr)
  {
    BiList* next = current->next;
    delete current;
    current = next;
  }
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
  BiList* buf = toDoubleLinkedList(array, res);
  BiList* temporary = buf;
  int b = 0;
  for (size_t i = 0; i < res; i++)
  {
    b = temporary->value;
    temporary = temporary->prev;
    std::cout << b << ' ';
  }
  delete[] array;
  toDeleteList(buf);
}

