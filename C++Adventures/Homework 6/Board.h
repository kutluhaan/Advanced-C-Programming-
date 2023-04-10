//
// Created by kutlu on 3.04.2023.
//
//Aygüzel Kutluhan
//su-username: kutluhan
//su-id: 00029563

#ifndef HOMEWORK_3_BOARD_H
#define HOMEWORK_3_BOARD_H
#include "CharStack.h"
struct slot{                                    //slot struct
    slot * next;
    slot * prev;
    CharStack slotStack;                        //Character Stack
    slot()                                      //default constructor for variables in slot struct
    {}
};
class Board {
    private:                                    //private values
        slot * head;                            //head of the list
        slot * tail;                            //tail of the list
        int xCnt;                               //amount of x
        int oCnt;                               //amount of o
    public:
        Board();                                //constructor
        bool noMove(char, int);                 //checking move for every same character valued index
        int validMove(char, int, int, int);     //checks whether entered slot and target slots are okay or not
        void movePiece(int, int);               //moving the char
        void printBoard();                      //print the game board
        int evaluateGame();                     //check the amount of x and o
        bool targetSlotFull(int);               //check whether the target slot is full or not
        void destroySlot(int);                  //delete the slot from the list
        void createSlotBegin(char, int);        //add slot to beginning of the list with values
        void createSlotEnd(char, int);          //add slot to end of the list with values
        void createEmptySlotEnd();              //add empty slot to end of the list
        void clearBoard();                      //delete all the slots from the list and memory
};



#endif //HOMEWORK_3_BOARD_H
