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
    FwdList* curr = head;
    for (size_t i = 0; i < index; ++i)
    {
      curr = curr->next;
    }
    FwdList* new_list = curr;
    size_t true_count = 0;
    for (size_t i = 0; i < count; ++i)
    {
      FwdList* duplicate = nullptr;
      try
      {
        duplicate = new FwdList{new_list->value, new_list->next};
        true_count++;
      }
      catch (const std::bad_alloc&)
      {
        for (size_t i = 0; i < true_count; ++i)
        {
          FwdList* next_curr = curr->next;
          delete curr;
          curr = next_curr;
        }
        throw;
      }
      new_list->next = duplicate;
      new_list = duplicate;
    }
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
  int index = 0, count = 0, size = 10;
  while (std::cin >> index >> count)
  {
    if (index > size || index <= 0 || count < 0)
    {
      deleteList(head);
      return 1;
    }
    try
    {
      insertDuplicates(head, index - 1, count);
    }
    catch (const std::bad_alloc&)
    {
      deleteList(head);
      std::cerr << "Not enough memory\n";
      return 1;
    }
    size += count;
  }
  printList(std::cout, head);
  std::cout << "\n";
  deleteList(head);
  return 0;
}
