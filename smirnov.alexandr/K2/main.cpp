struct FwdList
{
  int value;
  FwdList * next;
};

void deleteList(FwdList * list)
{
  while (list != nullptr)
  {
    FwdList * next = list->next;
    delete list;
    list = next;
  }
}

FwdList* createList()
{
  FwdList * head = new FwdList{0, nullptr};
  FwdList* current = head;
  for (size_t i = 1; i < 10; ++i)
  {
    FwdList * newNode = nullptr;
    try
    {
      newNode = new FwdList{i, nullptr};
    }
    catch (const std::bad_alloc & e)
    {
      deleteFwdList(head);
      throw;
    }
    current->next = newNode;
    current = current->next;
  }
  return head;
}

int main()
{
  FwdList * list = nullptr;
  try
  {
    list = createList();
  }
  catch (const std::bad_alloc & e)
  {
    std::cerr << "Out of memory\n";
    return 1;
  }
}
