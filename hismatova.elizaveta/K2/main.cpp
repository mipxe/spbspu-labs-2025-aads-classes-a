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
  for (int i = 0; i < 10; ++i)
  {
    FwdList* newNode = new FwdList{i, nullptr};
    if (head == nullptr)
    {
      head = newNode;
      tail = newNode;
    }
    else
    {
      tail->next = newNode;
      tail = newNode;
    }
  }
  int num1 = 0;
  int num2 = 0;
  while (std::cin >> num1)
  {
    if (!(std::cin >> num2))
    {
      break;
    }
    try
    {
      head = addDubli(head, num1, num2);
    }
    catch (const std::out_of_range& e)
    {
      std::cerr << e.what() << "\n";
      deleteList(head);
      return 1;
    }
  }
  FwdList* current = head;
  while (current)
  {
    std::cout << current->value;
    current = current->next;
    if (current)
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";
  deleteList(head);
  return 0;
}
