#include <iostream>

struct BiList {
  int value;
  BiList * prev, * next;
};

BiList * convert(int * arr, size_t count)
{
  if (count == 0)
  {
    return nullptr;
  }
  BiList * head = new BiList {arr[0], nullptr, nullptr};
  BiList * current = head;
  for (size_t i = 1; i < count; i++)
  {
    BiList * subhead = new BiList {arr[i], current, nullptr};
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
  int * num = new int[10];
  size_t k = 0;
  while (k < 10 && std::cin >> num[k] && !std::cin.eof())
  {
    k++;
  }
  BiList * listHead = convert(num, k);
  BiList * current = listHead;
  while (current && current->next != nullptr)
  {
    current = current->next;
  }
  while (current != nullptr)
  {
    std::cout << current->value << " ";
    current = current->prev;
  }
  std::cout << '\n';
  deleteBiList(listHead);
  delete[] num;
}
