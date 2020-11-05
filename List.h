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
    return (first == nullptr) && (last == nullptr);
  }

  //EFFECTS: returns the number of elements in this List
  int size() const
  {
    if (empty())
      return 0;
    return last - first + 1;
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
    Node new_node = {first, nullptr, datum};
    if (empty())
    {
      first = &new_node;
      last = first;
    }
    else
    {
      first->prev = &new_node;
      first = first->prev;
    }
  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum)
  {
    {
      Node new_node = {nullptr, last, datum};
      if (empty())

      {
        last = &new_node;
        first = last;
      }
      else
      {
        last->next = &new_node;
        last = last->next;
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
      first = first->next;
      delete n;
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

      last = last->prev;
      delete n;
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
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    Iterator();
    ~Iterator();
    Iterator(const &Iterator I);

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
    Iterator(Node *p);

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
    return Iterator(last->next); //need some work
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i)
  {
    typename List<T>::Node p = (i.node_ptr)->prev;
    typename List<T>::Node n = (i.node_ptr)->next;
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum)
  {
  }

}; //List

////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

#endif // Do not remove this. Write all your code above this line.
