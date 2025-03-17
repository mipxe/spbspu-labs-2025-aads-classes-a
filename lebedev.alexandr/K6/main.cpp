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
