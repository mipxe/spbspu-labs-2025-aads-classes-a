#include <iostream>

struct FwdList
{
  int value;
  FwdList * next;
};

FwdList * duplicateElementInsideList(FwdList * head, size_t pos, size_t dupl_number);
void clearList(FwdList * head);
void outputListElements(std::ostream & out, const FwdList * head);

int main()
{
  FwdList * head = nullptr;
  int element = 0;
  try
  {
    head = new FwdList{ element++, nullptr };
    FwdList * ptr_list = head;
    while (element != 10)
    {
      ptr_list->next = new FwdList{ element++, nullptr };
      ptr_list = ptr_list->next;
    }
  }
  catch(const std::bad_alloc & e)
  {
    clearList(head);
    std::cerr << "ERROR: Out of memory" << "\n";
    return 1;
  }
  size_t list_length = 10;
  size_t dupl_number = 0;
  size_t pos = 0;
  try
  {
    do
    {
      dupl_number = 0;
      std::cin >> pos >> dupl_number;
      if ((pos > list_length || pos <= 0) && std::cin)
      {
        throw std::out_of_range("ERROR: Incorrect position of element");
      }
      else if (dupl_number == 0)
      {
        continue;
      }
      list_length += dupl_number;
      duplicateElementInsideList(head, pos, dupl_number);
    }
    while (!std::cin.eof() && std::cin);
  }
  catch(const std::out_of_range & e)
  {
    clearList(head);
    std::cerr << e.what() << '\n';
    return 2;
  }
  catch(const std::bad_alloc & e)
  {
    clearList(head);
    std::cerr << "ERROR: Out of memory" << "\n";
    return 1;
  }
  outputListElements(std::cout, head);
  std::cout << "\n";
  clearList(head);
}

FwdList * duplicateElementInsideList(FwdList * head, size_t pos, size_t dupl_number)
{
  for (size_t i = 0; i < pos - 1; i++)
  {
    head = head->next;
  }
  FwdList * duplicable_element = head;
  FwdList * after_dupl_element = head->next;
  for (size_t i = 0; i < dupl_number; i++)
  {
    head->next = new FwdList{ duplicable_element->value, after_dupl_element };
    head = head->next;
  }
  return duplicable_element;
}

void clearList(FwdList * head)
{
  FwdList * newhead = nullptr;
  while (head != nullptr)
  {
    newhead = head->next;
    delete head;
    head = newhead;
  }
}

void outputListElements(std::ostream & out, const FwdList * head)
{
  out << head->value;
  head = head->next;
  while (head != nullptr)
  {
    out << " " << head->value;
    head = head->next;
  }
}
