#include <iostream>

template< class T >
struct BiTree 
{
  T data;
  BiTree< T >* left;
  BiTree< T >* right;
  BiTree< T >* parent;
  BiTree< T >(int x):
    data(x),
    left(nullptr),
    right(nullptr),
    parent(nullptr)
  {}
};

template< class T >
BiTree< T >* convert(int nums[], size_t size)
{
  BiTree< T >* head = new BiTree< T >(nums[0]);
  BiTree< T >* current = head;
  for (size_t i = 1; i < size; ++i)
  {
    BiTree< T >* elem = nullptr;
    try
    {
      elem = new BiTree< T >(nums[i]);
    }
    catch(const std::bad_alloc&)
    {
      throw;
    }
    while(true)
    {
      if (nums[i] < current->data)
      {
        if (current->left)
        {
          current = current->left;
        }
        else
        {
          current->left = elem;
          elem->parent = current;
          break;
        }
      }
      else
      {
        if (current->right)
        {
          current = current->right;
        }
        else
        {
          current->right = elem;
          elem->parent = current;
          break;
        }
      }
    }
    current = head;
  }
  return head;
}

int main()
{
  size_t size = 0;
  std::cin >> size;
  int* nums = new int[size];
  size_t i = 0;
  while (!std::cin.eof() && i < size)
  {
    int a = 0;
    std::cin >> a;
    nums[i++] = a;
  }
  if (i < size)
  {
    std::cerr << "incomplete sequence!\n";
    return 1;
  }
}
