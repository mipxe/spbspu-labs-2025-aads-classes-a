#include <iostream>

struct BiList
{
  int value;
  BiList * prev, * next;
};

BiList* convert(int* arr, size_t size)
{
  if (size == 0)
  {
    return nullptr;
  }

  BiList* head = new BiList{ arr[0], nullptr, nullptr };
  BiList* tail = head;

  for (size_t i = 1; i < size; i++)
  {
    BiList* temp = tail;
    tail = new BiList{ arr[i], temp, nullptr };
    temp->next = tail;
  }
  return head;
}

void deleteList(BiList* head)
{
  while (head != nullptr)
  {
    BiList* subHead = head->next;
    delete head;
    head = subHead;
  }
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
  try
  {
    head = convert(arr, size);
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "Memory allocation error!\n";
    return 2;
  }

  BiList* tail = head;
  while (tail && tail->next)
  {
    tail = tail->next;
  }

  std::cout << tail->value;
  BiList* subtail = tail->prev;
  for (size_t i = 0; i < size - 1; i++)
  {
    std::cout << ' ' << subtail->value;
    subtail = subtail->prev;
  }
  std::cout << '\n';
  
  deleteList(head);
  delete[] arr;
  return 0;
}
