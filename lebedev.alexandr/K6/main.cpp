#include <iostream>

template< class T >
struct BiTree
{
  T data;
  BiTree< T > * left, * right, * parent;
};

void deleteTree(BiTree< int >* root)
{
  if (root == nullptr)
  {
    return;
  }

  deleteTree(root-> left);
  deleteTree(root->right);

  delete root;
}

BiTree< int >* insertNode(BiTree< int >* root, int value)
{
  if (!root)
  {
    return new BiTree< int >{ value, nullptr, nullptr, nullptr };
  }

  BiTree< int >* current = root;
  BiTree< int >* parent = nullptr;

  while (current)
  {
    parent = current;
    if (value < current->data)
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }

  current = new BiTree< int >{ value, nullptr, nullptr, parent };
  if (value < parent->data)
  {
    parent->left = current;
  }
  else
  {
    parent->right = current;
  }

  return root;
}
int main()
{
  size_t size = 0;
  std::cin >> size;
  BiTree< int >* root = nullptr;
  BiTree< int >* current = nullptr;

  try
  {
    int value = 0;
    std::cin >> value;
    root = new BiTree< int >{ value, nullptr, nullptr, nullptr };
    current = root;
    for (size_t i = 1; i < size; i++)
    {
      if (!std::cin >> value)
      {
        deleteTree(root);
        std::cerr << "Incorrect input!\n";
        return 1;
      }

    }
  }
  catch(...)
  {}
}
