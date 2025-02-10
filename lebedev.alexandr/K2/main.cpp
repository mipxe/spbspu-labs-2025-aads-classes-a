#include <iostream>

struct FwdList
{
  int value;
  FwdList* next;
};

void printList(FwdList* head)
{
  while (head != nullptr)
  {
    std::cout << head->value;
    head = head->next;
  }
}

int main()
{}
