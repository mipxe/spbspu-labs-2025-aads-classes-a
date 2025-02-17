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
  try
  {
    FwdList* newNode = new FwdList{0, nullptr};
    head = newNode;
    tail = newNode;
    for (int i = 1; i < 10; ++i)
    {
      newNode = new FwdList{i, nullptr};
      tail->next = newNode;
      tail = newNode;
    }
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "ERROR: out of memory\n";
    deleteList(head);
    return 1;
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
  std::cout << current->value;
  current = current->next;
  while (current)
  {
    std::cout << " " << current->value;
    current = current->next;
  }
  std::cout << "\n";
  deleteList(head);
  return 0;
}
