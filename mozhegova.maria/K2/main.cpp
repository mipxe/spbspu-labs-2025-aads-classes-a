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
  if (index < 1)
  {
    throw std::out_of_range("Out of range");
  }
  FwdList * current = head;
  for (size_t i = 1; i < index && current != nullptr; i++)
  {
    current = current->next;
  }
  if (current == nullptr)
  {
    throw std::out_of_range("Out of range");
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
  try
  {
    head = new FwdList {0, nullptr};
    current = head;
    for (int i = 1; i < 10; i++)
    {
      FwdList * subhead = new FwdList {i, nullptr};
      current->next = subhead;
      current = subhead;
    }
  }
  catch (const std::bad_alloc &)
  {
    deleteList(head);
    std::cerr << "Out of memory\n";
    return 1;
  }

  size_t index = 0, count = 0;
  while (std::cin >> index >> count && !std::cin.eof())
  {
    try
    {
      duplicate(head, index, count);
    }
    catch (const std::exception & e)
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
