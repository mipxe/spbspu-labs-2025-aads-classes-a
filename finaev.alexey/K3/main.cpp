#include <iostream>
#include <string>

template< class T >
struct List {
  T data;
  List< T >* next;
};

template< class T >
void deleteList(List< T >* head)
{
  while (head != nullptr)
  {
    List< T >* temp = head;
    head = head->next;
    delete temp;
  }
}

template< class T >
void deleteList(List< List< T > *>* head)
{
  while (head != nullptr)
  {
    List< T >* temp = head->data;
    deleteList(temp);
    List< List< T >*>*  tempHead = head;
    head = head->next;
    delete tempHead;
  }
}

template< class T >
void deleteArr(T** arr, size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    delete[] arr[i];
  }
  delete[] arr;
}

List<int>* convert(const int* arr, size_t n)
{
  List<int>* head = new List<int>{ arr[0], nullptr };
  List<int>* tail = head;
  for (size_t i = 1; i < n; ++i)
  {
    List<int>* newEl = nullptr;
    try
    {
      newEl = new List<int>{ arr[i], nullptr };
    }
    catch (std::bad_alloc&)
    {
      deleteList(head);
    }
    tail->next = newEl;
    tail = newEl;
  }
  return head;
}

List< List< int >* >* convert(const int* const* d, size_t m, const size_t* n)
{
  if (m == 0)
  {
    return nullptr;
  }
  List< List< int >* >* head = new List< List< int > * > { convert(d[0], n[0]), nullptr };
  List< List< int >* >* tail = head;
  for (size_t i = 1; i < m; ++i)
  {
    List< List< int >* >* newEl = nullptr;
    try
    {
      newEl = new List< List< int > * > { convert(d[i], n[i]), nullptr };
    }
    catch (std::bad_alloc&)
    {
      deleteList(head);
    }
    tail->next = newEl;
    tail = newEl;
  }
  return head;
}

template< class T >
size_t countOdd(const List< List< T >* >* head)
{
  size_t resOdd = 0;
  const List<List<T>*>* tail = head;
  while (tail != nullptr)
  {
    List<T>* temp = tail->data;
    while (temp != nullptr)
    {
      if ((temp->data % 2) != 0)
      {
        resOdd += 1;
      }
      temp = temp->next;
    }
    tail = tail->next;
  }
  return resOdd;
}

template<class T>
size_t countEven(const List<List<T>*>* head)
{
  size_t resEven = 0;
  const List<List<T>*>* tail = head;
  while (tail != nullptr)
  {
    List<T>* temp = tail->data;
    while (temp != nullptr)
    {
      if ((temp->data % 2) == 0)
      {
        resEven += 1;
      }
      temp = temp->next;
    }
    tail = tail->next;
  }
  return resEven;
}

template< class T, class C >
size_t count(const List< List< T >* >* head, C condition)
{
  if (condition == 2)
  {
    return countEven(head);
  }
  else if (condition == 1)
  {
    return countOdd(head);
  }
  return 0;
}

int main()
{
  size_t capacity = 0;
  std::cin >> capacity;
  if (!std::cin.good())
  {
    std::cerr << "uncorrect input\n";
    return 1;
  }
  int** arr = nullptr;
  try
  {
    arr = new int* [capacity];
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "bad alloc!\n";
    return 1;
  }
  size_t* size = nullptr;
  try
  {
    size = new size_t[capacity];
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "bad alloc\n";
    deleteArr(arr, capacity);
    return 1;
  }
  for (size_t i = 0; i < capacity; ++i)
  {
    std::cin >> size[i];
    if (!std::cin.good())
    {
      deleteArr(arr, i);
      delete[] size;
      std::cerr << "uncorrect input\n";
      return 1;
    }
    try
    {
      arr[i] = new int[size[i]];
    }
    catch (const std::bad_alloc&)
    {
      deleteArr(arr, i);
      delete[] size;
      std::cerr << "bad_alloc\n";
      return 1;
    }
    for (size_t j = 0; j < size[i]; ++j)
    {
      int temp = 0;
      std::cin >> temp;
      if (!std::cin.good())
      {
        deleteArr(arr, i + 1);
        delete[] size;
        std::cerr << "uncorrect input\n";
        return 1;
      }
      arr[i][j] = temp;
    }
  }
  List< List< int >* >* head = nullptr;
  try
  {
    head = convert(arr, capacity, size);
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "uncorrect convert\n";
    deleteArr(arr, capacity);
    delete[] size;
    return 1;
  }
  std::string condition = "";
  std::cin >> condition;
  if (condition == "even")
  {
    std::cout << count(head, 2);
  }
  else if (condition == "odd")
  {
    std::cout << count(head, 1);
  }
  else
  {
    std::cout << count(head, 1) << " " << count(head, 2);
  }
  std::cout << "\n";
  deleteArr(arr, capacity);
  delete[] size;
  deleteList(head);
}
