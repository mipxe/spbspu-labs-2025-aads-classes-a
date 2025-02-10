#include <iostream>

struct FwdList
{
  int value;
  FwdList * next;
};

void freeList(FwdList * head)
{
    FwdList * subhead = head;
    while (subhead)
    {
      FwdList * next = subhead->next;
      delete subhead;
      subhead = next;
    }
}

size_t getLength(FwdList * head)
{
  size_t length = 0;
  FwdList * subhead = head;
  while (subhead)
  {
    length++;
    subhead = subhead->next;
  }
  return length;
}

FwdList * duplicate(FwdList * head, size_t index, size_t count)
{
  FwdList * subhead = head;
  size_t currentIndex = 1;
  while (subhead && currentIndex != index)
  {
    subhead = subhead->next;
    currentIndex++;
  }
  FwdList * node = subhead;
  try
  {
    for (size_t i = 0; i < count; ++i)
    {
      FwdList * newElement = new FwdList{subhead->value, node->next};
      node->next = newElement;
      node = newElement;
    }
  }
  catch (const std::bad_alloc &)
  {
    freeList(head);
    throw;
  }

  return subhead;
}

int main()
{
  FwdList * head = nullptr;
  FwdList * tail = nullptr;
  try
  {
    for (int i = 1; i < 11; ++i)
    {
      FwdList * newElement = new FwdList{i, nullptr};
      if (head == nullptr)
      {
        head = newElement;
        tail = newElement;
      }
      else
      {
        tail->next = newElement;
        tail = newElement;
      }
    }
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Memory error\n";
    freeList(head);
    return 1;
  }
  size_t index = 0, count = 0;
  while (std::cin >> index && !std::cin.eof())
  {
    if (std::cin.fail())
    {
      break;
    }
    if (index > getLength(head))
    {
      std::cerr << "the element number exceeds the number of element in the list\n";
      freeList(head);
      return 1;
    }
    if (std::cin >> count)
    {
      if (std::cin.fail())
      {
        break;
      }
      try
      {
        duplicate(head, index, count);
      }
      catch (const std::bad_alloc &)
      {
        std::cerr << "Memory error\n";
        return 1;
      }
    }
    else
    {
      break;
    }
  }
  FwdList * subhead = head;
  while (subhead)
  {
    std::cout << subhead->value;
    if (subhead->next)
    {
      std::cout << " ";
    }
    subhead = subhead->next;
  }
  std::cout << "\n";
  freeList(head);
}
