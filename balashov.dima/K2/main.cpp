#include <iostream>

struct FwdList {
  int value;
  FwdList* next;
};

void deleteList(FwdList* head)
{
    FwdList* temp = head;
    while (temp)
    {
      FwdList* nextHead = temp->next;
      delete temp;
      temp = nextHead;
    }
}

FwdList* duplicate(FwdList * head, size_t numberElement, size_t numberDuplicates)
{
  if (numberElement < 1)
  {
    throw;
  }
  FwdList* nowHead = head;
  for (size_t i = 1; i < numberElement && nowHead != nullptr; i++)
  {
    nowHead = nowHead->next;
  }
  if (nowHead == nullptr)
  {
    throw;
  }
  for (size_t i = 0; i < numberDuplicates; i++)
  {
    FwdList* endHead = new FwdList{ nowHead->value, nullptr };
    endHead->next = nowHead->next;
    nowHead->next = endHead;
  }
  return nowHead;
}

int main()
{

  int maxCount = 10;

  FwdList *list = new FwdList{ 0, nullptr };
  FwdList* headNow = list;

  for (int i = 0; i < maxCount; i++)
  {
    FwdList* new_list = new FwdList{ i, nullptr };
    headNow->next = new_list;
    headNow = new_list;
  }

  int input;
  int realCount = 0;
  for (size_t i = 0; i < maxCount; i++)
  {
    std::cin >> input;
    if (std::cin.fail() && !std::cin.eof())
    {
      break;
    }
    realCount++;
  }
}
