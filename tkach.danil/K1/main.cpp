#include <iostream>
#include "list.hpp"

namespace
{
  void printReverseList(std::ostream& out, tkach::BiList* tail)
  {
    while(tail != nullptr)
    {
      out << tail->value << " ";
      tail = tail->prev;
    }
  }

  tkach::BiList* createlist(int* array, size_t size)
  {
    using namespace tkach;
    if (size == 0)
    {
      return nullptr;
    }
    BiList* head = new BiList{array[0], nullptr, nullptr};
    BiList* tail = head;
    BiList* current = head;
    for (size_t i = 1; i < size; ++i)
    {
      BiList* new_list = new BiList{array[i], current, nullptr};
      current->next = new_list;
      current = new_list;
    }
    tail = current;
    return tail;
  }
}

int main()
{
  size_t counter = 0;
  int* array = new int[10];
  while(!std::cin.eof() && counter <= 9 && !std::cin.fail())
  {
    std::cin >> array[counter];
    counter++;
  }
  counter--;
  printReverseList(std::cout, createlist(array, counter));
  std::cout << "\n";
  delete[] array;
  return 0;
}
