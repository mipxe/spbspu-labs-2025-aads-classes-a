#include <iostream>

template< class T >
struct BiTree {
  T data;
  BiTree< T > * left, * right, * parent;
};

template< class T >
BiTree< T > * rotate_right(BiTree< T > * root);

template< class T >
BiTree< T > * rotate_left(BiTree< T > * root);

template< class T, class Cmp >
BiTree< T > * find(BiTree< T > * root, const T & value, Cmp cmp);

template< class T >
void clear(BiTree< T > * root);

int main()
{
  size_t n = 0;
  std::cin >> n;
  int * nums = nullptr;
  try
  {
    nums = new int[n];
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "out of memory\n";
    return 1;
  }
  for (size_t i = 0; i < n; i++)
  {
    if (!(std::cin >> nums[i]))
    {
      delete[] nums;
      std::cerr << "invalid input\n";
      return 1;
    }
  }

  BiTree< int > * root = nullptr;
  try
  {
    root = new BiTree< int >{nums[0], nullptr, nullptr, nullptr};
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "out of memory\n";
    return 1;
  }
  for (size_t i = 1; i < n; i++)
  {
    BiTree< int > * temp = root;
    while (temp->left && temp->right)
    {
      if (nums[i] > temp->data)
      {
        temp = temp->right;
      }
      else
      {
        temp = temp->left;
      }
    }
    while (temp->right && nums[i] > temp->data)
    {
      temp = temp->right;
    }
    while (temp->left && nums[i] < temp->data)
    {
      temp = temp->left;
    }
    BiTree< int > * newTree = nullptr;
    try
    {
      newTree = new BiTree< int >{nums[i], nullptr, nullptr, temp};
    }
    catch (const std::bad_alloc &)
    {
      delete[] nums;
      clear(root);
      std::cerr << "out of memory\n";
      return 1;
    }
    if (nums[i] > temp->data)
    {
      temp->right = newTree;
    }
    else
    {
      temp->left = newTree;
    }
  }
}
