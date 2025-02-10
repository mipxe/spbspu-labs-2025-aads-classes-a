#include <iostream>

struct FwdList
{
  int value;
  FwdList * next;
};

int main()
{
  constexpr size = 10;
  int index = 0;
  int count = 0;
  try
  {
    FwdList * head = new FwdList{0, nullptr};
    FwdList * subhead = head;
    for (size_t i = 1; i < size; i++)
    {
      FwdList * node = nullptr;
      node = new FwdList{i, nullptr};
      subhead->next = node;;
      subhead = node;
    }
    delete subhead;
    i = 0;
  }
  catch(std::bad_alloc &)
  {
    return 1;
  }
  while (!std::cin.eof() && std::cin >> number)
  {

  }
}
