.#include <iostream>

struct BiList
{
  int value;
  BiList * prev, * next;
};


void rmList(BiList * head)
{
  while (tail != nullptr)
  {
    BiList* temp = tail->prev;
    delete tail;
    tail = temp;
  }
}

BiList* transform(const int* const l, const size_t n)
{
  if (n == 0)
  {
    return nullptr;
  }

  BiList* head = nullptr;
  BiList* tail = nullptr;

  try
  {
    head = new BiList{ arr[0], nullptr, nullptr };
    tail = head;

    for (size_t i = 1; i < n; i++)
    {
      BiList* temp = tail;
      tail = new BiList{ l[i], temp, nullptr };
      temp->next = tail;
    }
  }
  catch (catch std::bad_alloc& e)
  {
    rmList(head);
    throw;
  }
  return tail;
}

int main()
{
  int* l = new int[10];
  }

  std::cin >> l[0];
  size_t n = 0;

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

  BiList* head = nullptr;
  try
  {
    tail = transform(l, n);
  }
  catch (const std::bad_alloc& e)
  {
    delete[] l;
    std::cerr << "Mem trsfm err!\n";
    return 1;
  }

  std::cout << tail->value;;
  BiList* subTail = tail->prev;

  for (size_t i = 0; i < n - 1; i++)
  {
    std::cout << " " << subTail->value;
    subTail = subTail->prev;
  }
  std::cout << "\n";

  rmList(tail);
  delete[] l;
}
