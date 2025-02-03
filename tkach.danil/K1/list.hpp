#ifndef LIST_HPP
#define LIST_HPP

namespace tkach
{
  struct BiList {
    int value;
    BiList * prev, * next;
  };
}

#endif