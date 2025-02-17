#include <iostream>
#include <string>

template< class T >
struct List {
  T data;
  List< T > * next;
};

template< class T >
void deleteList(List< T >* head)
{
  while (head != nullptr)
  {
    List< T >* subHead = head->next;
    delete head;
    head = subHead;
  }
}

template< class T >
void deleteList(List< T >** arr, size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    deleteList(arr[i]);
  }
  delete[] arr;
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

List< List< int > * > * convert(const int * const * d, size_t m, const size_t * n)
{
  List<int>** arr = new List<int>*[m];
  for (size_t i = 0; i < m; ++i)
  {
    List< int >* head = nullptr;
    List< int >* tail = head;
    for (size_t j = 0; j < n[i]; ++j)
    {
      List< int >* new_element = nullptr;
      try
      {
        new_element = new List< int > { d[i][j], nullptr };
      }
      catch (const std::bad_alloc&)
      {
        deleteList(arr, i);
        throw;
      }
      if (head == nullptr) 
      {
        head = new_element; 
        tail = head; 
      } 
      else 
      {
        tail->next = new_element;
        tail = tail->next;
      }
    }
    arr[i] = head;
  }
  List<List< int >*>* head = nullptr;
  try
  {
    head = new List< List <int> *> {arr[0], nullptr};
  }
  catch(const std::bad_alloc&)
  {
    deleteList(arr, m);
  }
  List<List< int >*>* tail = head;
  for (size_t i = 1; i < m; ++i)
  {
    List<List< int >*>* new_element = nullptr;
    try
    {
      new_element = new List<List< int >*> { arr[i], nullptr };
    }
    catch (const std::bad_alloc&)
    {
      deleteList(arr, m);
      deleteList(head);
      throw;
    }
    tail->next = new_element;
    tail = tail->next;
  }
  delete[] arr;
  return head;
}

template< class T >
size_t countOdd(const List< List< T > * > * head)
{
  size_t resOdd = 0;
  if (head != nullptr)
  {
    List< T > * temp = head->data;
    while(temp != nullptr)
    {
      if ((temp->data % 2) != 0)
      {
        resOdd += 1;
      }
      temp = temp->next;
    }
  }
  List< List< T > * > * tail = head->next;
  while (tail != nullptr)
  {
    List< T > * tailTemp = tail->data;
    while(tailTemp != nullptr)
    {
      if ((tailTemp->data % 2) != 0)
      {
        resOdd += 1;
      }
      tailTemp = tailTemp->next;
    }
    tail = tail->next;
  }
  return resOdd;
}

template< class T >
size_t countEven(const List< List< T > * > * head)
{
  size_t resEven = 0;
  if (head != nullptr)
  {
    List< T > * temp = head->data;
    while(temp != nullptr)
    {
      if ((temp->data % 2) == 0)
      {
        resEven += 1;
      }
      temp = temp->next;
    }
  }
  List< List< T > * > * tail = head->next;
  while (tail != nullptr)
  {
    List< T > * tailTemp = tail->data;
    while(tailTemp != nullptr)
    {
      if ((tailTemp->data % 2) == 0)
      {
        resEven += 1;
      }
      tailTemp = tailTemp->next;
    }
    tail = tail->next;
  }
  return resEven;
}

template< class T, class C >
size_t count(const List< List< T > * > * head, C condition)
{
  if (condition == "even")
  {
    return countEven(head);
  }
  else if (condition == "odd")
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
  if (capacity == 0)
  {
    std::cerr << "empty\n";
    return 1;
  }
  int ** arr = nullptr;
  try
  {
    arr = new int*[capacity];
  }
  catch(const std::bad_alloc&)
  {
    std::cerr << "bad alloc!\n";
    return 1;
  }
  size_t* size = nullptr;
  try
  {
    size = new size_t[capacity];
  }
  catch(const std::bad_alloc&)
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
    catch(const std::bad_alloc&)
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
        deleteArr(arr, i);
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
  catch(const std::bad_alloc&)
  {
    std::cerr << "uncorrect convert\n";
    deleteArr(arr, capacity);
    delete[] size;
    return 1;
  }
  std::string condition = "";
  std::cin >> condition;
  if (condition == "even" or condition == "odd")
  {
    std::cout << count(head, condition);
  }
  else
  {
    std::cout << count(head, "odd") << " " << count(head, "even");
  }
  std::cout << "\n";
  deleteArr(arr, capacity);
  delete[] size;
  deleteList(head);
}
