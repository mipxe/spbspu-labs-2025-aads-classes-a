#include <iostream>

struct BiList
{
  int value;
  BiList * prev, * next;
};


void rmList(BiList* tail)
{
  while (tail != nullptr)
  {
    BiList* temp = tail->prev;
    delete tail;
    tail = temp;
  }
}

BiList* transform(const int* l, size_t n)
{
  if (n == 0)
  {
    return nullptr;
  }

  BiList* head = nullptr;
  BiList* tail = nullptr;

  try
  {
    head = new BiList{ l[0], nullptr, nullptr };
    tail = head;

    for (size_t i = 1; i < n; i++)
    {
      BiList* temp = tail;
      tail = new BiList{ l[i], temp, nullptr };
      temp->next = tail;
    }
  }
  catch (const std::bad_alloc& e)
  {
    rmList(head);
    throw;
  }
  return tail;
}

int main()
{
  int* l = new int[10];
  size_t n = 0;
  std::cin >> l[0];

  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      break;
    }

    n++;

    if (n == 10)
    {
      break;
    }

    std::cin >> l[n];
  }

  BiList* tail = nullptr;

  if (n == 0)
  {
    std::cout << '\n';
    delete[] l;
    return 0;
  }

  try
  {
    tail = transform(l, n);
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "Mem trsfm err!\n";
    delete[] l;
    return 1;
  }

  std::cout << tail->value;
  BiList* subTail = tail->prev;

  for (size_t i = 0; i < n - 1; i++)
  {
    std::cout << " " << subTail->value;
    subTail = subTail->prev;
  }
  std::cout << "\n";

  rmList(tail);
  delete[] l;
  return 0;
}
