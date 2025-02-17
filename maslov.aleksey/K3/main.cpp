#include <iostream>
#include <cstddef>

int main()
{
  size_t numArray = 0;
  if (!(std::cin >> numArray))
  {
    std::cerr << "error input number of arrays\n";
    return 1;
  }
  int * array = nullptr;
  try
  {
    array = new int[numArray];
    for (size_t i = 0; i < numArray; ++i)
    {
      if (!(std::cin >> array[i]))
      {
        std::cerr << "error input\n";
      }
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
  }
}
