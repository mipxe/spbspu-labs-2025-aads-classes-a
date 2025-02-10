#include <iostream>

struct FwdList {
  int value;
  FwdList * next;
};

FwdList* inDuplicates(FwdList* head, int pos, int c)
{
  FwdList* current = head;
  FwdList* prev = nullptr;
  for (int i = 1, i < pos, i++)
  {
    if (current == nullptr)
    {
      break;
    }
    prev = current;
    current = currrent->next;
  }
}

int main()
{}
