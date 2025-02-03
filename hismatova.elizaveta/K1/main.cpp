#include <iostream>
#include <stdexcept>

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
  while (head)
  {
    BiList* nextNode = head->next;
    delete head;
    head = nextNode;
  }
}
int main()
{
  const int maxi = 10;
  int* numbers = nullptr;
  try
  {
    numbers = new int[maxi];
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "ERROR: out of memory\n";
    return 1;
  }
  int count = 0;
  while (count < maxi && std::cin >> numbers[count])
  {
    ++count;
  }
  if (std::cin.fail() && !std::cin.eof())
  {
    std::cerr << "ERROR: invalid input\n";
    delete[] numbers;
    return 1;
  }
  BiList* listHead = nullptr;
  try
  {
    listHead = arrayToBiList(numbers, count);
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "ERROR: out of memory\n";
    delete[] numbers;
    return 1;
  }
  if (listHead)
  {
    BiList* current = listHead;
    while (current->next)
    {
      current = current->next;
    }
    while (current)
    {
      std::cout << current->value;
      current = current->prev;
      if (current != nullptr)
      {
        std::cout << " ";
      }
    }
    std::cout << "!\n";
  }
  deleteList(listHead);
  delete[] numbers;
  return 0;
}
