#include <iostream>

struct BiList
{
  int value;
  BiList * prev, * next;
};

void deleteList(BiList* head)
{
  while (head != nullptr)
  {
    BiList* subHead = head->next;
    delete head;
    head = subHead;
  }
}

BiList* convert(const int* arr, size_t size)
{
  if (size == 0)
  {
    return nullptr;
  }

  BiList* head = nullptr;
  BiList* tail = nullptr;

  try
  {
    head = new BiList{ arr[0], nullptr, nullptr };
    tail = head;

    for (size_t created = 1; created < size; created++)
    {
      BiList* temp = tail;
      tail = new BiList{ arr[created], temp, nullptr };
      temp->next = tail;
    }
  }
  catch (const std::bad_alloc& e)
  {
    deleteList(head);
    throw;
  }
  return tail;
}

int main()
{
  int* arr = new int[10];
  size_t size = 0;
  std::cin >> arr[0];

  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      break;
    }
    size++;
    if (size == 10)
    {
      break;
    }

    std::cin >> arr[size];
  }

  BiList* head = nullptr;
  BiList* tail = nullptr;

  if (size == 0)
  {
    delete[] arr;
    return 0;
  }

  try
  {
    tail = convert(arr, size);
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "Memory allocation error!\n";
    delete[] arr;
    return 2;
  }

  std::cout << tail->value;
  BiList* subtail = tail->prev;
  for (size_t i = 0; i < size - 1; i++)
  {
    if (subtail->prev == nullptr)
    {
      head = subtail;
    }
    std::cout << ' ' << subtail->value;
    subtail = subtail->prev;
  }
  std::cout << '\n';

  deleteList(head);
  delete[] arr;
  return 0;
}
