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
    throw std::out_of_range("range err!");
  }

  FwdList* pointer = head;

  if (pointer != nullptr)
  {
    for (int i = 1; i < pos; i++)
    {
      pointer = pointer->next;
    }
  }
  if (pointer == nullptr)
  {
    throw std::logic_error("Current is out of list!");
  }

  for (size_t i = 0; i < c; i++)
  {
    FwdList* nNode = new FwdList{ pointer->value, pointer->next };
    pointer->next = nNode;
    pointer = nNode;
  }

  return pointer;
}

void rmList(FwdList* head)
{
  while (head != nullptr)
  {
    FwdList* temp = head->next;
    delete head;
    head = temp;
  }
}

void showList(std::ostream& out, const FwdList* head)
{
  out << head->value;
  FwdList* pointer = head->next;

  while (pointer != nullptr)
  {
    out << " " << pointer->value;
    pointer = pointer->next;
  }
}

int main()
{
  FwdList* head = new FwdList{ 0, nullptr };
  FwdList* tail = head;

  for (int i = 1; i < 10; i++)
  {
    FwdList* enterPart = nullptr;

    try
    {
      enterPart = new FwdList{ i, nullptr };
    }
    catch (const std::bad_alloc& e)
    {
      rmList(head);
      return 1;
    }

    tail->next = enterPart;
    tail = enterPart;
  }

  while (!std::cin.eof())
  {
    size_t fir = 0, sec = 0;

    std::cin >> fir >> sec;
    if (std::cin.fail())
    {
      break;
    }

    try
    {
      inDuplicates(head, fir, sec);
    }
    catch (std::logic_error& e)
    {
      rmList(head);
      return 1;
    }
  }

  showList(std::cout, head);
  std::cout << "\n";
  rmList(head);
}
