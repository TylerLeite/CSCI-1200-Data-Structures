#ifndef dslist_h_
#define dslist_h_
// A simplified implementation of a generic list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined: a Node class, an iterator class, and
// the actual list class.  The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular.

#include <cassert>

// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
  Node() : next_(NULL), prev_(NULL) {}
  Node(const T& v) : value_(v), next_(NULL), prev_(NULL) {}

  // REPRESENTATION
  T value_;
  Node<T>* next_;
  Node<T>* prev_;
};

// A "forward declaration" of this class is needed
template <class T> class dslist;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:
  list_iterator() : ptr_(NULL) {end = false;}
  list_iterator(Node<T>* p) : ptr_(p) {end = false;}
  list_iterator(list_iterator<T> const& old) : ptr_(old.ptr_) {end = old.end;}
  ~list_iterator() {}

  list_iterator<T> & operator=(const list_iterator<T> & old) { 
    ptr_ = old.ptr_;  end = old.end; return *this; 
  }

  // dereferencing operator gives access to the value at the pointer
  T operator*()  {if (end) return NULL; else return ptr_->value_; }

  // increment & decrement operators
  list_iterator<T> & operator++() { // pre-increment, e.g., ++iter
    if (ptr_->next_ == NULL) end = true; else ptr_ = ptr_->next_; 
    return *this;
  }
  list_iterator<T> operator++(int) { // post-increment, e.g., iter++
    list_iterator<T> temp(*this);
    
    if (ptr_->next_ == NULL) end = true; else ptr_ = ptr_->next_;
    return temp;
  }
  list_iterator<T> & operator--() { // pre-decrement, e.g., --iter
    if (end) end = false; else ptr_ = ptr_->prev_;
    return *this;
  }
  list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
    list_iterator<T> temp(*this);
    if (end) end = false; else ptr_ = ptr_->prev_;
    return temp;
  }

  friend class dslist<T>;

  // Comparions operators are straightforward
  bool operator==(const list_iterator<T>& r) const {
    return ptr_ == r.ptr_ && end == r.end;
  }
  bool operator!=(const list_iterator<T>& r) const {
    return ptr_ != r.ptr_ || end != r.end;
  }

  bool end;

private:
  // REPRESENTATION
  Node<T>* ptr_;    // ptr to node in the list
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class dslist {
public:
  dslist() : head_(NULL), tail_(NULL), size_(0) {}
  dslist(const dslist<T>& old) { this->copy_list(old); }
  ~dslist() { this->destroy_list(); }
  dslist& operator= (const dslist<T>& old);

  unsigned int size() const { return size_; }
  bool empty() const { return head_ == NULL; }
  void clear() { this->destroy_list(); }
   
  void push_front(const T& v);
  void pop_front();
  void push_back(const T& v);
  void pop_back();

  const T& front() const { return head_->value_;  }
  T& front() { return head_->value_; }
  const T& back() const { return tail_->value_; }
  T& back() { return tail_->value_; }

  typedef list_iterator<T> iterator;
  iterator erase(iterator itr);
  iterator insert(iterator itr, T const& v);
  iterator begin() { return iterator(head_); }
  iterator end() {iterator out = iterator(tail_); out.end = true; return out;}

private:
  void copy_list(dslist<T> const & old);
  void destroy_list();
  void destroy_from(Node<T>* node);

  //REPRESENTATION
  Node<T>* head_;
  Node<T>* tail_;
  unsigned int size_;

};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T>
dslist<T>& dslist<T>::operator= (const dslist<T>& old) {
  if (&old != this) {
    this->destroy_list();
    this->copy_list(old);
  }
  return *this;
}


template <class T> 
void dslist<T>::push_back(const T& v) {
  Node<T>* newp = new Node<T>( v );
  // special case:  initially empty list
  if (!tail_) {
    head_ = tail_ = newp;
  }
  // normal case:  at least one node already
  else {
    newp -> prev_ = tail_;
    tail_ -> next_ = newp;
    tail_ = newp;
  }
  ++size_;
}


template <class T> 
void dslist<T>::push_front(const T& v) {




}


template <class T> 
void dslist<T>::pop_back() {





}


template <class T> 
void dslist<T>::pop_front() {





}


template <class T> 
typename dslist<T>::iterator dslist<T>::erase(iterator itr) {
  assert (size_ > 0);
  --size_;
  iterator result(itr.ptr_ -> next_);
  // One node left in the list.  
  if (itr.ptr_ == head_ && head_ == tail_) {
    head_ = tail_ = 0;
  }
  // Removing the head in a list with at least two nodes
  else if (itr.ptr_ == head_) {
    head_ = head_ -> next_;
    head_ -> prev_ = 0;
  }
  // Removing the tail in a list with at least two nodes
  else if (itr.ptr_ == tail_) {
    tail_ = tail_ -> prev_;
    tail_ -> next_ = 0;
  }
  // Normal remove
  else {
    itr.ptr_ -> prev_ -> next_ = itr.ptr_ -> next_;
    itr.ptr_ -> next_ -> prev_ = itr.ptr_ -> prev_;
  }
  delete itr.ptr_;
  return result;
}


// insert BEFORE the node indicated by the iterator and return an iterator to the new node
template <class T> 
typename dslist<T>::iterator dslist<T>::insert(iterator itr, T const& v) {
  ++size_ ;
  Node<T>* p = new Node<T>(v);
  p -> prev_ = itr.ptr_ -> prev_;
  p -> next_ = itr.ptr_;
  itr.ptr_ -> prev_ = p;
  if (itr.ptr_ == head_)
    head_ = p;
  else
    p -> prev_ -> next_ = p;
  return iterator(p);
}


template <class T> 
void dslist<T>::copy_list(dslist<T> const & old) {
  size_ = old.size_;
  // Handle the special case of an empty list.
  if (size_ == 0) {
    head_ = tail_ = 0;
    return;
  }
  // Create a new head node. 
  head_ = new Node<T>(old.head_ -> value_);
  // tail_ will point to the last node created and therefore will move
  // down the new list as it is built
  tail_ = head_;
  // old_p will point to the next node to be copied in the old list
  Node<T>* old_p = old.head_ -> next_;
  // copy the remainder of the old list, one node at a time
  while (old_p) {
    tail_ -> next_ = new Node<T>(old_p -> value_);
    tail_ -> next_ -> prev_ = tail_;
    tail_ = tail_ -> next_;
    old_p = old_p -> next_;
  }
}


template <class T>
void dslist<T>::destroy_list() {
//*
    destroy_from(head_);
    head_ = NULL;
    tail_ = NULL;
//*/
}

template <class T>
void dslist<T>::destroy_from(Node<T>* node) {    
    if (node != tail_){
        destroy_from(node->next_);
    }
    
    delete node;
}

#endif
