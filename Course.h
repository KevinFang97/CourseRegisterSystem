#ifndef COURSE_H
#define COURSE_H

#include <string>

using std::string;

enum Credit {ONE = 1, TWO = 2, THREE = 3, FOUR = 4, FIVE = 5, SIX = 6};

class Course {
public:
  static const int NUM_OF_BUCKETS = 17;
  static const int BASE = 36;
  
  string courseCode;
  string courseName;
  Credit credit;
  
  Course(string code, string name, Credit cre): courseCode(code), courseName(name), credit(cre){}
  
  //overload comparative operator
  bool operator<(const Course&) const;
  bool operator>(const Course&) const;
  bool operator<=(const Course& c) const {return !((*this) > c);}
  bool operator>=(const Course& c) const {return !((*this) < c);}
  bool operator==(const Course&) const;
  bool operator!=(const Course&) const {return !((*this) == c);}
  
  //overload with hash function
  int operator()() const;
  
  //0~9 -> 48~57, A~Z -> 65~90
  int charHash(char c) {
    if(c < 58) return c - 48;
    return c - 54;
  }
}

bool Course::operator<(const Course& c) const {
  for(int i = 0; i < 7; i++)
    if(courseCode[i] < c.courseCode[i]) return true;
    else if(courseCode[i] > c.courseCode[i]) return false;
  //post condition:first 7 char equal  

  if(size() == 7) return false;
  //post condition:this has 8 char
  
  if(c.size() == 7) return false;
  //post condition:both have 8 char
  
  return courseCode[7] < c.courseCode[7];
}

bool Course::operator>(const Course& c) const {
  for(int i = 0; i < 7; i++)
    if(courseCode[i] > c.courseCode[i]) return true;
    else if(courseCode[i] < c.courseCode[i]) return false;
  //post condition:first 7 char equal  

  if(size() == 7) return false;
  //post condition:this has 8 char
  
  if(c.size() == 7) return true;
  //post condition:both have 8 char
  
  return courseCode[7] > c.courseCode[7];
}

bool Course::operator==(const Course& c) const {
  if(size() != c.size()) return false;
  for(int i = 0; i < size(); i++)
    if(courseCode[i] != c.courseCode[i]) return false;
  return true;
}

int Course::operator()() const {
  int temp = 1;
  int result = 0;
  for(int i = 0; i < size(); i++) {
    result += charHash(courseName[i])*temp%NUM_OF_BUCKETS;
    temp = temp*BASE%NUM_OF_BUCKETS;
  }
  result %= NUM_OF_BUCKETS;
  return result;
}

#endif