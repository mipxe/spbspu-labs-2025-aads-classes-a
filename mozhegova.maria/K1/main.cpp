#include <iostream>

struct BiList {
  int value;
  BiList * prev, * next;
};

BiList * convert(int * arr, size_t count)
{
  BiList * head = new BiList {arr[0], nullptr};

  for (size_t i = 1; i < count; i++)
  {
    BiList * subhead = new BiList {arr[i], nullptr};
    head->prev = head;
    head->next = subhead;
    head = subhead;
  }
  head->next = nullptr;
  return head;
}

void deleteBiList(BiList * head)
{
  while (head != nullptr)
  {
    BiList * temp = head;
    head = head->next;
    delete temp;
  }
}

int main()
{
  int * num = new int[10];
  size_t k = 0;
  while (k < 10 || !std::cin.eof())
  {
    int a = 0;
    std::cin >> a;
    num[k++] = a;
  }
  BiList * list = convert(num, 10);
  while (list != nullptr)
  {
    std::cout << list->value << " ";
    list = list->prev;
  }
  std::cout << '\n';
  deleteBiList(list);
}
