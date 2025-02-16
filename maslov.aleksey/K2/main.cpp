#include <iostream>
#include <cstddef>
#include <stdexcept>

struct FwdList
{
  int value;
  FwdList * next;
};
void printList(std::ostream & out, const FwdList * head);
void freeList(FwdList * head);
FwdList * duplicateElements(FwdList * head, size_t index, size_t count);

int main()
{
  FwdList * head = nullptr;
  FwdList * tail = nullptr;
  try
  {
    FwdList * newElement = new FwdList{0, nullptr};
    head = newElement;
    tail = newElement;
    for (int i = 1; i < 10; ++i)
    {
      FwdList * newElement = new FwdList{i, nullptr};
      tail->next = newElement;
      tail = newElement;
    }
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Memory error\n";
    freeList(head);
    return 1;
  }
  size_t index = 0, count = 0;
  while (std::cin >> index >> count && !std::cin.eof())
  {
    try
    {
      duplicateElements(head, index, count);
    }
    catch (const std::exception & e)
    {
      freeList(head);
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  printList(std::cout, head);
  std::cout << "\n";
  freeList(head);
}
void printList(std::ostream & out, const FwdList * head)
{
  out << head->value;
  head = head->next;
  while (head)
  {
    out << " " << head->value;
    head = head->next;
  }
}
void freeList(FwdList * head)
{
  while (head)
  {
    FwdList * next = head->next;
    delete head;
    head = next;
  }
}
FwdList * duplicateElements(FwdList * head, size_t index, size_t count)
{
  if (index < 1)
  {
    throw std::invalid_argument("index must be positive");
  }
  FwdList * subhead = head;
  size_t currentIndex = 1;
  while (subhead && currentIndex != index)
  {
    subhead = subhead->next;
    currentIndex++;
  }
  if (subhead == nullptr)
  {
    throw std::out_of_range("out of range");
  }
  FwdList * node = subhead;
  for (size_t i = 0; i < count; ++i)
  {
    FwdList * newElement = new FwdList{subhead->value, node->next};
    node->next = newElement;
    node = newElement;
  }
  return subhead;
}
