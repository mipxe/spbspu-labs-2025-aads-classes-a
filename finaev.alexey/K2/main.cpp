#include <iostream>

struct FwdList {
  int value;
  FwdList* next;
};

void addNewElems(FwdList* head, size_t i, size_t count)
{
  FwdList* ptr = head;
  if (ptr != nullptr)
  {
    for (size_t j = 1; j < i ; ++j)
    {
      while (ptr->value == ptr->next->value)
      {
        ptr = ptr->next;
      }
      ptr = ptr->next;
    }
    for (size_t j = 0; j < count; ++j)
    {
      FwdList* new_el = new FwdList{ ptr->value, ptr->next };
      ptr->next = new_el;
      ptr = new_el;
    }
  }
}

void printList(std::ostream& out, const FwdList* head)
{
  out << head->value;
  FwdList* ptr = head->next;
  while (ptr != nullptr)
  {
    out << " " << ptr->value;
    ptr = ptr->next;
  }
}

void deleteList(FwdList* head)
{
  while (head->next != nullptr)
  {
    FwdList* subHead = head->next;
    delete head;
    head = subHead;
  }
}

int main()
{
  FwdList* head = new FwdList{ 0, nullptr };
  FwdList* tail = head;
  for (int i = 1; i < 10; ++i)
  {
    FwdList* new_element = nullptr;
    try
    {
      new_element = new FwdList{ i, nullptr };
    }
    catch (const std::bad_alloc&)
    {
      deleteList(head);
      return 1;
    }
    tail->next = new_element;
    tail = new_element;
  }
  while (!std::cin.eof())
  {
    size_t a = 0;
    size_t b = 0;
    std::cin >> a;
    if (a > 10)
    {
      std::cerr << "out of range\n";
      return 1;
    }
    std::cin >> b;
    if (std::cin.fail())
    {
      break;
    }
    addNewElems(head, a, b);
  }
  printList(std::cout, head);
  deleteList(head);
}
