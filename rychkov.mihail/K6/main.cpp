#include <iostream>
#include <functional>
#include <string>

template< class T >
struct BiTree
{
  T data;
  BiTree< T >* left = nullptr;
  BiTree< T >* right = nullptr;
  BiTree< T >* parent = nullptr;
};
template< class T >
BiTree< T >* rotate_right(BiTree< T >* root)
{
  return root;
}
template< class T >
BiTree< T >* rotate_left(BiTree< T >* root)
{
  return root;
}
template< class T, class C >
BiTree< T >* find(BiTree< T >* root, const T& value, C compare)
{
  while (root != nullptr)
  {
    if (compare(value, root->data))
    {
      root = root->left;
    }
    else if (compare(root->data, value))
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
    else
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
  if (!(std::cin >> size))
  {
    std::cerr << "failed to read size\n";
    return 1;
  }
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
  std::string input;
  while (std::cin >> input >> number)
  {
    BiTree< int >* node = find(root, number, std::less<>());
    if (input == "left")
    {
      BiTree< int >* temp = rotate_left(node);
      if (temp == nullptr)
      {
        std::cerr << "<INVALID ROTATE>\n";
        destroy(root);
        return 1;
      }
      if (node == root)
      {
        root = temp;
      }
      std::cout << node->data << '\n';
    }
    else if (input == "right")
    {
      BiTree< int >* temp = rotate_right(node);
      if (temp == nullptr)
      {
        std::cerr << "<INVALID ROTATE>\n";
        destroy(root);
        return 1;
      }
      if (node == root)
      {
        root = temp;
      }
      std::cout << node->data << '\n';
    }
    else
    {
      std::cerr << "<INVALID COMMAND>\n";
      destroy(root);
      return 1;
    }
  }
  if (!std::cin.eof())
  {
    std::cerr << "<INVALID COMMAND>\n";
    destroy(root);
    return 1;
  }
  destroy(root);
}
