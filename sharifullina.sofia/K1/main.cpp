#include <iostream>

struct Bilist
{
  int value;
  Bilist * prev;
  Bilist * next;
};

Bilist * createList(const int * array, size_t size)
{
  if (size == 0)
  {
    return nullptr;
  }
  Bilist * head = nullptr;
  Bilist * current = nullptr;
  try
  {
    head = new Bilist{array[0], nullptr, nullptr};
    current = head;
    for (size_t i = 1; i < size; i++)
    {
      Bilist* subhead = new Bilist{array[i], current, nullptr};
      current->next = subhead;
      current = subhead;
    }
  }
  catch (const std::bad_alloc&)
  {
    while (head)
    {
      Bilist* next = head->next;
      delete head;
      head = next;
    }
    throw;
  }
  return current;
}

void deleteList(Bilist * subhead)
{
  while (subhead)
  {
    Bilist * prev = subhead->prev;
    delete subhead;
    subhead = prev;
  }
}

int main()
{

  int * array = nullptr;
  try
  {
    array = new int[10];
    size_t k = 0;
    while (k < 10 && std::cin >> array[k])
    {
      ++k;
    }
    Bilist* tail = createList(array, k);
    delete[] array;
    for (Bilist* node = tail; node; node = node->prev)
    {
        std::cout << node->value << (node->prev ? " " : "\n");
    }
    deleteList(tail);
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "out of memory" << std::endl;
    delete[] array;
    return 1;
  }
  return 0;
}
