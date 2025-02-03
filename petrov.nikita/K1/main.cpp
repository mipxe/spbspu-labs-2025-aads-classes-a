#include <iostream>

struct BiList
{
  int value;
  BiList * prev, * next;
};

BiList * transformArrayToList(int * start, size_t size);

int main()
{
  constexpr size_t max_capacity = 10;
  int * ptr_massive = nullptr;
  try
  {
    ptr_massive = new int[max_capacity];
  }
  catch(const std::bad_alloc & e)
  {
    std::cerr << "ERROR: Out of memory\n";
    return 1;
  }
  size_t size = 0;
  while (size != 10 && !std::cin.eof())
  {
    std::cin >> ptr_massive[size++];
    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(1);
      size--;
    }
  }
  BiList * start_of_list = nullptr;
  if (size)
  {
    int * start_of_massive = ptr_massive;
    BiList * end_of_list = nullptr;
    try
    {
      end_of_list = transformArrayToList(start_of_massive, size);
    }
    catch(const std::bad_alloc & e)
    {
      std::cerr << "ERROR: Out of memory\n";
      return 1;
    }
    std::cout << end_of_list->value;
    for (size_t i = 1; i < size; i++)
    {
      end_of_list = end_of_list->prev;
      std::cout << " " << end_of_list->value;
    }
    start_of_list = end_of_list;
  }
  std::cout << "\n";
  start_of_list = start_of_list->next;
  for (size_t i = 1; i < size; i++)
  {
    delete start_of_list->prev;
    start_of_list = start_of_list->next;
  }
  delete start_of_list;
  delete[] ptr_massive;
}

BiList * transformArrayToList(int * start, size_t size)
{
  BiList * head = nullptr;
  size_t created = 0;
  head = new BiList{ start[0], nullptr, nullptr };
  created++;
  try
  {
    for (size_t i = 1; i < size; i++)
    {
      head->next = new BiList{ start[i], head, nullptr };
      head = head->next;
      created++;
    }
  }
  catch(const std::bad_alloc & e)
  {
    delete head;
    head = head->prev;
    for (size_t i = 1; i < created; i++)
    {
      delete head;
      head = head->prev;
    }
    throw;
  }
  return head;
}
