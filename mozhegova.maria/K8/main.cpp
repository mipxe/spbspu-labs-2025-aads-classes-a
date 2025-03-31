#include <iostream>
#include <functional>

template< class T, class Cmp >
struct BiTree {
  T data;
  Cmp cmp;
  BiTree< T, Cmp > * left, * right, * parent;
};

template< class T, class Cmp >
BiTree< T, Cmp > * extract(BiTree< T, Cmp > * root, const T & value, BiTree< T, Cmp > ** result);

template< class T, class Cmp >
void clear(BiTree< T, Cmp > * root)
{
  if (root)
  {
    clear(root->left);
    clear(root->right);
    delete root;
  }
}

template< class T, class Cmp >
BiTree< T, Cmp > * createBiTree(const T * nums, size_t n, Cmp cmp)
{
  if (n == 0)
  {
    return nullptr;
  }
  BiTree< T, Cmp > * root = new BiTree< T, Cmp >{nums[0], nullptr, nullptr, nullptr};
  for (size_t i = 1; i < n; i++)
  {
    BiTree< T, Cmp > * current = root;
    BiTree< T, Cmp > * parent = nullptr;
    while (current)
    {
      parent = current;
      if (cmp(nums[i], current->data))
      {
        current = current->left;
      }
      else
      {
        current = current->right;
      }
    }
    BiTree< T, Cmp > * newTree = nullptr;
    try
    {
      newTree = new BiTree< T, Cmp >{nums[i], nullptr, nullptr, parent};
    }
    catch (const std::bad_alloc &)
    {
      clear(root);
      throw;
    }
    if (cmp(nums[i], parent->data))
    {
      parent->left = newTree;
    }
    else
    {
      parent->right = newTree;
    }
  }
  return root;
}

int main()
{
  size_t n = 0;
  if (!(std::cin >> n))
  {
    std::cerr << "invalid input\n";
    return 1;
  }
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

  BiTree< int, std::less< int > > * root = nullptr;
  try
  {
    root = createBiTree(nums, n, std::less< int >());
  }
  catch (const std::bad_alloc &)
  {
    delete[] nums;
    std::cerr << "Out of memory\n";
    return 1;
  }
  delete[] nums;
}
