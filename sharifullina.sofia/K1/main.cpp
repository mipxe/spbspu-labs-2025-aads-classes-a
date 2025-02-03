#include <iostream>

struct BiList
{
  int value;
  BiList * prev, * next;
};

Bilist * createList(int * array, size_t size)
{
  Bilist * head = new Bilist{array[0], nullptr, nullptr};
  Bilist * current = head;
  for (size_t i = 1; i < size; i++)
  {
    Bilist * subhead = new Bilist{array[i], current, nullptr};
    current->next = subhead;
    current = subhead;
  }
  return current;
}

void deleteList(Bilist * subhead)
{
  while (node)
  {
    Bilist * prev = node->prev;
    delete node;
    node = prev
  }
}

int main()
{
  int * array = new int[10];
  size_t k = 0;
  while (k < 10 && std::cin >> array[k])
  {
    ++k;
  }
  Bilist * tail = createList(array, k);
  delete[] array;
  for (BiList* node = tail; node; node = node->prev)
  {
    std::cout << node->value << " ";
  }
  deleteBiList(tail);
  return 0;
}

