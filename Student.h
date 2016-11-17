#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <array>

using std::string;
using std::array;

enum Year { YEAR_ONE = 1, YEAR_TWO = 2, YEAR_THREE = 3};
enum Gender {FEMALE, MALE};

class Student {
public:
  static const int ID_LENGTH = 8;
  static const int NUM_OF_BUCKETS = 29;
  static const int BASE = 10;
  
  array<int,ID_LENGTH> ID;
  string name;
  Year year;
  Gender gender;
  
  Student(array<int,ID_LENGTH> id, string nm, Year y, Gender g): ID(id), name(nm), year(y), gender(g) {}

  //comparative operations overloaded
  bool operator<(const Student&) const;
  bool operator>(const Student&) const;
  bool operator<=(const Student& s) const {return !((*this)>s);};
  bool operator>=(const Student& s) const {return !((*this)<s);};
  bool operator==(const Student&) const;
  bool operator!=(const Student& s) const {return !((*this)==s);}
  
  //overload hash func
  int operator()() const;
};

bool Student::operator<(const Student& s) const {
  for(int i = 0; i < ID_LENGTH; i++) 
    if(this->ID[i] < s.ID[i]) return true;
    else if (this->ID[i] > s.ID[i]) return false;
  return false;
}

bool Student::operator>(const Student& s) const {
  for(int i = 0; i < ID_LENGTH; i++) 
    if(this->ID[i] > s.ID[i]) return true;
    else if (this->ID[i] < s.ID[i]) return false;
  return false;
}

bool Student::operator==(const Student& s) const {
  for(int i = 0; i < ID_LENGTH; i++) 
    if(this->ID[i] != s.ID[i]) return false;
  return true;
}

int Student::operator()() const {
  int temp = 1; // the module of power of 10
  int result = 0;
  for(int i = 0; i < ID_LENGTH; i++) {
    result += ID[i]*temp%NUM_OF_BUCKETS;
    temp = temp*BASE%NUM_OF_BUCKETS;
  }
  result %= NUM_OF_BUCKETS;
  return result;
}

#endif