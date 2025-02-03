#include <iostream>

struct BiList {
  int value;
  BiList * prev, * next;
};

BiList * arrayToBiList(int * numbers, int count)
{
  if (count == 0)
  {
    return nullptr;
  }
  BiList * head = new BiList{numbers[0], nullptr, nullptr};
  BiList * current = head;
  for (int i = 1; i < count; ++i)
  {
    current->next = new BiList{array[i], current, nullptr};
    current = current->next;
  }
   return head;
}


int main()
{
  constexpr size_t max_size = 10;
  int * numbers = new int[max_size];
  size_t count = 0;
  while (count < max_size || !std::cin.eof())
  {
    std::cin >> numbers[count];
    ++count;
  }
  BiList * list = arrayToBiList(numbers, count);
  delete numbers[];
}
