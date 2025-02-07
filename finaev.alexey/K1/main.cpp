#include <iostream>

struct BiList
{
  int value;
  BiList* prev, * next;
};

void deleteList(BiList* p)
{
  while (p != nullptr)
  {
    BiList* back = p->prev;
    delete p;
    p = back;
  }
}

BiList* convertToList(const int* arr, const size_t count)
{
  BiList* head = nullptr;
  try
  {
    head = new BiList{ arr[0], nullptr, nullptr };
  }
  catch (const std::bad_alloc&)
  {
    throw;
  }
  BiList* p = head;
  for (size_t i = 1; i < count; ++i)
  {
    try
    {
      p->next = new BiList{ arr[i], p, nullptr };
    }
    catch (const std::bad_alloc&)
    {
      deleteList(p);
      throw;
    }
    p = p->next;
  }
  return p;
}

void printList(std::ostream& out, const BiList* p)
{
  out << p->value;
  p = p->prev;
  while (p != nullptr)
  {
    out << " " << p->value;
    p = p->prev;
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
  BiList* p = nullptr;
  try
  {
    p = convertToList(arr, count);
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Bad alloc!\n";
    return 1;
  }
  printList(std::cout, p);
  std::cout << "\n";
  deleteList(p);
  delete[] arr;
}
