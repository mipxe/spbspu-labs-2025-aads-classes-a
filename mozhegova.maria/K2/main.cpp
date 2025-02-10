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
  FwdList * current = head;
  for (size_t i = 1; i < index; i++)
  {
    if (current == nullptr)
    {
      throw std::out_of_range("Position exceeds the list size");
    }
    current = current->next;
  }
  for (size_t i = 0; i < count; i++)
  {
    FwdList * node = new FwdList {current->value, nullptr};
    node->next = current->next;
    current->next = node;
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
    if (head == nullptr)
    {
      head = subhead;
      current = subhead;
    }
    current->next = subhead;
    current = subhead;
  }

  size_t index = 0, count = 0;
  while (std::cin >> index >> count && !std::cin.eof())
  {
    try
    {
      duplicate(head, index, count);
    }
    catch (const std::bad_alloc &)
    {
      deleteList(head);
      std::cerr << "Out of memory\n";
      return 1;
    }
    catch (const std::out_of_range & e)
    {
      deleteList(head);
      std::cerr << e.what() << "\n";
      return 1;
    }
  }

  FwdList * temp = head;
  std::cout << temp->value;
  for (temp = temp->next; temp != nullptr; temp = temp->next)
  {
    std::cout << " " << temp->value;
  }
  std::cout << "\n";
  deleteList(head);
}
