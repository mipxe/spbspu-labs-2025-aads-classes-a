#include <iostream>

void deleteArray(int** t, size_t created)
{
  for (size_t i = 0; i < created; i++)
  {
    delete[] t[i];
  }
  delete[] t;
}

int main()
{
  int** ptr = nullptr;
  size_t* sizes = nullptr;
  size_t m = 0, n = 0, created = 0;
  if (!(std::cin >> m))
  {
    std::cerr << "Incorrect input!\n";
    return 1;
  }

  try
  {
    ptr = new int*[m];
    sizes = new size_t[m];
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "Memory allocation error!\n";
    deleteArray(ptr, created);
    delete[] sizes;
    return 2;
  }

  while (created < m && std::cin >> n)
  {
    try
    {
      ptr[created] = new int[n];
      sizes[created] = n;
    }
    catch (const std::bad_alloc& e)
    {
      deleteArray(ptr, created);
      delete[] sizes;
      std::cerr << "Memory allocation error!\n";
      return 2;
    }

    for (size_t i = 0; i < n; i++)
    {
      if (!(std::cin >> ptr[created][i]))
      {
        std::cerr << "Incorrect input!\n";
        deleteArray(ptr, created);
        delete[] sizes;
        return 1;
      }
    }
    created++;
  }

  if (created == 0)
  {
    std::cerr << "Incorrect input!\n";
    deleteArray(ptr, created);
    delete[] sizes;
    return 1;
  }

  for (size_t i = 0; i < m; i++)
  {
    std::cout << sizes[i] << ' ';
  }
  std::cout << '\n';

  for (size_t i = 0; i < m; i++)
  {
    for (size_t j = 0; j < sizes[i]; j++)
    {
      std::cout << ptr[i][j] << ' ';
    }
    std::cout << '\n';
  }
  deleteArray(ptr, m);
  delete[] sizes;
  return 0;
}
