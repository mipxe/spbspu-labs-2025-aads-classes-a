#include <iostream>
#include <stdexcept>

struct FwdList
{
  int value;
  FwdList* next;
};
void deleteList(FwdList* head)
{
  while (head)
  {
    FwdList* temp = head;
    head = head->next;
    delete temp;
  }
}
FwdList* addDubli(FwdList* head, int index, int dubli)
{
  if (index < 1)
  {
    throw std::out_of_range("ERROR: invalid index");
  }
  FwdList* current = head;
  for (int i = 1; current != nullptr && i < index; ++i)
  {
    current = current->next;
  }
  if (current == nullptr)
  {
    throw std::out_of_range("ERROR: index is more than list size");
  }
  for (int i = 0; i < dubli; ++i)
  {
    FwdList* newNode = new FwdList{current->value, current->next};
    current->next = newNode;
    current = newNode;
  }
  return head;
}

int main()
{
  FwdList* head = nullptr;
  FwdList* tail = nullptr;
}
