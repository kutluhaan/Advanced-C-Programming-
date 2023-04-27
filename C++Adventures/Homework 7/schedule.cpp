//
// Created by kutlu on 16.04.2023.
//
//su-username: kutluhan
//su-id: 00029563

#include "schedule.h"
#include <ostream>
using namespace std;

Schedule::Schedule(){ // default constructor
    time_slots = 0;
    data = new string * [7];

    for (int i = 0; i < 7; i++) //set all cells to NULL
        data[i] = NULL;
}

Schedule::Schedule(int c) { // parameter constructor
    time_slots = c;
    data = new string * [7];

    for (int i = 0; i < 7; i++) // initialize the column for cells
        data[i] = new string [c];

    for (int i = 0; i < 7; i++){ // set all values to "free"
        for (int j = 0; j < c; j++)
            data[i][j] = "free";
    }
}

Schedule::Schedule(const Schedule & copy) { // deepcopy constructor
    this->time_slots = copy.time_slots; // take the time_slots
    this->data = new string * [7]; //initialize week
    for (int i = 0; i < 7; i++){ //copy every data
        this->data[i] = new string [this->time_slots]; // initialize week's day
        for (int j = 0; j < this->time_slots; j++)
            this->data[i][j] = copy.data[i][j];
    }
}

Schedule::~Schedule() { // destructor
    time_slots = 0;
    for (int i = 0; i < 7; i++){
        if (data[6-i] != NULL){
            delete [] data[6 - i];
            data[6 - i] = NULL;
        }
    }
    delete [] data; //delete data at the end
}

const Schedule & Schedule::operator = (const Schedule & rhs) { // = operator
    if(this != &rhs){
        if (time_slots != rhs.time_slots) //if not same delete the lhs
            this->~Schedule();
        string ** temp = new string * [7]; //initialize a new data string**
        for (int i = 0; i < 7; i++){
            temp[i] = new string [rhs.time_slots]; // initialize the week's day and copy data
            for (int j = 0; j < rhs.time_slots; j++)
                temp[i][j] = rhs.data[i][j];
        }
        time_slots = rhs.time_slots; //assigning values
        data = temp;
    }
    return *this;
}

Schedule Schedule::operator + (const Days & day) { // make a specific day "busy"
    Schedule newSchedule(*this);
    int index = Days(day);
    for (int i = 0; i < time_slots; i++)
        newSchedule.data[index][i] = "busy";
    return newSchedule;
}

Schedule Schedule::operator + (const int &rhs) { // make specific time slot "busy"
    Schedule newSchedule(*this);
    for (int i = 0; i < 7; i++)
        newSchedule.data[i][rhs] = "busy";
    return newSchedule;
}

Schedule Schedule::operator + (const Schedule & rhs){ // finding common free slots
    Schedule newSchedule(*this);
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < rhs.time_slots; j++){
            if (!(rhs.data[i][j] == "free" && newSchedule.data[i][j] == "free")) // if both not "free", then "busy". otherwise "free".
                newSchedule.data[i][j] = "busy";
        }
    }
    return newSchedule;
}

const Schedule Schedule::operator*(Schedule & rhs) { // find busy slots
    Schedule newSchedule(*this);
    for (int i = 0; i < 7; i++){ // set all to "free"
        for (int j = 0; j < newSchedule.time_slots; j++)
            newSchedule.data[i][j] = "free";
    }
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < rhs.time_slots; j++){
            if (this->data[i][j] == "busy" && rhs.data[i][j] == "busy")  // if both "busy", then "busy".
                newSchedule.data[i][j] = "busy";
        }
    }
    return newSchedule;
}

string* Schedule::operator [] (const Days day) const{ // return a specific day
    int dayIndex = Days(day);
    return this->data[dayIndex];
}

bool Schedule::operator < (const Schedule & rhs) { // counting busy and free slots in both schedules
    int lhsBusy = 0, rhsBusy = 0;
    for (int i = 0; i < 7; i++){
        for (int j = 0; j < rhs.time_slots; j++){
            if (this->data[i][j] == "busy")
                lhsBusy++;
            else if (rhs.data[i][j] == "busy")
                rhsBusy++;
        }
    }

    if (lhsBusy < rhsBusy) // returning the result
        return true;
    return false;
}

string** Schedule::dataGetter() const{ return data; } // getter for data

int Schedule::slotGetter() const { return time_slots; } // getter for time_slots

ostream& operator << (ostream& os, const Schedule & rhs){ // output the schedule object
    string** temp = rhs.dataGetter();
    int SLOT = rhs.slotGetter();
    for (int i = 0; i < 7; i++){ // based on i, show the day
        if (i == 0)
            os << "Mo:";
        else if (i == 1)
            os << "Tu:";
        else if (i == 2)
            os << "We:";
        else if (i == 3)
            os << "Th:";
        else if (i == 4)
            os << "Fr:";
        else if (i == 5)
            os << "Sa:";
        else if (i == 6)
            os << "Su:";
        for (int j = 0; j < SLOT; j++){
            if (*temp != NULL) // if there is a string array, show the content
                os << " " << temp[i][j];
        }
        os << endl;
    }
    return os;
}

ostream& operator << (ostream& os, const Days & rhs) { // show the days in full length
    int day = rhs;
    if (day == 0)
        os << "Monday";
    else if (day == 1)
        os << "Tuesday";
    else if (day == 2)
        os << "Wednesday";
    else if (day == 3)
        os << "Thursday";
    else if (day == 4)
        os << "Friday";
    else if (day == 5)
        os << "Saturday";
    else if (day == 6)
        os << "Sunday";
    return os;
}
