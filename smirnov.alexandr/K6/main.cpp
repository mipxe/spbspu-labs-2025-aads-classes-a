#include <iostream>
#include <cstddef>
#include <stdexcept>

template< class T >
struct BiTree {
  T data;
  BiTree< T > * left, * right, * parent;
};

template< class T >
void clearBiTree(BiTree< T > * root)
{
  if (root != nullptr)
  {
    clearBiTree(root->left);
    clearBiTree(root->right);
    delete root;
  }
}

template< class T, class Compare = std::less< T > >
BiTree< T > * createBiTree(T * arr, size_t size, Compare cmp = Compare())
{
  BiTree< T > * root = nullptr;
  try
  {
    for (size_t i = 0; i < size; ++i)
    {
      BiTree< T > * new_node = new BiTree< T >;
      new_node->data = arr[i];
      new_node->left = nullptr;
      new_node->right = nullptr;
      new_node->parent = nullptr;
      if (root == nullptr)
      {
        root = new_node;
      }
      else
      {
        BiTree< T > * current = root;
        bool flag = true;
        while (flag)
        {
          if (cmp(arr[i], current->data))
          {
            if (current->left == nullptr)
            {
              current->left = new_node;
              new_node->parent = current;
              flag = false;
            }
            else
            {
              current = current->left;
            }
          }
          else
          {
            if (current->right == nullptr)
            {
              current->right = new_node;
              new_node->parent = current;
              flag = false;
            }
            else
            {
              current = current->right;
            }
          }
        }
      }
    }
  }
  catch (const std::bad_alloc & e)
  {
    clearBiTree(root);
    throw std::runtime_error("Memory allocation failed");
  }
  return root;
}

int main()
{
  size_t length = 0;
  if (!(std::cin >> length))
  {
    std::cerr << "Input error\n";
    return 1;
  }
  int * arr = nullptr;
  try
  {
    arr = new int[length];
  }
  catch (const std::bad_alloc & e)
  {
    std::cerr << "Out of memory\n";
    return 1;
  }
  for (size_t i = 0; i < length; ++i)
  {
    if (!(std::cin >> arr[i]))
    {
      delete[] arr;
      std::cerr << "Input error\n";
      return 1;
    }
  }
  BiTree< int > * root = nullptr;
  try
  {
    root = createBiTree(arr, length);
  }
  catch (const std::bad_alloc & e)
  {
    delete[] arr;
    std::cerr << "Out of memory\n";
    return 1;
  }
}
