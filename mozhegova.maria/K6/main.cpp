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
  if (!root || !root->left)
  {
    throw std::logic_error("<INVALID ROTATE>");
  }
  BiTree< int > * newRoot = root->left;
  BiTree< int > * temp = newRoot->right;
  root->left = temp;
  if (temp)
  {
    temp->parent = root;
  }
  newRoot->right = root;
  newRoot->parent = root->parent;
  root->parent = newRoot;
  if (newRoot->parent)
  {
    if (newRoot->parent->left == root)
    {
      newRoot->parent->left = newRoot;
    }
    else
    {
      newRoot->parent->right = newRoot;
    }
  }
  return newRoot;
}

template< class T >
BiTree< T > * rotate_left(BiTree< T > * root)
{
  if (!root || !root->right)
  {
    throw std::logic_error("<INVALID ROTATE>");
  }
  BiTree< int > * newRoot = root->right;
  BiTree< int > * temp = newRoot->left;
  root->right = temp;
  if (temp)
  {
    temp->parent = root;
  }
  newRoot->left = root;
  newRoot->parent = root->parent;
  root->parent = newRoot;
  if (newRoot->parent)
  {
    if (newRoot->parent->left == root)
    {
      newRoot->parent->left = newRoot;
    }
    else
    {
      newRoot->parent->right = newRoot;
    }
  }
  return newRoot;
}

template< class T, class Cmp >
BiTree< T > * find(BiTree< T > * root, const T & value, Cmp cmp)
{
  BiTree< int > * temp = root;
  while (temp && temp->data != value)
  {
    if (cmp(value, temp->data))
    {
      temp = temp->left;
    }
    else
    {
      temp = temp->right;
    }
  }
  return temp;
}

template< class T >
void clear(BiTree< T > * root)
{
  while (root)
  {
    clear(root->left);
    clear(root->right);
    delete root;
  }
}

template< class T >
BiTree< T > * createBiTree(const T * nums, size_t n)
{
  if (n == 0)
  {
    return nullptr;
  }
  BiTree< int > * root = new BiTree< int >{nums[0], nullptr, nullptr, nullptr};
  for (size_t i = 1; i < n; i++)
  {
    BiTree< int > * current = root;
    BiTree< int > * parent = nullptr;
    while (current)
    {
      parent = current;
      if (nums[i] < current->data)
      {
        current = current->left;
      }
      else
      {
        current = current->right;
      }
    }
    BiTree< int > * newTree = nullptr;
    try
    {
      newTree = new BiTree< int >{nums[i], nullptr, nullptr, parent};
    }
    catch (const std::bad_alloc &)
    {
      clear(root);
      throw;
    }
    if (nums[i] > parent->data)
    {
      parent->right = newTree;
    }
    else
    {
      parent->left = newTree;
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

  BiTree< int > * root = nullptr;
  try
  {
    root = createBiTree(nums, n);
  }
  catch (const std::bad_alloc &)
  {
    delete[] nums;
    std::cerr << "Out of memory\n";
    return 1;
  }
  delete[] nums;

  std::string direct;
  int num = 0;
  while (!std::cin.eof() && (std::cin >> direct >> num))
  {
    if ((direct != "left" && direct != "right") || std::cin.fail())
    {
      std::cout << "<INVALID COMMAND>\n";
      return 1;
    }
    BiTree< int > * findNode = find(root, num, std::less< int>());
    if (findNode == nullptr)
    {
      clear(root);
      std::cout << "<INVALID ROTATE>\n";
      continue;
    }
    BiTree< int > * temp = nullptr;
    try
    {
      if (direct == "left")
      {
        temp = rotate_left(findNode);
      }
      else
      {
        temp = rotate_right(findNode);
      }
    }
    catch (const std::logic_error & e)
    {
      clear(root);
      std::cout << e.what() << '\n';
    }
    if (findNode == root)
    {
      root = temp;
    }
    std::cout << temp->data << '\n';
  }
  clear(root);
}
