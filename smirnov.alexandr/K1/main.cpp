#include <iostream>

struct BiList {
  int value;
  BiList * prev, * next;
};

BiList * arrayToBiList(int * numbers, size_t count)
{
  if (count == 0)
  {
    return nullptr;
  }
  BiList * head = new BiList{numbers[0], nullptr, nullptr};
  BiList * current = head;
  for (size_t i = 1; i < count; ++i)
  {
    current->next = new BiList{numbers[i], current, nullptr};
    current = current->next;
  }
  return head;
}

void printReverse(BiList * list)
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

void deleteBiList(BiList * list)
{
  while (list != nullptr)
  {
    BiList * next = list->next;
    delete list;
    list = next;
  }
}

int main()
{
  constexpr size_t max_size = 10;
  int * numbers = new int[max_size];
  size_t count = 0;
  while (count < max_size && std::cin >> numbers[count])
  {
    ++count;
  }
  BiList * list = arrayToBiList(numbers, count);
  printReverse(list);
  deleteBiList(list);
  delete[] numbers;
}
