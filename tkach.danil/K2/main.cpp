#include <iostream>
#include <stdexcept>
#include <cstddef>

namespace
{
  struct FwdList {
    int value;
    FwdList * next;
  };

  void deleteList(FwdList* head)
  {
    while (head != nullptr)
    {
      FwdList* next_head = head->next;
      delete head;
      head = next_head;
    }
  }

  FwdList* insertDuplicates(FwdList* const head, const size_t index, const size_t count)
  {
    if (count == 0)
    {
      return nullptr;
    }
    FwdList* curr = head;
    for (size_t i = 0; i < index && curr != nullptr; ++i)
    {
      curr = curr->next;
    }
    if (curr == nullptr)
    {
      throw std::out_of_range("Index is bigger than size");
    }
    FwdList* duplicate_head = new FwdList{curr->value, nullptr};
    FwdList* duplicate_tail = duplicate_head;
    for (size_t i = 0; i < count - 1; ++i)
    {
      FwdList* duplicate = nullptr;
      try
      {
        duplicate = new FwdList{duplicate_tail->value, nullptr};
      }
      catch (const std::bad_alloc&)
      {
        deleteList(duplicate_head);
        throw;
      }
      duplicate_tail->next = duplicate;
      duplicate_tail = duplicate;
    }
    FwdList* temp = curr->next;
    curr->next = duplicate_head;
    duplicate_tail->next = temp;
    return curr;
  }

  void printList(std::ostream& out, const FwdList* head)
  {
    if (head == nullptr)
    {
      return;
    }
    out << head->value;
    head = head->next;
    while (head != nullptr)
    {
      out << " " << head->value;
      head = head->next;
    }
  }

}

int main()
{
  FwdList* head = nullptr;
  FwdList* tail = nullptr;
  try
  {
    head = new FwdList{0, nullptr};
    tail = head;
    for (int i = 1; i < 10; ++i)
    {
      FwdList* new_list = new FwdList{i, nullptr};
      tail->next = new_list;
      tail = new_list;
    }
  }
  catch (const std::bad_alloc&)
  {
    deleteList(head);
    std::cerr << "Not enough memory\n";
    return 1;
  }
  int index = 0, count = 0;
  while (std::cin >> index >> count)
  {
    if (index <= 0 || count < 0)
    {
      deleteList(head);
      return 1;
    }
    try
    {
      insertDuplicates(head, index - 1, count);
    }
    catch (const std::exception& e)
    {
      deleteList(head);
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  printList(std::cout, head);
  std::cout << "\n";
  deleteList(head);
  return 0;
}
