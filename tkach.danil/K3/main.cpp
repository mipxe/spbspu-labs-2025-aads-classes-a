#include <iostream>
#include <string>
#include <cstddef>

namespace
{
  template< class T >
  struct List {
    T data;
    List< T > * next;
  };

  void deleteMtx(int** matrix, size_t m)
  {
    for (size_t i = 0; i < m; ++i)
    {
      delete[] matrix[i];
    }
    delete[] matrix;
  }

  template< class T >
  void deleteList(List< T >* head)
  {
    while (head != nullptr)
    {
      List< T >* next_head = head->next;
      delete head;
      head = next_head;
    }
  }

  template< class T >
  void deleteListOfLists(List< List< T >* > * head)
  {
    while (head != nullptr)
    {
      List< List< T >* > * next_head = head->next;
      deleteList(head->data);
      head = next_head;
    }
  }

  List< List< int > * > * convert(const int * const * d, const size_t m, const size_t * n)
  {
    List< List< int > * > * head = nullptr;
    size_t first = 0;
    while (n[first] == 0)
    {
      first++;
    }
    List< int > * first_list = new List <int>{d[first][0]};
    try
    {
      List< int > * first_list_tail = first_list;
      for (size_t i = 1; i < n[first]; ++i)
      {
        first_list_tail->next = new List< int >{d[first][i], nullptr};
        first_list_tail = first_list_tail->next;
      }
      head = new List< List< int > * >{first_list, nullptr};
    }
    catch (const std::bad_alloc&)
    {
      deleteList(first_list);
      throw;
    }
    List< List< int > * > * tail = head;
    for (size_t i = first + 1; i < m; ++i)
    {
      if (n[i] == 0)
      {
        continue;
      }
      List< int > * innhead = nullptr;
      try
      {
        innhead = new List< int >{d[i][0], nullptr};
        List< int > * inntail = innhead;
        for (size_t j = 1; j < n[i]; j++)
        {
          inntail->next = new List< int >{d[i][j],nullptr};
          inntail = inntail->next;
        }
        tail->next = new List< List< int > * >{innhead, nullptr};
        tail = tail->next;
      }
      catch (const std::bad_alloc&)
      {
        deleteListOfLists(head);
        throw;
      }
    }
    return head; 
  }

  template< class T, class C >
  size_t count(const List< List< T > * > * head, C condition)
  {
    size_t counter = 0;
    for (const List< List< T > * > * i = head; i != nullptr; i = i->next)
    {
      for (List< T > * j = i->data; j != nullptr; j = j->next)
      {
        if (condition(j->data))
        {
          counter++;
        }
      }
    }
    return counter;
  }

  bool isOdd(int n)
  {
    return n % 2 != 0;
  }

  bool isEven(int n)
  {
    return n % 2 == 0;
  }
}

int main()
{
  int arrays_size = 0;
  std::cin >> arrays_size;
  if (arrays_size <= 0)
  {
    std::cerr << "No arrays\n";
    return 1;
  }
  int** arrays = new int*[arrays_size];
  size_t* sizes = new size_t[arrays_size];
  size_t created = 0;
  for (;created < size_t(arrays_size);)
  {
    std::cin >> sizes[created];
    try
    {
      arrays[created] = new int[sizes[created]];
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "Not enough memory\n";
      delete[] sizes;
      deleteMtx(arrays, created);
      return 1;
    }
    created++;
    for (size_t j = 0; j < sizes[created - 1]; ++j)
    {
      std:: cin >> arrays[created - 1][j];
    }
    
  }
  if (!std::cin)
  {
    delete[] sizes;
    deleteMtx(arrays, created);
    std::cerr << "Input error\n";
    return 1;
  }
  List< List< int > * > * head = nullptr;
  try
  {
    head = convert(arrays, arrays_size, sizes);
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Not enough memory\n";
    delete[] sizes;
    deleteMtx(arrays, created);
    return 1;
  }
  std::string s = "";
  std::cin >> s;
  std::cout << "\n";
  if (s == "Odd")
  {
    std::cout << count(head, isOdd) << "\n";
  }
  else if (s == "Even")
  {
    std::cout << count(head, isEven) << "\n";
  }
  else
  {
    std::cout << count(head, isOdd) << "\n";
    std::cout << count(head, isEven) << "\n";
  }
  deleteMtx(arrays, created);
  delete[] sizes;
  return 0;
}
