#include <iostream>

template < class T >
struct List {
  T data;
  List< T > * next;
}

void rmArr(int** arr, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    delete[] arr;
  }
  delete[] arr;
}

void rmList(List< int > * head)
{
  while (head != nullptr)
  {
    List< int > * temp = head;
    head = head->next;
    delete temp;
  }
}

void rmList(List< List< int > * > * head)
{
  while (head != nullptr)
  {
    List< int > * temp = head->data;
    rmList(temp);
    List< List< int > * > * tempHead = head;
    head = head->next;
    delete tempHead;
  }
}

int main()
{
  size_t m = 0;

  std::cin >> m;
  if (std::cin.fail())
  {
    std::cerr << "Error: Main -> cin m.\n";
    return 1;
  }

  int** arr = nullptr;
  try
  {
    arr = new int*[m]
  }
  catch (const std::bad_alloc()&)
  {
    std::cerr << "Error: main -> arr bad_alloc\n";
    return 1;
  }

  size_t* size = nullptr;
  try
  {
    size = new size_t[m];
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Error: main -> size bad_alloc\n";
    rmArr(arr, m);
    return 1;
  }

  for (size_t i = 0; i < m; i++)
  {
    std::cin >> size[i];
    if (std::cin.fail())
    {
      std::cerr << "Error: Main -> cin size.\n";
      rmArr(arr, m);
      delete[] size;
      return 1;
    }

    try
    {
      arr[i] = new int[i];
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "Error: main -> arr bad_alloc\n";
      rmArr(arr, i);
      delete[] size;
      return 1;
    }

    for (size_t j = 0; j < size[i]; j++)
    {
      std::cin >> arr[i][j];
      if (std::cin.fail())
      {
        std::cerr << "Error: main -> cin arr[i][j].\n";
        rmArr(arr, i + 1);
        delete[] size;
        return 1;
      }
    }
  }

  List< List < int > * > * head = nullptr;
  try
  {
    head = convert(arr, m, size);
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "Error: main -> convert bad_alloc\n";
    rmArr(arr, m);
    delete[] size;
    return 1;
  }

  std::string word = "";
  std::cin >> word;
  if (word == "even")
  {
    std::cout << count(head, 1);
  }
  else if (word == "odd")
  {
    std::cout << count(head, 0);
  }
  else
  {
    std::cout << count(head, 0) << " " << count(head, 1);
  }
  std::cout << "\n";

  rmArr(arr, m);
  delete[] size;
  rmList(head);
}
