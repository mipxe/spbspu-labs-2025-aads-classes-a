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

BiList* transform(int * l, const size_t n)
{
  if (n == 0)
  {
    return nullptr;
  }

  BiList* head = new BiList{ l[0], nullptr, nullptr };
  BiList* tail = head;

  for (size_t i = 1; i < n; i++)
  {
    BiList* temp = tail;
    try
    {
      tail = new BiList{ l[i], temp, nullptr };
    }
    catch (std::bad_alloc& e)
    {
      return tail;
    }
    temp->next = tail;
  }
  return head;
}

int main()
{
  int* l = new int[10];
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

  head = transform(l, n);
  if (head == nullptr)
  {
    delete[] l;
    rmList(head);
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
