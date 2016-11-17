#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "OrderedDoublyLinkedList.h"
#include <vector>

using std::vector;

//a hash table using separate chaining
//it's actually an array of ODLinkedList

//only take one typename as value
//here T can be Student, Course, cs_course_iterator, cs_student_iterator
//which overload coparative operators
//and valid copy constructor
//and operator() as hash function which will return an int (0 ~ size-1)

//it's always used in another container class
//it's ok to use public array of ODLinkedList
//data encapsulation can be done in those upper level container classes
//i.e. StudentTable, CourseTable, IndexCourseTable, IndexStudentTable

//should not have a default constructor

template<typename T>
class HashTable {
public:
  const int size;
  vector<ODLinkedList<T>*> hashArr;
  HashTable(int);
  const T* find(const T&); //return nullptr if not exist
  bool insert(const T& item) {return hashArr[item()]->insert(item);}
  bool remove(const T& item) {return hashArr[item()]->remove(item);}
};

//initialize the hash table with empty ODLinkedList
template<typename T>
HashTable<T>::HashTable(int sz): size(sz), hashArr(sz) {
  for(int i = 0; i < size; i++)
    hashArr[i] = new ODLinkedList<T>();
}

template<typename T>
const T* HashTable<T>::find(const T& item) {
  Node<T>* node = hashArr[item()]->find(item);
  if(node) return &(node->elem);
  else return nullptr;
}



#endif