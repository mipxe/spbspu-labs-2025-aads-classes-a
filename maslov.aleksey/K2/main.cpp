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

int main()
{
  FwdList * head = nullptr;
  FwdList * tail = nullptr;
  try
  {
    for (int i = 0; i < 10; ++i)
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
  while (std::cin >> index >> count && !std::cin.eof())
  {
    if (std::cin.fail())
    {
      break;
    }
    if (index > 0)
    {
      std::cerr << "the element number exceeds the number of element in the list\n";
      freeList(head);
      return 1;
    }
  }
}
