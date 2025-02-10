#include <iostream>

struct FwdList {
  int value;
  FwdList * next;
};

void deleteList(FwdList * head)
{
  FwdList * temp = head;
  while (temp)
  {
    FwdList * nextHead = temp->next;
    delete temp;
    temp = nextHead;
  }
}

FwdList * duplicate(FwdList * head, size_t index, size_t count)
{
  int num = 0;
  FwdList * current = head;
  for (size_t i = 1; i != index; i++)
  {
    current = current->next;
    ++num;
  }
  for (size_t i = 0; i < count; i++)
  {
    FwdList * subhead = current->next;
    FwdList * node = new FwdList {num, nullptr};
    node->next = subhead->next;
    subhead->next = node;
  }
  return current;
}

int main()
{
  FwdList * head = nullptr;
  FwdList * current = nullptr;
  for (int i = 0; i < 10; i++)
  {
    FwdList * subhead = nullptr;
    try
    {
      subhead = new FwdList {i, nullptr};
    }
    catch (const std::bad_alloc &)
    {
      deleteList(head);
      std::cerr << "Out of memory\n";
      return 1;
    }
    current->next = subhead;
    current = subhead;
  }

  size_t index = 0, count = 0;
  while (std::cin >> index >> count)
  {
    try
    {
      duplicate(head, index, count);
    }
    catch(const std::bad_alloc &)
    {
      deleteList(head);
      std::cerr << "Out of memory\n";
      return 1;
    }
  }
}