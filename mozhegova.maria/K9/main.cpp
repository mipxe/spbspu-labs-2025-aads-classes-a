#include <iostream>
#include <string>
#include <limits>

template< class T, class Cmp >
struct TriTree {
  std::pair< T, T > data;
  TriTree< T, Cmp > * left, * middle, * right, * parent;
};

template< class T, class Cmp >
struct TriTreeIterator {
public:
  using this_t = TriTreeIterator< T, Cmp >;
  TriTreeIterator(TriTree< T, Cmp > * node);

  bool hasNext() const;
  bool hasPrev() const;

  this_t prev() const;
  this_t next() const;

  std::pair< T, T > & data();
private:
  TriTree< T, Cmp > * root;
};

template< class T, class Cmp >
TriTreeIterator< T, Cmp >::TriTreeIterator(TriTree< T, Cmp > * node):
  root(node)
{}

template< class T, class Cmp >
std::pair< T, T > & TriTreeIterator< T, Cmp >::data()
{
  return root->data;
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > TriTreeIterator< T, Cmp >::prev() const
{
  TriTree< T, Cmp > * temp = root;
  if (temp->left)
  {
    temp = temp->left;
    while (temp->right)
    {
      temp = temp->right;
    }
    return TriTreeIterator< T, Cmp >{temp};
  }
  else if (temp->middle)
  {
    temp = temp->middle;
    while (temp->right)
    {
      temp = temp->right;
    }
    return TriTreeIterator< T, Cmp >{temp};
  }
  else
  {
    while (temp->parent && temp == temp->parent->left)
    {
      temp = temp->parent;
    }
    if (temp->parent && temp == temp->parent->right)
    {
      if (temp->parent->middle)
      {
        temp = temp->parent->middle;
        while (temp->right)
        {
          temp = temp->right;
        }
        return TriTreeIterator< T, Cmp >{temp};
      }
      return TriTreeIterator< T, Cmp >{temp->parent}.prev();
    }
    return TriTreeIterator< T, Cmp >{temp->parent};
  }
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > TriTreeIterator< T, Cmp >::next() const
{
  TriTree< T, Cmp > * temp = root;
  if (temp->middle)
  {
    temp = temp->middle;
    while (temp->left)
    {
      temp = temp->left;
    }
    return TriTreeIterator< T, Cmp >{temp};
  }
  if (temp->right)
  {
    temp = temp->right;
    while (temp->left)
    {
      temp = temp->left;
    }
    return TriTreeIterator< T, Cmp >{temp};
  }
  else
  {
    while (temp->parent && temp == temp->parent->right)
    {
      temp = temp->parent;
    }
    if (temp->parent && temp == temp->parent->middle)
    {
      if (temp->parent->right)
      {
        temp = temp->parent->right;
        while (temp->left)
        {
          temp = temp->left;
        }
        return TriTreeIterator< T, Cmp >{temp};
      }
      return TriTreeIterator< T, Cmp >{temp->parent}.next();
    }
    return TriTreeIterator< T, Cmp >{temp->parent};
  }
}

template< class T, class Cmp >
bool TriTreeIterator< T, Cmp >::hasNext() const
{
  return root;
}

template< class T, class Cmp >
bool TriTreeIterator< T, Cmp >::hasPrev() const
{
  return root;
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > begin(TriTree< T, Cmp > * root)
{
  TriTree< T, Cmp > * temp = root;
  while (temp->left)
  {
    temp = temp->left;
  }
  return TriTreeIterator< T, Cmp >{temp};
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp > * root)
{
  TriTree< T, Cmp > * temp = root;
  while (temp->right)
  {
    temp = temp->right;
  }
  return TriTreeIterator< T, Cmp >{temp};
}

template< class T, class Cmp >
void clearTree(TriTree< T, Cmp > * root)
{
  if (root)
  {
    clearTree(root->left);
    clearTree(root->middle);
    clearTree(root->right);
    delete root;
  }
}

template< class T, class Cmp >
TriTree< T, Cmp > * insertTree(TriTree< T, Cmp > * root, std::pair< T, T > pair)
{
  TriTree< T, Cmp > * current = root;
  TriTree< T, Cmp > * parent = nullptr;
  while (current)
  {
    parent = current;
    if (Cmp()(pair.second, current->data.first))
    {
      current = current->left;
    }
    else if (Cmp()(current->data.first, pair.first) && Cmp()(pair.second, current->data.second))
    {
      current = current->middle;
    }
    else if (Cmp()(current->data.second, pair.first))
    {
      current = current->right;
    }
    else
    {
      return nullptr;
    }
  }
  TriTree< T, Cmp > * newTree = nullptr;
  try
  {
    newTree = new TriTree< T, Cmp >{pair, nullptr, nullptr, nullptr, parent};
  }
  catch (const std::bad_alloc &)
  {
    clearTree(root);
    throw;
  }
  if (Cmp()(pair.second, parent->data.first))
  {
    parent->left = newTree;
  }
  else if (Cmp()(parent->data.second, pair.first))
  {
    parent->right = newTree;
  }
  else
  {
    parent->middle = newTree;
  }
  return newTree;
}

template< class T, class Cmp >
size_t countInters(TriTree< T, Cmp > * root, const T & v1, const T & v2)
{
  if (!root) return 0;
  size_t count = 0;
  for (auto it = begin(root); it.hasNext(); it = it.next())
  {
    if (it.data().first <= v2 && it.data().second >= v1)
    {
      count++;
    }
  }
  return count;
}

template< class T, class Cmp >
size_t countCovers(TriTree< T, Cmp > * root, const T & v1, const T & v2)
{
  if (!root) return 0;
  size_t count = 0;
  for (auto it = begin(root); it.hasNext(); it = it.next())
  {
    if (it.data().first >= v1 && it.data().second <= v2)
    {
      count++;
    }
  }
  return count;
}

template< class T, class Cmp >
size_t countAvoids(TriTree< T, Cmp > * root, const T & v1, const T & v2)
{
  if (!root) return 0;
  size_t count = 0;
  for (auto it = begin(root); it.hasNext(); it = it.next())
  {
    if (it.data().first > v2 || it.data().second < v1)
    {
      count++;
    }
  }
  return count;
}

int main()
{
  size_t n = 0;
  if (!(std::cin >> n))
  {
    std::cerr << "invalid input\n";
    return 1;
  }
  int first, second = 0;
  TriTree< int, std::less< int > > * tree = nullptr;
  for (size_t i = 0; i < n; i++)
  {
    if (!(std::cin >> first >> second))
    {
      clearTree(tree);
      std::cerr << "invalid input\n";
      return 1;
    }
    if (!std::less< int >()(first, second)) std::swap(first, second);
    try
    {
      insertTree(tree, std::make_pair(first, second));
    }
    catch (const std::bad_alloc & e)
    {
      std::cerr << "out of memory\n";
      return 1;
    } 
  }

  std::string command = "";
  while (!(std::cin >> command).eof())
  {
    if (command != "intersects" && command != "covers" && command != "avoids")
    {
      std::cerr << "invalid command!!!\n";
      clearTree(tree);
      return 1;
    }
    int v1, v2 = 0;
    if (!(std::cin >> v1 >> v2) || (v1 >= v2))
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      std::cout << "<INVALID COMMAND>\n";
      continue;
    }
    if (command == "intersects")
    {
      std::cout << countInters(tree, v1, v2) << "\n";
    }
    else if (command == "covers")
    {
      std::cout << countCovers(tree, v1, v2) << "\n";
    }
    else if (command == "avoids")
    {
      std::cout << countAvoids(tree, v1, v2) << "\n";
    }
  }
  clearTree(tree);
}
