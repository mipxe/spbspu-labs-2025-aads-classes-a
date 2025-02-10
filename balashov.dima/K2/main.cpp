#include <iostream>

struct FwdList {
  int value;
  FwdList* next;
};

FwdList* Duplicate(FwdList * list, size_t numberElement, size_t numberDuplicates)
{

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
  }
}
