#include <iostream>

template< class T >
struct List 
{
  T data;
  List< T > * next;
};

void allocateMemoryForMassive(int * ptr_massives, size_t number_of_elements);
void clearAllMassives(int ** ptr_massives, size_t * ptr_numbers_of_elements, size_t number_of_massives);
List< List< int > * > * convert(const int * const * d, size_t m, const size_t * n);

int main()
{
  int ** ptr_massives = nullptr;
  size_t number_of_massives = 0;
  if (!(std::cin >> number_of_massives))
  {
    std::cerr << "ERROR: Invalid argument" << "\n";
    return 1;
  }
  size_t * ptr_numbers_of_elements = nullptr;
  size_t number_of_elements = 0;
  size_t created = 0;
  try
  {
    ptr_massives = new int * [number_of_massives];
    ptr_numbers_of_elements = new size_t [number_of_massives];
    for (size_t i = 0; i < number_of_massives; i++)
    {
      if (!(std::cin >> number_of_elements) || std::cin.eof())
      {
        throw std::logic_error("ERROR: Invalid argument");
      }
      allocateMemoryForMassive(ptr_massives[i], number_of_elements);
      created++;
      ptr_numbers_of_elements[i] = number_of_elements;
    }
  }
  catch (const std::logic_error & e)
  {
    clearAllMassives(ptr_massives, ptr_numbers_of_elements, created);
    std::cerr << e.what() << "\n";
    return 2;
  }
  catch(const std::bad_alloc & e)
  {
    clearAllMassives(ptr_massives, ptr_numbers_of_elements, created);
    std::cerr << "ERROR: Out of memory" << "\n";
    return 3;
  }
  convert(ptr_massives, number_of_massives, ptr_numbers_of_elements);
}

void allocateMemoryForMassive(int * ptr_massive, size_t number_of_elements)
{
  ptr_massive = new int [number_of_elements];
  for (size_t i = 0; i < number_of_elements; i++)
  {
    std::cin >> ptr_massive[i];
  }
}

void clearAllMassives(int ** ptr_massives, size_t * ptr_numbers_of_elements, size_t created)
{
  for (size_t i = 0; i < created; i++)
  {
    delete[] ptr_massives[i];
  }
  delete[] ptr_massives;
  delete[] ptr_numbers_of_elements;
}