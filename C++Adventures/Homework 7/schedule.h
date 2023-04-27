//
// Created by kutlu on 16.04.2023.
//

#ifndef HOMEWORK_4_SCHEDULE_H
#define HOMEWORK_4_SCHEDULE_H
#include <string>
#include <ostream>
using namespace std;
enum Days {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday}; // days list
class Schedule{
private:
    int time_slots;                                              // time slot data
    string** data;                                               // double string pointer
public:
    Schedule();                                                  // default constructor
    Schedule(int);                                               // parameter constructor
    Schedule(const Schedule&);                                   // deep copy constructor
    ~Schedule();                                                 // destructor
    const Schedule& operator = (const Schedule &);               // = operator: assign lhs to rhs
    Schedule operator + (const Days &);                          // + operator: assign all day to busy
    Schedule operator + (const int &);                           // + operator: assigns a time slot too busy
    Schedule operator + (const Schedule &);                      // + operator: assigns common free time slots to an schedule object
    const Schedule operator * (Schedule &);                      // * operator: assign common busy time slots to an schedule object
    string* operator [] (const Days) const;                      // []operator: returns the row pointer of a day
    bool operator < (const Schedule &);                          // < operator: compares busy slots and returns a boolean value
    string** dataGetter() const;                                 // getter function for data
    int slotGetter () const;                                     // getter function for time_slots
};
ostream& operator << (ostream&, const Schedule &);               // <<operator: displays the content of the schedule
ostream& operator << (ostream&, const Days &);                   // <<operator: displays the Days type variables

#endif //HOMEWORK_4_SCHEDULE_H
