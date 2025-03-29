#include <iostream>
#include <string>

template< class T >
struct BiTree
{
  T data;
  BiTree< T > * left, * right, * parent;
};

template< class T >
BiTree< T > * rotate_right(BiTree< T > * root)
{
  auto grandfather = root->parent->parent;
  auto father = root->parent;
  auto son = root->right;
  father->left = son;
  if (son)
  {
    son->parent = father;
    father = root;
    father->right = son->parent;
    son->parent->parent = root;
  }
  else
  {
    auto temp = father;
    father = root;
    father->right = temp;
    temp->parent = root;
  }
  root->parent = grandfather;
  return root->left;
}

template< class T >
BiTree< T > * rotate_left(BiTree< T > * root)
{
  auto grandfather = root->parent->parent;
  auto father = root->parent;
  auto son = root->left;
  father->right = son;
  if (son)
  {
    son->parent = father;
    father = root;
    father->left = son->parent;
    son->parent->parent = root;
  }
  else
  {
    auto temp = father;
    father = root;
    father->left = temp;
    temp->parent = root;
  }
  root->parent = grandfather;
  return root->right;
}

template< class T, class Cmp >
BiTree< T > * find(BiTree< T > * root, const T & value, Cmp cmp)
{
  while (root->data != value)
  {
    if (cmp(value, root->data) && root->left)
    {
      root = root->left;
    }
    else if (!cmp(value, root->data) && root->right)
    {
      root = root->right;
    }
    else
    {
      root = nullptr;
      break;
    }
  }
  return root;
}

template< class T, class Cmp >
BiTree< T > * convert(const T * array, size_t size, Cmp cmp)
{
  BiTree< T > * root = new BiTree< T >{ array[0], nullptr, nullptr, nullptr };
  for (size_t i = 1; i < size; i++)
  {
    auto temp = root;
    while (temp->left || temp->right)
    {
      if (cmp(array[i], temp->data) && temp->left)
      {
        temp = temp->left;
      }
      else if (!cmp(array[i], temp->data) && temp->right)
      {
        temp = temp->right;
      }
      else
      {
        break;
      }
    }
    if (cmp(array[i], temp->data))
    {
      temp->left = new BiTree< T >{ array[i], nullptr, nullptr, temp };
    }
    else
    {
      temp->right = new BiTree< T >{ array[i], nullptr, nullptr, temp };
    }
  }
  return root;
}

template< class T, class Cmp >
void clearBiTree(BiTree< T > * root, Cmp cmp)
{
  auto begin = root;
  while (begin->left)
  {
    begin = begin->left;
  }
  while (begin != root)
  {
    auto todelete = begin;
    begin = begin->parent;
    delete todelete;
    if (begin->right)
    {
      auto subbegin = begin->right;
      while (subbegin->left)
      {
      }
    }
  }
}

int main()
{
  size_t sequence_length = 0;
  if (!(std::cin >> sequence_length))
  {
    std::cerr << "ERROR: Invalid argument" << "\n";
    return 1;
  }
  else if (std::cin.eof())
  {
    std::cerr << "End of file" << "\n";
    return 2;
  }
  int * elements_array = new int[sequence_length];
  size_t i = 0;
  while(i != sequence_length && std::cin && !std::cin.eof())
  {
    std::cin >> elements_array[i++];
  }
  if (!std::cin)
  {
    delete[] elements_array;
    std::cerr << "ERROR: Invalid argument" << "\n";
    return 1;
  }
  else if (std::cin.eof())
  {
    delete[] elements_array;
    std::cerr << "End of file" << "\n";
    return 2;
  }
  BiTree< int > * root = convert(elements_array, sequence_length, std::less< int >());
  std::string type_of_command;
  int number = 0;
  while (!std::cin.eof())
  {
    std::cin >> type_of_command;
    if (!(std::cin >> number))
    {
      std::cerr << "<INVALID COMMAND>";
      std::cerr << "\n";
      return 3;
    }
    BiTree< int > * subroot = find(root, number, std::less< int >());
    if (type_of_command == "left" && subroot)
    {
      std::cout << rotate_left(subroot)->data;
      std::cout << "\n";
      while (root->parent)
      {
        root = root->parent;
      }
      std::cout << root->data;
    }
    else if (type_of_command == "right" && subroot)
    {
      BiTree< int > * subroot = find(root, number, std::less< int >());
      std::cout << rotate_right(subroot)->data;
      std::cout << "\n";
      while (root->parent)
      {
        root = root->parent;
      }
      std::cout << root->data;
    }
    else
    {
      std::cerr << "<INVALID ROTATE>";
      std::cerr << "\n";
      return 4;
    }
  }
  delete[] elements_array;
}
