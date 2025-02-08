#include <iostream>
#include <stdexcept>

struct BiList
{
  int value;
  BiList* prev;
  BiList* next;
};
void deleteList(BiList* tail)
{
  while (tail)
  {
    BiList* prevNode = tail->prev;
    delete tail;
    tail = prevNode;
  }
}
BiList* arrayToBiList(const int* array, int count)
{
  if (count == 0)
  {
    return nullptr;
  }
  BiList* tail = nullptr;
  for (int i = 0; i < count; ++i)
  {
    BiList* newNode = nullptr;
    try
    {
      newNode = new BiList{array[i], tail, nullptr};
    }
    catch (const std::bad_alloc&)
    {
      deleteList(tail);
      throw;
    }
    if (tail)
    {
      tail->next = newNode;
    }
    tail = newNode;
  }
  return tail;
}
int main()
{
  const int maxi = 10;
  int* numbers = nullptr;
  size_t count = 0;
  try
  {
    numbers = new int[maxi];
    int temp = 0;
    while (count < maxi && std::cin >> temp && !std::cin.eof())
    {
      numbers[count++] = temp;
    }
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "ERROR: out of memory\n";
    delete[] numbers;
    return 1;
  }
  BiList* listTail = nullptr;
  try
  {
    listTail = arrayToBiList(numbers, count);
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "ERROR: out of memory\n";
    delete[] numbers;
    return 1;
  }
  BiList* saveTail = listTail;
  while (listTail)
  {
    std::cout << listTail->value;
    listTail = listTail->prev;
    if (listTail)
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";
  deleteList(saveTail);
  delete[] numbers;
  return 0;
}
