//
// Created by kutlu on 3.04.2023.
//
//Aygüzel Kutluhan
//su-username: kutluhan

#include <iostream>
#include "Board.h"
#include "CharStack.h"
using namespace std;

Board::Board(){ //constructor
    CharStack board;
    head = NULL;
    tail = NULL;
    xCnt = 0;
    oCnt = 0;
}

bool Board::noMove(char player_char, int range) {
    slot * temp = head;
    int beforePos = 1, afterPos = 1, totalPos = 0; //total positions, before the donor index, after the donor index
    char ch;
    while (temp != NULL){
        if (!temp->slotStack.isEmpty()){ //if not empty check the value
            temp->slotStack.pop(ch);
            temp->slotStack.push(ch);
            if (ch == player_char){ //if value is okay
                slot * before = temp;
                slot * after = temp;
                for (int i = 0; i < range; i++){
                    if (before != NULL)
                        before = before->prev;
                    else
                        beforePos--; //if we could not reach the index before donor
                    if (after != NULL)
                        after = after->next;
                    else
                        afterPos--; //if we could not reach the index after donor
                }
                if (after == NULL || after->slotStack.isFull())
                    afterPos--;
                else if (!after->slotStack.isEmpty() ){ //if not full and not NULL and not empty, pop the value and check
                    after->slotStack.pop(ch);
                    after->slotStack.push(ch);
                    if(ch != player_char) //if value is not player_char
                        afterPos--;
                }
                if (before == NULL || before->slotStack.isFull()) //same things we do for after donor index
                    beforePos--;
                else if(!before->slotStack.isEmpty()){
                    before->slotStack.pop(ch);
                    before->slotStack.push(ch);
                    if (ch != player_char)
                        beforePos--;
                }
                if (temp != NULL) //go on
                    temp = temp->next;
                if (afterPos > 0) //check the conditions for possible positions
                    totalPos++;
                if (beforePos > 0)
                    totalPos++;
                beforePos = 1; //reset the values
                afterPos = 1;
            }
            else{
                if (temp != NULL) //if not NULL, go on
                    temp = temp->next;
            }
        }
        else{ //if empty and not last slot, then go on
            if (temp != NULL)
                temp = temp->next;
        }
    }
    if (totalPos == 0) //check the last situation for possible positions
        return true;
    else
        return false;
}

int Board::validMove(char player_char, int index, int range, int direction){
    int listIndex = 0;
    slot * temp = head;
    while (true) { //checking the entered slot and character of the entered slot
        if (listIndex == index && temp!= NULL){ //if arrived and not out of bounds
            char ch;
            temp->slotStack.pop(ch);
            temp->slotStack.push(ch); //check the character in the slot
            if (ch != player_char)
                return 4;
            else
                break;
        }
        else if (listIndex != index && temp == NULL) //if not arrived and out of bounds
            return 1;
        else{
            if (temp != NULL) //go on and increase the index
                temp = temp->next;
            listIndex++;
        }
    }
    if (direction == 0) { //direction check
        for (int i = 0; i < range; i++){ //go till come to range
            if (temp != NULL)
                temp = temp->prev;
            else
                return 2; //if range out of bounds
        }
        char ch;
        if (!temp->slotStack.isEmpty()) { //if not empty pop and check the value
            temp->slotStack.pop(ch);
            temp->slotStack.push(ch);
            if (ch != player_char)
                return 3;
            else
                return 0;
        }
    }
    else{ //for other direction
        for (int i = 0; i < range; i++){ //go till come to range
            if (temp != NULL)
                temp = temp->next;
            else
                return 2; //if range out of bounds
        }
        char ch;
        if (!temp->slotStack.isEmpty()){ //if not empty pop and check the value
            temp->slotStack.pop(ch);
            temp->slotStack.push(ch);
            if (ch != player_char)
                return 3;
            else
                return 0;
        }

    }
    return 0; //must return something
}

void Board::movePiece(int source, int targetInd){
    slot * temp = head;
    for (int i = 0; i < source; i++){ //come till source
        if (temp != NULL)
            temp = temp->next;
    }
    char ch;
    temp->slotStack.pop(ch); //pop the source's value
    temp = head; //come back
    for (int i = 0; i < targetInd; i++){ //go to the target index
        if (temp != NULL)
            temp = temp->next;
    }
    temp->slotStack.push(ch); //push character to target index
}

void Board::printBoard(){ //finished
    slot * temp = head;//assigning head
    char ch;
    string last = "|", final = "", caret = "";
    int index = 1, increment = 0, location = 0, caretLong = 0;
    while(temp != NULL){ //take all the values as a 4 size string
        string first = "", missing = ""; //first string and missing values as 4 - length
        while (!temp->slotStack.isEmpty()) { //if not empty pop it until it becomes empty
            temp->slotStack.pop(ch);
            if (ch != 'x' && ch != 'o' && ch != ' ') //check the character
                ch = ' ';
            first += ch;
        }
        if (first.length() != 4){ //add the missing ' '
            for (int i = 0; i < 4 - first.length(); i++){
                missing += " ";
            }
        }
        last += missing + first + "|"; //separate the slots' values
        temp = temp->next; //go on
    }
    while (true){ //reformatting the string
        if (index + increment < last.length()){ //take the values of strings as it will be printed
            final += last[index + increment];
            increment += 5;
        }
        else{
            final += "|"; //separate the strings that will be represent the board
            index++;
            increment = 0;
        }
        if (index == 5) //if it comes to end of the reformatting
            break;
    }
    while (true){
        caretLong = location; //assign the length of caret string
        location = final.find("|"); //read the string by referencing |
        if (location == string::npos)
            break;
        else{
            cout << final.substr(0, location) << endl; //cut the printed part out
            final = final.substr(location + 1); //shorten
        }
    }
    for (int i = 0; i < caretLong; i++) //shape the final caret string
        caret += "^";
    cout << caret << endl;
    last = last.substr(1); //cut out the first |
    temp = head; //come back
    for (int i = 0; i < last.length() - 1; i++){ //push all values back
        if (last[i] == '|')
            temp = temp->next;
        else if (last[i] != ' ')
            temp->slotStack.push(last[i]);
    }
}

int Board::evaluateGame(){
    slot * temp = head;
    string allchars = ""; //the string will hold all the chars in the lists
    char ch;
    while (temp != NULL){
        while(!temp->slotStack.isEmpty()){ //if not empty take the char from it
            temp->slotStack.pop(ch);
            allchars += ch; //assign it to string
        }
        allchars += "|"; //after one slot make separation
        temp = temp->next; //go on
    }
    temp = head; //come back
    for (int i = 0; i < allchars.length(); i++){ //pushing back
        if (allchars[i] == '|')
            temp = temp->next;
        else{
            temp->slotStack.push(allchars[i]);
            if(allchars[i] == 'x') //count x in string
                xCnt++;
            else if(allchars[i] == 'o') //count o in string
                oCnt++;
        }
    }
    if (oCnt > xCnt) //evaluate the xCnt and oCnt
        return 1;
    else if (xCnt > oCnt)
        return 2;
    else
        return 3;
}

bool Board::targetSlotFull(int index){
    int number = 0; //index control
    slot * temp = head;
    while (temp != NULL){
        if (number == index){ //if arrive to right slot
            if (temp->slotStack.isFull())
                return true;
            else
                return false;
        }
        else{
            number++; //increase index and go forward in list
            temp=temp->next;
        }
    }
    return true; //must return something
}

void Board::destroySlot(int index){
    slot * temp = head;
    int number = 0; //controlling index
    while(temp != NULL){
        if(number == index){ //if arrive to right index
            if (temp == head){ //if the index is head
                if (head != NULL){
                    head = head->next; //make head its next
                    head->prev = NULL; //make its prev NULL
                    temp = NULL; //make temp (tobedeleted) NULL
                    delete temp;
                    break;
                }
                else{
                    delete head;
                    break;
                }
            }
            else{
                if (temp == tail){ //if it is the last
                    slot * before = temp->prev; //new slot before tail
                    before->next = NULL;
                    tail = before;
                    temp = NULL;
                    delete temp;
                    break;
                }
                slot * before = temp->prev; //make it the slot before temp
                before->next = temp->next; //link it to slot after temp
                temp->next->prev=before; //make the slot after temp linked to before
                temp = NULL;
                delete temp;
                break;
            }
        }
        else{
            number++; //increase index num and go forward in list
            temp=temp->next;
        }
    }
}

void Board::createSlotBegin(char player_char, int num){
    slot * newHead = new slot(); //new slot
    for (int i = 0; i < num; i++) //push the values
        newHead->slotStack.push(player_char);
    head->prev = newHead; //link head to new head
    newHead->next=head; //link new head to head
    newHead->prev = NULL; //make new head's prev to NULL
    head = newHead; //make head new head
}

void Board::createSlotEnd(char player_char, int num){
    slot * end = new slot(); //new slot
    for(int i = 0; i < num; i++)
        end->slotStack.push(player_char); //push the values
    if (head == NULL){ //if first slot
        head = end; //head becomes end
        end->prev = NULL; //prev and next are NULL
        end->next = NULL;
        tail = end; //tail becomes end
    }
    else{
        end->prev = tail; //link end to tail
        tail->next = end; //link tail to end
        end->next = NULL; //make end next NULL
        tail = end; //tail becomes end
    }
}

void Board::createEmptySlotEnd(){
    slot * end = new slot(); //create empty slot
    end->prev = NULL; //make its prev and next NULL
    end->next = NULL;
    if (head == NULL){ //if it's the first slot in list
        tail = end; //make tail end
        head = tail; //tail and head are same
    }
    else{ //if there is more than one slot in list
        end->prev = tail; //link end to tail
        tail->next = end; //link tail to end
        tail = end;
    }
}

void Board::clearBoard(){
    while(head != NULL){
        slot * temp = head; //before head
        head = head->next; //head becomes its next
        if (head != NULL)
            head->prev = NULL; //make prev NULL
        else{ //if head = NULL
            head = NULL;
            tail = NULL;
            delete head; //delete both tail and head
            delete tail;
        }
        temp = NULL; //before delete temp make it NULL
        delete temp;
    }
}
