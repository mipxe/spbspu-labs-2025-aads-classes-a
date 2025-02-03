#include <iostream>

struct BiList
{
  int value;
  BiList* prev;
  BiList* next;
};
BiList* arrayToBiList(int* array, int count)
{
  if (count == 0)
  {
    return nullptr;
  }
  BiList* head = nullptr;
  BiList* tail = nullptr;
  for (int i = 0; i < count; ++i)
  {
    BiList* newNode = new BiList();
    newNode->value = array[i];
    newNode->prev = tail;
    newNode->next = nullptr;
    if (tail)
    {
      tail->next = newNode;
    }
    else
    {
      head = newNode;
    }
    tail = newNode;
  }
  return head;
}
void deleteList(BiList* head)
{
  BiList* current = head;
  while (current)
  {
    BiList* nextNode = current->next;
    delete current;
    current = nextNode;
  }
}
int main()
{
  const int maxi = 10;
  int numbers[maxi];
  int count = 0;
  while (count < maxi && std::cin >> numbers[count])
  {
    ++count;
  }
  BiList* listHead = arrayToBiList(numbers, count);
  BiList* current = listHead;
  if (current)
  {
    while (current->next)
    {
      current = current->next;
    }
    while (current)
    {
      std::cout << current->value << " ";
      current = current->prev;
    }
    std::cout << "\n";
  }
  deleteList(listHead);
  return 0;
}
