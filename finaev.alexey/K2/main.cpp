#include <iostream>

struct FwdList {
  int value;
  FwdList* next;
};

FwdList* addNewEls(FwdList* head, size_t i, size_t count)
{
  FwdList* tail = head;
  for (size_t j = 0;(tail != nullptr) && (j < i); ++j)
  {
    tail = tail->next;
  }
  for (size_t j = 0; j < count; ++j)
  {
    FwdList* new_el = new FwdList{ tail->value, tail->next };
    tail->next = new_el;
    tail = new_el;
  }
  return tail;
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
      throw;
    }
    tail->next = new_element;
    tail = new_element;
  }
  ListIterator head_ptr;
  head_ptr.node = head;
  int a = 0;
  int b = 0;
  while (!std::cin.eof())
  {
    std::cin >> a;
    std::cin >> b;
    if (std::cin.fail())
    {
      break;
    }
  }
}
