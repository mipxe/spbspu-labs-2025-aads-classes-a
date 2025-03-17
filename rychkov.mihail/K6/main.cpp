#include <iostream>
#include <functional>

template< class T >
struct BiTree
{
  T data;
  BiTree< T >* left = nullptr;
  BiTree< T >* right = nullptr;
  BiTree< T >* parent = nullptr;
};
template< class T >
BiTree< T >* rotate_right(BiTree< T >* root);
template< class T >
BiTree< T >* rotate_left(BiTree< T >* root);
template< class T, class C >
BiTree< T >* find(BiTree< T >* root, const T& value, C compare);
template< class T, class C >
BiTree< T >* insert(BiTree< T >* root, const T& value, C compare)
{
  BiTree< T >* result = root;
  if (root == nullptr)
  {
    return new BiTree< T >{value};
  }
  while (true)
  {
    if (compare(value, root->data))
    {
      if (root->left == nullptr)
      {
        root->left = new BiTree< T >{value, nullptr, nullptr, root};
        break;
      }
      else
      {
        root = root->left;
      }
    }
    else if (compare(root->data, value))
    {
      if (root->right == nullptr)
      {
        root->right = new BiTree< T >{value, nullptr, nullptr, root};
        break;
      }
      else
      {
        root = root->right;
      }
    }
  }
  return result;
}
template< class T >
void destroy(BiTree< T >* root)
{
  if (root == nullptr)
  {
    return;
  }
  destroy(root->left);
  destroy(root->right);
  delete root;
}

int main()
{
  size_t size = 0;
  std::cin >> size;
  BiTree< int >* root = nullptr;
  int number = 0;
  for (; (size != 0) && (std::cin >> number); size--)
  {
    try
    {
      root = insert(root, number, std::less<>());
    }
    catch (...)
    {
      std::cerr << "failed to construct tree\n";
      destroy(root);
      return 2;
    }
  }
  if (size != 0)
  {
    std::cerr << "failed to read tree\n";
    destroy(root);
    return 1;
  }
  destroy(root);
}
