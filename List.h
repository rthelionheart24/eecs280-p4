#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * Project UID c1f28c309e55405daf00c565d57ff9ad
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL

template <typename T>
class List
{
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
  //Default constructor of List
  List() : first(nullptr), last(nullptr) {}

  //Destructor of List
  ~List()
  {
    clear();
  }

  //Copy ctor of List
  List(const List<T> &other) : first(nullptr), last(nullptr)
  {
    copy_all(other);
  }

  List<T> &operator=(const List<T> &rhs)
  {
    if (this == &rhs)
      return *this;
    clear();
    copy_all(rhs);
    return *this;
  }

  //EFFECTS:  returns true if the list is empty
  bool empty() const
  {
    return first == nullptr;
  }

  //EFFECTS: returns the number of elements in this List
  int size() const
  {
    if (empty())
      return 0;
    int count = 0;
    for (Node *np = first; np; np = np->next)
      count++;

    return count;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T &front()
  {
    assert(!empty());
    T &result = first->datum;
    return result;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T &back()
  {
    assert(!empty());
    T &result = last->datum;
    return result;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum)
  {
    Node *new_node = new Node;
    new_node->datum = datum;
    new_node->prev = nullptr;
    new_node->next = nullptr;
    if (empty())
    {
      first = new_node;
      last = first;
    }
    else
    {
      new_node->next = first;
      first->prev = new_node;
      first = new_node;
    }
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum)
  {
    {
      Node *new_node = new Node;
      new_node->datum = datum;
      new_node->next = nullptr;
      new_node->prev = nullptr;

      if (empty())
      {
        last = new_node;
        first = last;
      }
      else
      {
        new_node->prev = last;
        last->next = new_node;
        last = new_node;
      }
    }
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the front of the list
  void pop_front()
  {
    assert(!empty());
    Node *n = first;
    if (size() > 1)
    {
      first = n->next;
      delete n;
      first->prev = nullptr;
    }
    else
    {
      delete n;
      first = nullptr;
      last = nullptr;
    }
  }

  //REQUIRES: list is not empty
  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes the item at the back of the list
  void pop_back()
  {
    assert(!empty());
    Node *n = last;
    if (size() > 1)
    {

      last = n->prev;
      delete n;
      last->next = nullptr;
    }
    else
    {
      delete n;
      first = nullptr;
      last = nullptr;
    }
  }

  //MODIFIES: may invalidate list iterators
  //EFFECTS:  removes all items from the list
  void clear()
  {
    while (!empty())
      pop_back();
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

private:
  //a private type
  struct Node
  {
    Node *next;
    Node *prev;
    T datum;
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other)
  {
    assert(empty());
    for (Node *np = other.first; np; np = np->next)
    {
      push_back(np->datum);
    }
  }

  Node *first; // points to first Node in list, or nullptr if list is empty
  Node *last;  // points to last Node in list, or nullptr if list is empty

public:
  ////////////////////////////////////////
  class Iterator
  {
    friend class List;
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // //Default ctor
    // Iterator() : node_ptr(nullptr) {}

    // Iterator(const Iterator &other) : node_ptr(other.node_ptr) {}

    // //Destructor
    // ~Iterator()
    // {
    //   delete node_ptr;
    // }

    // //Assignment operator
    // Iterator &operator=(const Iterator &rhs)
    // {
    //   if (this == &rhs)
    //     return *this;

    //   delete this->node_ptr;
    //   this->node_ptr = rhs.node_ptr;
    //   return *this;
    // }

    //Dereference symbol
    T &operator*()
    {
      assert(node_ptr);
      return node_ptr->datum;
    }

    //Get the next iterator
    Iterator &operator++()
    {
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    //See if two iterators are pointing at the same node
    bool operator==(Iterator rhs) const
    {
      return node_ptr == rhs.node_ptr;
    }

    //See if two iterators are pointing at different nodes
    bool operator!=(Iterator rhs) const
    {
      return node_ptr != rhs.node_ptr;
    }

    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator &operator--()
    {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
    // add any additional necessary member variables here

    // add any friend declarations here

    // construct an Iterator at a specific position
    Iterator(Node *p) : node_ptr(p) {}

  }; //List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const
  {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const
  {
    if (empty())
      return Iterator(nullptr);

    return Iterator(last->next);
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i)
  {

    if (size() == 1)
    {
      first = nullptr;
      last = nullptr;
    }
    else
    {
      if (i.node_ptr == first)
      {
        first = first->next;
        first->prev = nullptr;
      }
      else if (i.node_ptr == nullptr)
      {
        last = last->prev;
        last->next = nullptr;
      }
      else
      {
        Node *p = (i.node_ptr)->prev;
        Node *n = (i.node_ptr)->next;
        //delete i.node_ptr;
        p->next = n;
        n->prev = p;
      }
    }
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum)
  {
    if (i.node_ptr == first)
    {
      push_front(datum);
    }
    else if (i.node_ptr == nullptr)
    {
      push_back(datum);
    }
    else
    {
      Node *p = (i.node_ptr)->prev;
      Node *n = (i.node_ptr)->next;
      Node new_node;
      new_node.datum = datum;
      new_node.next = i.node_ptr;
      new_node.prev = i.node_ptr->prev;

      p->next = &new_node;
      n->prev = &new_node;
    }
  }

}; //List

////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

#endif // Do not remove this. Write all your code above this line.
