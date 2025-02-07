#include <iostream>

struct BiList
{
  int value;
  BiList * prev, * next;
};

BiList * toBiList(int * array, size_t size);
void print(std::ostream & out, BiList * head);

int main()
{
  int * numbers = nullptr;
  size_t count = 0;
  constexpr size_t size = 10;
  try
  {
    int number = 0;
    numbers = new int[size];
    while (count < size && std::cin >> number && !std::cin.eof())
    {
      numbers[count++] = number;
    }
    BiList * head = toBiList(numbers, count);
    print(std::cout, head);
    clearBiList(head);
  }
  catch (const std::bad_alloc &)
  {
    delete[] numbers;
    std::cerr << "Memory error\n";
    return 1;
  }
  std::cout << "\n";
  delete[] numbers;
}
void print(std::ostream & out, BiList * head)
{
  BiList * subhead = head;
  while(subhead->next)
  {
    subhead = subhead->next;
  }
  while(subhead)
  {
    out << subhead->value;
    BiList * prev = subhead->prev;
    delete subhead;
    subhead = prev;
    if (subhead != nullptr)
    {
      out << " ";
    }
  }
}
BiList * toBiList(int * array, size_t size)
{
  BiList * head = new BiList{array[0], nullptr, nullptr};
  BiList * subhead = head;
  for (size_t i = 1; i < size; ++i)
  {
    BiList * node = nullptr;
    try
    {
      node = new BiList{array[i], subhead, nullptr};
    }
    catch (const std::bad_alloc &)
    {
      clearBiList(head);
      throw;
    }
    subhead->next = node;
    subhead = node;
  }
  return head;
}
void clearBiList(BiList * head)
{
  BiList * subhead = head;
  while (subhead != nullptr)
  {
    BiList * next = subhead->next;
    delete subhead;
    subhead = next;
  }
}
