#include <iostream>

namespace
{
  struct FwdList {
    int value;
    FwdList * next;
  };

  FwdList* insertDuplicates(FwdList* head, size_t index, size_t count)
  {
    FwdList* curr = head;
    for (size_t i = 0; i < index && curr != nullptr; ++i)
    {
      curr = curr->next;
    }
    for (size_t i = 0; i < count; ++i)
    {
      FwdList* duplicate = new FwdList{curr->value, curr->next};
      curr->next = duplicate;
      curr = duplicate;
    }

    return curr;
  }

  void printList(FwdList* head)
  {
    FwdList* current = head;
    std::cout << current->value;
    current = current->next;
    while (current != nullptr)
    {
      std::cout << " " << current->value;
      current = current->next;
    }
  }
}

int main()
{
  FwdList* head = new FwdList{0, nullptr};
  FwdList* tail = head;
  for (int i = 1; i < 10; ++i)
  {
    FwdList* new_list = new FwdList{i, nullptr};
    tail->next = new_list;
    tail = new_list;
  }
  size_t index = 0, count = 0;
  while(std:: cin >> index >> count)
  {
    insertDuplicates(head, index-1, count);
  }
  printList(head);
  std::cout << "\n";
  return 0;
}
