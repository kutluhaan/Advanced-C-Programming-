#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <iomanip>
#include <ctime>
#include <mutex>
#include "IntQueueHW6.h"
using namespace std;

mutex myMutex;


//************************************************
// Function search a number in the given vector. *
//************************************************

bool Search(vector <int> myVector, int number){

    //if found return true otherwise false
    for (int i = 0; i < myVector.size(); i++){
        if (myVector[i] == number)
            return true;
    }
    return false;
}


//*******************************************************************
// Function shows the numbers of the threads sitting on the chairs. *
//*******************************************************************

void Remain (IntQueueHW6 chairs, int player_num){

    int temp = 0; //this value of int will change in every iteration
    cout << "Remaining players are as follows: ";
    for (int i = 0; i < player_num; i++){
        if (!chairs.isEmpty()){
            // take the number out and display it
            chairs.dequeue(temp);
            cout << temp << " ";
        }
    }
    chairs.clear(); //clear the chairs
    cout << endl;
}


//************************************************************
// Function is starting point of a new thread.               *
// In this function threads race and tries to sit on a chair *
// in the given queue. If there is no empty chair to sit,    *
// then add the thread to the eliminated players vector.     *
//************************************************************

void start(IntQueueHW6 & chairs, int position, struct tm * time, vector<int> & non_players){
    //sleep until two seconds more of the current time
    this_thread::sleep_until(chrono::system_clock::from_time_t(mktime(time)));
    //lock for the scheduling intervention
    myMutex.lock();
    if (!chairs.isFull()){ //if ne one is sitting on the chair
        chairs.enqueue(position); //sit on it
        cout << "Player " << position << " captured a chair at " << put_time(time, "%X") << "." << endl;
    }
    else{
        //if no empty chairs anymore
        cout << "Player " << position <<  " couldn't capture a chair." << endl;
        //add to eliminated players list
        non_players.push_back(position);
    }
    //unlock the mutex
    myMutex.unlock();
}

int main() {
    int player_num, copy;
    //output lines
    cout << "Welcome to Musical Chairs game!\n";
    cout << "Enter the number of players in the game: \n";
    cin >> player_num;
    cout << "Game Start!\n";

    copy = player_num; //to preserve the input assign copy to player_num
                       //while decreasing the copy the player number is still
                       //same value as at the beginning
    //time configuration
    time_t systemTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    struct tm *chronometer = new struct tm;
    localtime_s(chronometer, &systemTime);

    thread players[player_num]; //thread list
    vector <int> non_players; //eliminated players vector

    while (copy > 1){ //when there is still a player
        IntQueueHW6 chairs(copy - 1); //always put one less chair than the number of players
        cout << endl << "Time is now " << put_time(chronometer,"%X") << endl; //show time
        chronometer->tm_sec = chronometer->tm_sec+2; //add two secs

        //take a chair if you are not eliminated
        for (int i = 0; i < player_num; i++){
            string temp = to_string(i);
            if (!Search(non_players, i))
                //if not eliminated then have a sit
                //give the beginning of the thread function, chairs to sit, a number for thread to sit,
                //a time to set the sit time, a vector to add the eliminated players
                players[i] = thread(&start, ref(chairs), i, chronometer,ref(non_players));
        }

        for (int i = 0; i < player_num; i++){
            //if not eliminated then join to main thread
            string temp = to_string(i);
            if (!Search(non_players, i))
                players[i].join();
        }
        if (copy == 2){ //if it is end of the game
            int winner_num = 0;
            //take the number with dequeue and put it back enqueue
            // and show the remaining and winner
            chairs.dequeue(winner_num);
            chairs.enqueue(winner_num);
            Remain(chairs, player_num);
            cout << "\nGame Over!\n";
            cout << "Winner is Player " << winner_num << "!";
        }
        else
            Remain(chairs, player_num); //print the remaining players
        copy--; //decrease one to initialize one less chair setting at the beginning
    }
    delete chronometer; //delete the time pointer
    return 0;
}