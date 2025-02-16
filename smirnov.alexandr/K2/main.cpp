#include <iostream>
#include <cstddef>

struct FwdList
{
  int value;
  FwdList * next;
};

void deleteFwdList(FwdList * head)
{
  while (head != nullptr)
  {
    FwdList * next = head->next;
    delete head;
    head = next;
  }
}

FwdList * createFwdList()
{
  FwdList * head = new FwdList{0, nullptr};
  FwdList * current = head;
  for (int i = 1; i < 10; ++i)
  {
    FwdList * newNode = nullptr;
    try
    {
      newNode = new FwdList{i, nullptr};
    }
    catch (const std::bad_alloc & e)
    {
      deleteFwdList(head);
      throw;
    }
    current->next = newNode;
    current = current->next;
  }
  return head;
}

FwdList * insertDuplicates(FwdList * head, size_t index, size_t count)
{
  if (index < 1)
  {
    throw std::out_of_range("Position is out of range");
  }
  FwdList * current = head;
  for (size_t i = 1; i < index && current != nullptr; ++i)
  {
    current = current->next;
  }
  if (current == nullptr)
  {
    throw std::out_of_range("Position is out of range");
  }
  for (size_t i = 0; i < count; ++i)
  {
    FwdList* newNode = new FwdList{current->value, current->next};
    current->next = newNode;
    current = newNode;
  }
  return head;
}

void printFwdList(const FwdList * head)
{
  std::cout << head->value;
  head = head->next;
  while (head != nullptr)
  {
    std::cout << " " << head->value;
    head = head->next;
  }
}

int main()
{
  FwdList * head = nullptr;
  try
  {
    head = createFwdList();
  }
  catch (const std::bad_alloc & e)
  {
    deleteFwdList(head);
    std::cerr << "Out of memory\n";
    return 1;
  }
  size_t index = 0;
  size_t count = 0;
  while (std::cin >> index >> count && !std::cin.eof())
  {
    try
    {
      head = insertDuplicates(head, index, count);
    }
    catch (const std::out_of_range & e)
    {
      deleteFwdList(head);
      std::cerr << "Position is out of range";
      return 1;
    }
  }
  printFwdList(head);
  std::cout << "\n";
  deleteFwdList(head);
}
