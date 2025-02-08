#include <iostream>

struct BiList
{
  int value;
  BiList * prev, * next;
};

void deleteList(BiList* tail)
{
  while (tail != nullptr)
  {
    BiList* back = tail->prev;
    delete tail;
    tail = back;
  }
}

BiList* convertToList(const int* arr, const size_t count)
{
  BiList * head = new BiList { arr[0], nullptr, nullptr };
  BiList* tail = head;
  for (size_t i = 1; i < count; ++i)
  {
    BiList* new_element = nullptr;
    try
    {
      new_element = new BiList{ arr[i], tail, nullptr };
    }
    catch (const std::bad_alloc&)
    {
      deleteList(tail);
      throw;
    }
    tail->next = new_element;
    tail = new_element;
  }
  return tail;
}

void printReverseList(std::ostream& out, const BiList* tail)
{
  out << tail->value;
  tail = tail->prev;
  while (tail != nullptr)
  {
    out << " " << tail->value;
    tail = tail->prev;
  }
}

int main()
{
  int* arr = nullptr;
  try
  {
    arr = new int[10];
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Bad alloc!\n";
    return 1;
  }
  int a = 0;
  size_t count = 0;
  while (!std::cin.eof())
  {
    if (count == 10)
    {
      break;
    }
    std::cin >> a;
    if (std::cin.fail())
    {
      break;
    }
    else
    {
      arr[count++] = a;
    }
  }
  if (count == 0)
  {
    std::cerr << "uncorrect str!\n";
    delete[] arr;
    return 1;
  }
  BiList* list_tail = nullptr;
  try
  {
    list_tail = convertToList(arr, count);
  }
  catch (const std::bad_alloc&)
  {
    delete[] arr;
    std::cerr << "Bad alloc!\n";
    return 1;
  }
  printReverseList(std::cout, list_tail);
  std::cout << "\n";
  deleteList(list_tail);
  delete[] arr;
}
