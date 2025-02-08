#include <iostream>

struct BiList {
  int value;
  BiList * prev, * next;
};

void deleteBiList(BiList * list)
{
  while (list != nullptr)
  {
    BiList * next = list->next;
    delete list;
    list = next;
  }
}

BiList * arrayToBiList(const int * const numbers, size_t count)
{
  if (count == 0)
  {
    return nullptr;
  }
  BiList * head = new BiList{numbers[0], nullptr, nullptr};
  BiList * current = head;
  for (size_t i = 1; i < count; ++i)
  {
    BiList * newNode = nullptr;
    try
    {
      newNode = new BiList{numbers[i], current, nullptr};
    }
    catch (const std::bad_alloc & e)
    {
      deleteBiList(head);
      throw;
    }
    current->next = newNode;
    current = newNode;
  }
  return head;
}

void printReverse(const BiList * list)
{
  while (list->next != nullptr)
  {
    list = list->next;
  }
  std::cout << list->value;
  list = list->prev;
  while (list != nullptr)
  {
    std::cout << " " << list->value;
    list = list->prev;
  }
  std::cout << "\n";
}

int main()
{
  constexpr size_t max_size = 10;
  int * numbers = nullptr;
  size_t count = 0;
  try
  {
    numbers = new int[max_size];
  }
  catch (const std::bad_alloc & e)
  {
    std::cerr << "Out of memory\n";
    return 1;
  }
  while (count < max_size && std::cin >> numbers[count])
  {
    ++count;
  }
  BiList * list = nullptr;
  try
  {
    list = arrayToBiList(numbers, count);
  }
  catch (const std::bad_alloc & e)
  {
    delete[] numbers;
    std::cerr << "Out of memory\n";
    return 1;
  }
  printReverse(list);
  deleteBiList(list);
  delete[] numbers;
}
