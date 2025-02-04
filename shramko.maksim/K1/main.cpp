#include <iostream>

struct BiList
{
  int value;
  BiList * prev, * next;
};

int main()
{
  try
  {
    int* l = new int[10];
  }
  catch (const std::bad_alloc & e)
  {
    delete[] l;
    std::cerr << "Mem err!\n";
    return 1;
  }

  size_t n = 0;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      break;
    }

    size++;

    if (n == 10)
    {
      break;
    }

    std::cin >> l[n];
  }

  BiList* head = nullptr;

  try
  {
    head = transform(l, n);
  }
  catch (const std::bad_alloc & e)
  {
    delete[] l;
    std::cerr << "Mem trsfm err!\n";
    return 1;
  }

  BiList* tail = head;

  while (tail && tail->next)
  {
    tail = tail->next;
  }

  std::cout << tail->value;
  BiList* subTail = tail->prerv;
  for (size_t i = 0; i < n - 1; i++)
  {
    std::cout << " " << subTail->value;
    subTail = subTail->prev;
  }
  std::cout << "\n";

  rmList(head);
  delete[] l;
}
