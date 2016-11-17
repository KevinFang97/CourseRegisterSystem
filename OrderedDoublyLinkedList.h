//#ifndef ORDERED_DOUBLY_LINKED_LIST_H
//#define ORDERED_DOUBLY_LINKED_LIST_H

#include <iostream>
//a doubly linked list sorted in ascending order from first to last
//NOT CIRCULAR!!!



//to avoid neccesity of iterators, make node public
//since ODLinkedList is only used in other container classes
//that's totally safe

template<typename T>
struct Node {
  T elem;//element stored in list
  Node* prev;//previous node
  Node* next;//next node
  
  //construction for Node
  /* to be completed*/
  Node() = default;
  Node(const T& item): elem(item), prev(nullptr), next(nullptr) {}
  Node(const T& item, Node* p, Node* n): elem(item), prev(p), next(n) {}
};
  
template<typename T>
class ODLinkedList {
public:
  ODLinkedList(): first(nullptr), last(nullptr), size(0) {}//to be completed
  
  Node<T>* first;
  Node<T>* last;
  
  bool isEmpty() {return !first;};
  int getSize() {return size;};
  
  Node<T>* find(const T&); //return nullptr if not exist
  bool insert(const T&); //return false if duplicate
  bool remove(const T&); //return false if doesn't exist
  
private:
  int size;
};

template<typename T>
Node<T>* ODLinkedList<T>::find(const T& item) {
  for(Node<T>* cur = first; cur != nullptr; cur = cur->next) 
    if(cur->elem == item) return cur; //return true if found
    else if (cur->elem > item) return nullptr; //return false if no need to move on
  return nullptr;
}

//if duplicated, return false
//return true right after insertion completed
template<typename T>
bool ODLinkedList<T>::insert(const T& item) {
  //special cases (when it's empty)
  if(!first) {last = first = new Node<T>(item); return true;}
  //special cases (when insert before first)
  if(first->elem > item) {
    first->prev = new Node<T>(item, nullptr, first);
    first = first->prev;
    return true;
  }
  //special cases (when insert after last)
  if(last->elem < item) {
    last->next = new Node<T>(item, last, nullptr);
    last = last->next;
    return true;
  }
  //when insertion falls in between
  Node<T>* cur;
  for(cur = first; cur != nullptr; cur = cur->next) {
    if(cur->elem == item) return false; //return false if duplicate
    if(cur->elem > item) break;
  }
  //insert at left of cur
  Node<T>* cur_left = cur->prev;
  cur_left->next = cur->prev = new Node<T>(item, cur_left, cur);
  
}

//return false if cannot find item, true if delete success
template<typename T>
bool ODLinkedList<T>::remove(const T& item) {
  Node<T>* trash = find(item);
  if(!trash) return false;
  if(first == trash) first = trash->next;
  if(last == trash) last = trash->prev;
  if(trash->prev) trash->prev->next = trash->next;
  if(trash->next) trash->next->prev = trash->prev;
  delete trash;
  return true;
}
//#endif