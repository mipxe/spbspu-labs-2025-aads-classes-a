#include "bi_list.hpp"

rychkov::BiList* rychkov::convert(const int* arr, size_t size)
{
  if (size == 0)
  {
    return nullptr;
  }

  BiList* tail = new BiList[size];
  for (size_t i = 0; i < size; i++)
  {
    tail[size - i - 1].value = arr[i];
  }
  for (size_t iHead = size - 1; iHead > 0; iHead--)
  {
    tail[iHead].next = tail + (iHead - 1);
  }
  for (size_t iTail = 0; iTail < size - 1; iTail++)
  {
    tail[iTail].prev = tail + (iTail + 1);
  }
  return tail;
}
void rychkov::destroy(BiList* tail)
{
  delete[] tail;
}
