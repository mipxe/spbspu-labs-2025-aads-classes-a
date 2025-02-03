#include <iostream>

struct BiList
{
  int value;
  BiList * prev, * next;
};

BiList * toBiList(int * array, size_t size);
void print(BiList * head);

int main()
{
  int * numbers = nullptr;
  size_t count = 0;
  const size_t size = 10;
  try
  {
    int number = 0;
    numbers = new int[size];
    while (count < size && std::cin >> number && !std::cin.eof())
    {
      numbers[count++] = number;
    }
  }
  catch (const std::bad_alloc & e)
  {
    std::cerr << "Memory error\n";
  }
  BiList * head = toBiList(numbers, count);
  print(head);
  std::cout << "\n";
  delete[] numbers;
}

void print(BiList * head)
{
  BiList * subhead = head;
  while(subhead->next)
  {
    subhead = subhead->next;
  }
  while(subhead)
  {
    std::cout << subhead->value << " ";
    BiList * prev = subhead->prev;
    delete subhead;
    subhead = prev;
  }
}

BiList * toBiList(int * array, size_t size)
{
  BiList * head = new BiList;
  head->value = array[0];
  head->prev = nullptr;
  head->next = nullptr;
  BiList* subhead = head;
  for (size_t i = 1; i < size; ++i)
  {
    BiList* node = new BiList;
    node->value = array[i];
    node->prev = subhead;
    node->next = nullptr;
    subhead->next = node;
    subhead = node;
  }
  return head;
}

