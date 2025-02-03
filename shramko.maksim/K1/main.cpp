#include <iostream>

struct BiList
{
  int value;
  BiList * prev, * next;
};

int main()
{
  int* l = nullptr;
  try
  {
    l = new int[10];
  }
  catch (const std::bad_alloc & e)
  {
    delete[] l;
    std::cerr << "Mem err!\n";
    return 1;
  }

  int n = 0;
  for (size_t i = 0; i < 10; i++)
  {
    std::cin >> n;
  }

  for (size_t j = 0; j < 10; j++)
  {
    std::cout << l[j];
  }
}
