#include <iostream>
#include <cstddef>
#include <stdexcept>
#include "list.hpp"

namespace
{
  void deleteList(tkach::BiList* tail)
  {
    while(tail != nullptr)
    {
      tkach::BiList* prev_tail = tail->prev;
      delete tail;
      tail = prev_tail;
    }
  }
  
  void printReverseList(std::ostream& out, const tkach::BiList* tail)
  {
    out << tail->value;
    tail = tail->prev;
    while(tail != nullptr)
    {
      out << " " << tail->value;
      tail = tail->prev;
    }
  }

  tkach::BiList* createlist(const int* const array, const size_t size)
  {
    using namespace tkach;
    if (size == 0)
    {
      return nullptr;
    }
    BiList* head = new BiList{array[0], nullptr, nullptr};
    BiList* tail = head;
    for (size_t i = 1; i < size; ++i)
    {
      BiList* new_list = nullptr;
      try
      {
        new_list = new BiList{array[i], tail, nullptr};
      }
      catch (const std::bad_alloc&)
      {
        deleteList(tail);
        throw;
      }
      tail->next = new_list;
      tail = new_list;
    }
    return tail;
  }
}

int main()
{
  size_t counter = 0;
  int* array = new int[10];
  while(counter < 10 && std::cin >> array[counter])
  {
    counter++;
  }
  tkach::BiList* tail = nullptr;
  try
  {
    tail = createlist(array, counter);
  }
  catch (const std::bad_alloc&)
  {
    delete[] array;
    std::cerr << "Not enough memory\n";
    return 1;
  }
  printReverseList(std::cout, tail);
  std::cout << "\n";
  delete[] array;
  deleteList(tail);
  return 0;
}
