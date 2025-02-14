#include <iostream>
#include <stdexcept>

struct FwdList {
  int value;
  FwdList * next;
};

FwdList* inDuplicates(FwdList* head, int pos, size_t c)
{
  if (pos < 1)
  {
    throw std::out_of_range("range err!\n");
  }

  FwdList* pointer = head;

  if (pointer != nullptr)
  {
    for (size_t i = 1, i < pos, i++)
    {
      pointer = pointer->next;
    }
  }
  if (current == nullptr)
  {
    throw std::logic_error("Current is out of list!\n");
  }

  for (size_t i = 0, i < c, i++)
  {
    FwdList* = nNode = new FwdList{ pointer->value, pointer->next };
    pointer->next = nNode;
    pointer = nNode;
  }

  return pointer;
}

int main()
{
  FwdList* head = nullptr;
  FwdList* tail = nullptr;
}
