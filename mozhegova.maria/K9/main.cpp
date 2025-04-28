#include <iostream>
#include <string>
#include <functional>

template< class T, class Cmp >
struct TriTree {
  std::pair< T, T > data;
  TriTree< T, Cmp > * left, * middle, * right, * parent;
};

template< class T, class Cmp >
struct TriTreeIterator {
public:
  using this_t = TriTreeIterator< T, Cmp >;
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
std::pair< T, T > & TriTreeIterator< T, Cmp >::data()
{
  return root->data;
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > TriTreeIterator< T, Cmp >::prev() const
{
  if (isFirst)
  {
    if (root->left)
    {
      root = root->left;
      while (root->right)
      {
        root = root->right;
      }
      return TriTreeIterator< T, Cmp >{root, false};
    }
    else
    {
      while (root->parent && root == root->parent->left)
      {
        root = root->parent;
      }
      if (root->parent && root == root->parent->right)
      {
        return TriTreeIterator< T, Cmp >{root->parent, false};
      }
      return TriTreeIterator< T, Cmp >{root->parent, true};
    }
  }
  else
  {
    if (root->middle)
    {
      root = root->middle;
      while (root->right)
      {
        root = root->right;
      }
      return TriTreeIterator< T, Cmp >{root, false};
    }
    else
    {
      return TriTreeIterator< T, Cmp >{root, true};
    }
  }
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > TriTreeIterator< T, Cmp >::next() const
{
  if (isFirst)
  {
    if (root->middle)
    {
      root = root->middle;
      while (root->left)
      {
        root = root->left;
      }
      return TriTreeIterator< T, Cmp >{root, true};
    }
    else
    {
      return TriTreeIterator< T, Cmp >{root, false};
    }
  }
  else
  {
    if (root->right)
    {
      root = root->right;
      while (root->left)
      {
        root = root->left;
      }
      return TriTreeIterator< T, Cmp >{root, true};
    }
    else
    {
      while (root->parent && root == root->parent->right)
      {
        root = root->parent;
      }
      if (root->parent && root == root->parent->left)
      {
        return TriTreeIterator< T, Cmp >{root->parent, true};
      }
      return TriTreeIterator< T, Cmp >{root->parent, false};
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
  TriTree< T, Cmp > * temp = root;
  TriTreeIterator< T, Cmp > iter = new TriTreeIterator< T, Cmp >{temp, true};
  while (iter.hasPrev())
  {
    iter = iter.prev();
  }
  return iter;
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp > * root)
{
  TriTree< T, Cmp > * temp = root;
  TriTreeIterator< T, Cmp > iter = new TriTreeIterator< T, Cmp >{temp, false};
  while (iter.hasNext())
  {
    iter = iter.next();
  }
  return iter;
}

int main()
{}
