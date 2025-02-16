#include <iostream>
#include <stdexcept>

struct FwdList {
  int value;
  FwdList* next;
};

void deleteList(FwdList* head)
{
  while (head != nullptr)
  {
    FwdList* subHead = head->next;
    delete head;
    head = subHead;
  }
}

FwdList* addNewElems(FwdList* head, size_t i, size_t count)
{
  if (i < 1)
  {
    throw std::logic_error("out of range\n");
  }
  FwdList* ptr = head;
  for (size_t j = 1; (ptr != nullptr) && (j < i) ; ++j)
  {
    ptr = ptr->next;
  }
  if (ptr == nullptr)
  {
    throw std::logic_error("out of range!\n");
  }
  for (size_t j = 0; j < count; ++j)
  {
    FwdList* new_el = new FwdList{ ptr->value, ptr->next };
    ptr->next = new_el;
    ptr = new_el;
  }
  return ptr;
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
    std::cin >> b;
    if (std::cin.fail())
    {
      break;
    }
    try
    {
      addNewElems(head, a, b);
    }
    catch(...)
    {
      deleteList(head);
      std::cerr << "uncorrect creation\n";
      return 1;
    }
  }
  printList(std::cout, head);
  std::cout << "\n";
  deleteList(head);
}
