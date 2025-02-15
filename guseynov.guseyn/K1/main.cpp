#include <iostream>

struct BiList
{
  int value;
  BiList * prev, * next;
};

BiList * toBiList(const int * arr, size_t size);
void print(std::ostream & out, BiList * head, const size_t count);
void clearBiList(BiList * head);

int main()
{
  size_t i = 0;
  int number = 0;
  constexpr size_t size = 10;
  int *arr = nullptr;
  try
  {
    arr = new int[size];
    while (i < size && std::cin >> number && !std::cin.eof())
    {
      arr[i++] = number;
    }
    BiList * head = toBiList(arr, i);
    if (head != nullptr)
    {
      print(std::cout, head, i);
      clearBiList(head);
    }
  }
  catch(std::bad_alloc &)
  {
    delete[] arr;
    return 1;
  }
  std::cout << "\n";
  delete[] arr;
}

void print(std::ostream & out, BiList * head, const size_t count)
{
  BiList * subhead = head;
  while(subhead->next)
  {
    subhead = subhead->next;
  }
    for (size_t i = 1; i < count; i++)
  {
    out << subhead->value << " ";
    subhead = subhead->prev;
  }
  out << subhead->value;
}

BiList * toBiList(const int * arr, size_t size)
{
  if (size == 0)
  {
    return nullptr;
  }
  BiList * head = new BiList{arr[0], nullptr, nullptr};
  BiList * subhead = head;
  for (size_t i = 1; i < size; ++i)
  {
    BiList * record = nullptr;
    try
    {
      record = new BiList{arr[i], subhead, nullptr};
    }
    catch (const std::bad_alloc &)
    {
      clearBiList(head);
      throw;
    }
    subhead->next = record;
    subhead = record;
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
