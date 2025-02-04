#include <iostream>

struct BiList
{
  int value;
  BiList * prev, * next;
};


void rmList(BiList * head)
{
  while (head == nullptr)
  {
    BiList* subHead = head->next;
    delete head;
    head = subHead;
  }
}

BiList* transform(const int* const l, const size_t n)
{
  if (n == 0)
  {
    return nullptr;
  }

  BiList* head = new BiList{ l[0], nullptr, nullptr };
  BiList* tail = head;

  for (size_t i = 1; i < n; i++)
  {
    BiList* temp = nullptr;
    try
    {
      tail = new BiList{ l[i], temp, nullptr };
    }
    catch (std::bad_alloc& e)
    {
      rmList(head);
      throw;
    }
    temp->next = tail;
  }
  return head;
}

int main()
{
  int* l = nullptr;
  try
  {
    l = new int[10];
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "Main mem err!\n";
    return 1;
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
    head = transform(l, n);
  }
  catch (const std::bad_alloc& e)
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
  BiList* subTail = tail->prev;
  for (size_t i = 0; i < n - 1; i++)
  {
    std::cout << " " << subTail->value;
    subTail = subTail->prev;
  }
  std::cout << "\n";

  rmList(head);
  delete[] l;
}
