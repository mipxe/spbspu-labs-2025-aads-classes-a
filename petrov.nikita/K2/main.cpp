#include <iostream>

struct FwdList
{
  int value;
  FwdList * next;
};

FwdList * duplicateElementInsideList(FwdList * head, size_t pos, size_t dupl_number);

int main()
{
  FwdList * head = nullptr;
  size_t i = 0;
  head = new FwdList;
  FwdList * ptr_list = head;
  ptr_list->value = i++;
  while (i != 10)
  {
    ptr_list->next = new FwdList;
    ptr_list->value = i;
    i++;
  }
  size_t dupl_number = 0;
  size_t pos = 0;
  size_t i = 0;
  do
  {
    dupl_number = 0;
    std::cin >> pos >> dupl_number;
    if (dupl_number == 0)
    {
      continue;
    }
    duplicateElementInsideList(head, pos, dupl_number);
  }
  while (i != 10 && !std::cin.eof());
  std::cout << head->value;
  head = head->next;
  while (head != nullptr)
  {
    std::cout << " " << head->value;
    head = head->next;
  }
}

FwdList * duplicateElementInsideList(FwdList * head, size_t pos, size_t dupl_number)
{
  for (size_t i = 0; i < pos - 1; i++)
  {
    head = head->next;
  }
}
