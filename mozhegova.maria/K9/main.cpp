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
  TriTreeIterator(TriTree< T, Cmp > * node, bool isValid);

  bool hasNext() const;
  bool hasPrev() const;

  this_t prev() const;
  this_t next() const;

  std::pair< T, T > & data();
private:
  TriTree< T, Cmp > * root;
  bool isFirst;
};

template< class T, class Cmp >
TriTreeIterator< T, Cmp >::TriTreeIterator(TriTree< T, Cmp > * node, bool isValid):
  root(node),
  isFirst(isValid)
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
  if (isFirst)
  {
    if (temp->left)
    {
      temp = temp->left;
      while (temp->right)
      {
        temp = temp->right;
      }
      return TriTreeIterator< T, Cmp >{temp, false};
    }
    else
    {
      while (temp->parent && temp == temp->parent->left)
      {
        temp = temp->parent;
      }
      if (temp->parent && temp == temp->parent->right)
      {
        return TriTreeIterator< T, Cmp >{temp->parent, false};
      }
      return TriTreeIterator< T, Cmp >{temp->parent, true};
    }
  }
  else
  {
    if (temp->middle)
    {
      temp = temp->middle;
      while (temp->right)
      {
        temp = temp->right;
      }
      return TriTreeIterator< T, Cmp >{temp, false};
    }
    else
    {
      return TriTreeIterator< T, Cmp >{temp, true};
    }
  }
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > TriTreeIterator< T, Cmp >::next() const
{
  TriTree< T, Cmp > * temp = root;
  if (isFirst)
  {
    if (temp->middle)
    {
      temp = temp->middle;
      while (temp->left)
      {
        temp = temp->left;
      }
      return TriTreeIterator< T, Cmp >{temp, true};
    }
    else
    {
      return TriTreeIterator< T, Cmp >{temp, false};
    }
  }
  else
  {
    if (temp->right)
    {
      temp = temp->right;
      while (temp->left)
      {
        temp = temp->left;
      }
      return TriTreeIterator< T, Cmp >{temp, true};
    }
    else
    {
      while (temp->parent && temp == temp->parent->right)
      {
        temp = temp->parent;
      }
      if (temp->parent && temp == temp->parent->left)
      {
        return TriTreeIterator< T, Cmp >{temp->parent, true};
      }
      return TriTreeIterator< T, Cmp >{temp->parent, false};
    }
  }
}

template< class T, class Cmp >
bool TriTreeIterator< T, Cmp >::hasNext() const
{
  if (next().root)
  {
    return true;
  }
  return false;
}

template< class T, class Cmp >
bool TriTreeIterator< T, Cmp >::hasPrev() const
{
  if (prev().root)
  {
    return true;
  }
  return false;
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > begin(TriTree< T, Cmp > * root)
{
  TriTreeIterator< T, Cmp > iter{root, true};
  while (iter.hasPrev())
  {
    iter = iter.prev();
  }
  return iter;
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp > * root)
{
  TriTreeIterator< T, Cmp > iter{root, false};
  while (iter.hasNext())
  {
    iter = iter.next();
  }
  return iter;
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
TriTree< T, Cmp > * getTree(std::istream & in)
{
  size_t n = 0;
  if (!(in >> n))
  {
    throw std::logic_error("invalid input");
  }
  T first, second = 0;
  if (!(in >> first >> second))
  {
    throw std::logic_error("invalid input");
  }
  TriTree< T, Cmp > * tree = new TriTree< T, Cmp >{};
  if (!Cmp()(first, second)) std::swap(first, second);
  tree->data = std::make_pair(first, second);
  for (size_t i = 1; i < n; i++)
  {
    if (!(in >> first >> second))
    {
      throw std::logic_error("invalid input");
    }
    if (!Cmp()(first, second)) std::swap(first, second);
    insertTree(tree, std::make_pair(first, second));
  }
  return tree;
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
  TriTree< int, std::less< int > > * tree = nullptr;
  try
  {
    tree = getTree< int, std::less< int > >(std::cin);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
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
      std::cerr << "<INVALID COMMAND>\n";
      continue;
    }
    if (command == "intersects")
    {
      std::cout << countInters(tree, v1, v2) << '\n';
    }
    else if (command == "covers")
    {
      std::cout << countCovers(tree, v1, v2) << '\n';
    }
    else if (command == "avoids")
    {
      std::cout << countAvoids(tree, v1, v2) << '\n';
    }
  }
  clearTree(tree);
}
