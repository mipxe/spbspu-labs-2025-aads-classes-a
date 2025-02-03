#include <iostream>

struct BiList
{
  int value;
  BiList * prev, * next;
};

BiList* convert(int* arr, size_t size)
{
  BiList* head = nullptr;
  BiList* tail = head;
  head = new BiList{arr[0], nullptr, nullptr};

  for (size_t i = 1; i < size; i++)
  {
    BiList* temp = tail;
    tail = new BiList{arr[i], temp, nullptr};
    temp->next = tail;
  }
  return tail;
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
  BiList* tail = convert(arr, size);

  std::cout << tail->value;
  BiList* subtail = tail;
  for (size_t i = 0; i < size - 1; i++)
  {
    subtail = subtail->prev;
    std::cout << ' ' << subtail->value;
  }
  deleteList(subtail);
  return 0;
}
