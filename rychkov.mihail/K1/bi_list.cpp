#include "bi_list.hpp"

rychkov::BiList* rychkov::convert(int* arr, size_t size)
{
  BiList* tail = new BiList[size];
  for (size_t i = 0; i < size; i++)
  {
    tail[size - i - 1].value = arr[i];
  }
  for (size_t i = 1; i < size; i++)
  {
    tail[i].next = tail + (i - 1);
    tail[i + 1].prev = tail + i;
  }
  return tail;
}
void rychkov::destroy(BiList* tail)
{
  delete[] tail;
}
