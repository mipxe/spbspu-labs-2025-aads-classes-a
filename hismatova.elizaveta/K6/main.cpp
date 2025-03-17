#include <iostream>
template< class T >
struct BiTree
{
  T data;
  BiTree< T >* left;
  BiTree< T >* right;
  BiTree< T >* parent;
  BiTree(T value):
    data(value),
    left(nullptr),
    right(nullptr),
    parent(nullptr)
  {}
};
template< class T >
BiTree< T >* rotate_right(BiTree< T >* root)
{
  if (!root || !root->left)
  {
    return nullptr;
  }
  BiTree< T >* new_root = root->left;
  root->left = new_root->right;
  if (new_root->right)
  {
    new_root->right->parent = root;
  }
  new_root->parent = root->parent;
  new_root->right = root;
  root->parent = new_root;
  return new_root;
}
template< class T >
BiTree< T >* rotate_left(BiTree< T >* root)
{
  if (!root || !root->right)
  {
    return nullptr;
  }
  BiTree< T >* new_root = root->right;
  root->right = new_root->left;
  if (new_root->left)
  {
    new_root->left->parent = root;
  }
  new_root->parent = root->parent;
  new_root->left = root;
  root->parent = new_root;
  return new_root;
}
template< class T, class Cmp >
BiTree< T >* find(BiTree< T >* root, const T& value, Cmp cmp)
{
  while (root != nullptr)
  {
    if (cmp(value, root->data))
    {
      root = root->left;
    }
    else if (cmp(root->data, value))
    {
      root = root->right;
    }
    else
    {
      return root;
    }
  }
  return nullptr;
}
void insert(BiTree< int >*& root, int value)
{
  if (!root)
  {
    try
    {
      root = new BiTree<int>(value);
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "ERROR: out of memory\n";
      throw;
    }
    return;
  }
  if (value < root->data)
  {
    insert(root->left, value);
    if (root->left)
    {
      root->left->parent = root;
    }
  }
  else
  {
    insert(root->right, value);
    if (root->right) root->right->parent = root;
  }
}

int main()
{}
