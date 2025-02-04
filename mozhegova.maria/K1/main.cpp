#include <iostream>

struct BiList {
  int value;
  BiList * prev, * next;
};

BiList * convert(const int * const arr, size_t count)
{
  if (count == 0)
  {
    return nullptr;
  }
  BiList * head = new BiList {arr[0], nullptr, nullptr};
  BiList * current = head;
  for (size_t i = 1; i < count; i++)
  {
    BiList * subhead = nullptr;
    try
    {
      subhead = new BiList {arr[i], current, nullptr};
    }
    catch (const std::bad_alloc &)
    {
      deleteBiList(head);
      throw;
    }
    current->next = subhead;
    current = subhead;
  }
  return head;
}

void deleteBiList(BiList * head)
{
  BiList * temp = head;
  while (temp)
  {
    BiList * nextHead = temp->next;
    delete temp;
    temp = nextHead;
  }
}

int main()
{
  int * num = nullptr;
  try
  {
    num = new int[10];
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Out of memory\n";
    return 1;
  }
  size_t k = 0;
  while (k < 10 && std::cin >> num[k] && !std::cin.eof())
  {
    k++;
  }
  BiList * listHead = nullptr;
  try
  {
    listHead = convert(num, k);
  }
  catch (const std::bad_alloc &)
  {
    delete[] num;
    std::cerr << "Out of memory\n";
    return 1;
  }
  BiList * current = listHead;
  while (current && current->next != nullptr)
  {
    current = current->next;
  }
  std::cout << current->value;
  current = current->prev;
  for (size_t i = k - 1; i > 0; i--)
  {
    std::cout << " " << current->value;
    current = current->prev;
  }
  std::cout << '\n';
  deleteBiList(listHead);
  delete[] num;
}
