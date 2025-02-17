#include <iostream>

template< class T >
struct List {
  T data;
  List< T > * next;
};

void deleteList(List< List< int > * > * head)
{
  List< List< int > * > * listOfLists = head;
  while (listOfLists)
  {
    List< int > * currentList = listOfLists->data;
    while (currentList)
    {
      List< int > * tempNode = currentList;
      currentList = currentList->next;
      delete tempNode;
    }
    List< List< int > * > * tempList = listOfLists;
    listOfLists = listOfLists->next;
    delete tempList;
  }
}

List< List< int > * > * convert(const int * const * d, size_t m, const size_t * n)
{
  List< List< int > * > * head = new List< List< int > * > ();
  List< List< int > * > * tail = head;
  try
  {
    for (size_t i = 0; i < m; i++)
    {
      List< int > * subhead = new List< int > {d[i][0], nullptr};
      List< int > * current = subhead;
      for (size_t j = 1; j < n[i]; j++)
      {
        List< int > * newNode = new List< int > {d[i][j], nullptr};
        current->next = newNode;
        current = newNode;
      }
      tail->data = subhead;
      tail->next = nullptr;
      tail = tail->next;
    }
  }
  catch(...)
  {
    deleteList(head);
    throw;
  }
  return head;
}

template< class T, class C >
size_t count(const List< List< T > * > * head, C condition);

void deleteArr(int ** arr, size_t count)
{
  for (size_t i = 0; i < count; i++)
  {
    delete[] arr[i];
  }
  delete[] arr;
}

int main()
{
  size_t M = 0;
  std::cin >> M;
  int ** arr = nullptr;
  size_t i = 0;
  size_t * n = nullptr;
  try
  {
    arr = new int * [M];
    n = new size_t[M];
    for (; i < M; i++)
    {
      size_t N = 0;
      std::cin >> N;
      arr[i] = new int[N];
      n[i] = N;
      for (size_t j = 0; j < N; j++)
      {
        std::cin >> arr[i][j];
      }
    }
  }
  catch(...)
  {
    delete[] n;
    deleteArr(arr, i);
    std::cerr << "Out of memory\n";
    return 1;
  }


}
