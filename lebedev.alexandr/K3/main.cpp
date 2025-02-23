#include <iostream>

template< class T >
struct List
{
  T data;
  List< T > * next;
};

void deleteList(List< List< int >* >* head)
{
  List< List< int >* >* listOfLists = head;
  while (listOfLists)
  {
    List< int >* currentList = listOfLists->data;
    while (currentList)
    {
      List< int >* tempNode = currentList->next;
      delete currentList;
      currentList = tempNode;
    }
    List< List< int >* >* tempNode = head->next;
    delete head;
    head = tempNode;
  }
}

List< List< int >* >* convert(const int* const* d, size_t m, const size_t* n)
{
  if (m == 0)
  {
    return nullptr;
  }
  List< List< int >* >* head = new List< List< int >* >();
  List< List< int >* >* tail = head;
}

void deleteArray(int** t, size_t created)
{
  for (size_t i = 0; i < created; i++)
  {
    delete[] t[i];
  }
  delete[] t;
}

int main()
{
  int** ptr = nullptr;
  size_t* sizes = nullptr;
  size_t m = 0, n = 0, created = 0;
  if (!(std::cin >> m))
  {
    std::cerr << "Incorrect input!\n";
    return 1;
  }

  try
  {
    ptr = new int*[m];
    sizes = new size_t[m];
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "Memory allocation error!\n";
    deleteArray(ptr, created);
    delete[] sizes;
    return 2;
  }

  while (created < m)
  {
    if (!(std::cin >> n))
    {
      std::cerr << "Incorrect input!\n";
      deleteArray(ptr, created);
      delete[] sizes;
      return 1;
    }
    try
    {
      ptr[created] = new int[n];
      sizes[created] = n;
    }
    catch (const std::bad_alloc& e)
    {
      deleteArray(ptr, created);
      delete[] sizes;
      std::cerr << "Memory allocation error!\n";
      return 2;
    }

    for (size_t i = 0; i < n; i++)
    {
      if (!(std::cin >> ptr[created][i]))
      {
        std::cerr << "Incorrect input!\n";
        deleteArray(ptr, created);
        delete[] sizes;
        return 1;
      }
    }
    created++;
  }

  deleteArray(ptr, m);
  delete[] sizes;
  return 0;
}
