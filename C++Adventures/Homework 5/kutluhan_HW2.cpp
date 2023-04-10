#include <iostream>
#include <string>
#include <cctype>
#include "feedback.h"
using namespace std;
struct node{
    int digit;
    node * next;
    node ()
            :digit(-5555), next(nullptr)
    {}
    node(int i, node *n)
            :digit(i), next(n)
    {}
};
node * Add(node * &head, int number){
    node * ptr = head;
    //first situation
    if (head == NULL || number < head->digit){ //it means that head is the first and and only pointer in that slot
        node * temp = new node(number, head);
        head = temp;
        return temp;
    }
    //if head is not the first pointer in the slot
    //other situations
    while(ptr->next != NULL && ptr->next->digit <number){
        ptr = ptr->next;
    }
    node * temp = new node(number, ptr->next);
    ptr->next = temp;
    return head;
}
void PrintValues(node * pos_head, node * im_head, int slot){
    cout << "Slot: " << slot << endl;
    cout << "Impossibles: ";
    while (im_head != NULL){
        cout << im_head->digit << " ";
        im_head = im_head->next;
    }
    cout << endl << "Possibles: ";
    while (pos_head != NULL){
        cout << pos_head->digit << " ";
        pos_head = pos_head->next;
    }
    cout << endl << endl;
}
void DeleteOneNode(node * &head, int detector){
    node * after = head, *prev = nullptr;
    while(after != NULL){
        if (after->digit != detector){
            prev = after;
            after = after->next;
        }
        else if (after->digit == detector){
            if (prev != nullptr){
                prev->next = after->next;
            }
            else {
                head = after->next;
            }
            after->next = NULL;
            delete after;
            return;
        }
    }
}
void DeleteList (node *&head) {
    node *temp;
    while (head != NULL) {
        temp = head->next;
        delete head;
        head = temp;
    }
}
bool Search(node*head, int number){
    node * temp = head;
    while(temp != NULL){
        if (temp->digit != number){
            temp = temp->next;
        }
        else if (temp->digit != number && temp->next == NULL){
            return true;
        }
        else if (temp->digit == number){
            return false;
        }
    }
    if (head == NULL || temp == NULL){
        return true;
    }
    else{
        return false;
    }
}
bool Unique(string guess){
    if (guess.length() == 3 && (isdigit(guess[0]) && isdigit(guess[1]) && isdigit(guess[2]))){
        if(stoi(guess) >= 012 && stoi(guess) <= 987){
            for (int i = 0; i < guess.length() - 1; i++){
                for (int j =  i + 1; j < guess.length();j++){
                    if (guess[i] == guess[j]){
                        return false;
                    }
                }
            }
            return true;
        }
        else
            return false;
    }
    else
        return false;
}
bool Found(node * Pos_head, node * Im_head){
    int Im_count = 0, Pos_count = 0;
    while(Im_head != NULL){
        Im_count++;
        Im_head = Im_head->next;
    }
    while(Pos_head != NULL){
        Pos_count++;
        Pos_head = Pos_head->next;
    }
    if (Pos_count == 1 && Im_count == 9){
        return false;
    }
    return true;
}
void SecretRevealed(node * Pos_head, node * Im_head, int & Pos, int & Im){
    while(Im_head != NULL){
        Im++;
        Im_head = Im_head->next;
    }
    while(Pos_head != NULL){
        Pos++;
        Pos_head = Pos_head->next;
        break;
    }
}
int main(){
    string guess;
    int gameID;
    cout << "Please enter a game ID." << endl;
    cin >> gameID;
    node *impossible[3];
    node *possible[3];
    for (int i = 0; i < 3; i++){
        possible[i] = NULL;
        impossible[i] = NULL;
    }
    int Pos_finish = 0, Im_finish = 0;
    bool check_1 = true, check_2 = true;
    string ask = "ask";
    while (check_1){
        while(check_2){
            if(ask == "ask"){
                cout << "Enter your guess." << endl;
                cin >> guess;
            }
            else{
                ask = "ask";
            }
            string value = get_the_feedback(guess, gameID);
            if(Unique(guess)){
                for (int i = 0; i < 3;i ++){ //i, will shape the index iteration of guess and value(feedback)
                    char letter = value[i]; //i is the index number of letter
                    int number = guess[i] - 48; //i is the index number of number
                    if (letter == 'R'){
                        //if letter is RED, then the number must be added every impossible slot
                        //and should be removed from every possible slot.
                        for (int j = 0; j < 3; j++){
                            if (Search(impossible[j], number) && Search(possible[j], number)) {
                                Add(impossible[j], number);
                                DeleteOneNode(possible[j], number );
                            }
                        }
                    }
                    else if (letter == 'Y'){
                        //if letter is YELLOW, then it should be added every slot
                        //except the slot that the index of the Y in the feedback string.
                        //number should not be added to the index with G code.
                        if (Search(impossible[i], number))
                            Add(impossible[i], number);

                        for (int j = 0; j < 3; j++) {
                            if (j != value.find('G') && j != i && Search(possible[j], number) && Search(impossible[j], number))
                                Add(possible[j], number);
                            else if(j != value.find('G') && !Search(impossible[j], number) && !Search(possible[j], number)){
                                DeleteOneNode(possible[j], number);
                            }
                        }
                    }

                    else if (letter == 'G'){
                        //1. if letter is G, then the number should be removed from every other possible slot
                        //2. it must be added to the same index number with the G in the feedback string
                        //3. impossible slot with the same index of G in feedback string must be
                        //filled with every other number from 0-9 except the number in the guess which is
                        //in the same index with G.
                        //4. it must be added to the same index in the impossible array.

                        if (Found(possible[i], impossible[i])){ //if the exact value is not found
                            //1.
                            for (int j = 0; j < 3; j++){
                                if (j != i){
                                    DeleteOneNode(possible[j], number);
                                } //if it is
                            }
                            //2.
                            DeleteList(possible[i]);
                            Add(possible[i], number);

                            //3.
                            DeleteList(impossible[i]);

                            //4. add number to every other impossible slot
                            for (int j = 0; j < 3; j++){
                                if (j != i && Search(impossible[j], number) && Search(possible[j], number))
                                    Add(impossible[j], number);
                            }

                            //{10} - G. add every number other than number to the ith slot
                            for (int j = 0; j < 10; j++){
                                if (j != number && Search(impossible[i], number))
                                    Add(impossible[i], j);
                            }
                        }
                    }
                }
                bool secret = false; //if all values are found then the secret is true, if not found then the secret is false
                if (value != "GGG") { //if not all values are found correctly
                    for (int j = 0; j < 3; j++) { //counting the numbers in possibles and impossibles
                        SecretRevealed(possible[j], impossible[j], Pos_finish, Im_finish);
                    }
                    //if Im_finish + Pos_finish = 30, then no missing. If sum is 29 there is just one missing
                    int missing = 0;
                    if (Im_finish == 27 && Pos_finish == 2) { //there is a missing number
                        //then we try to find the missing one
                        cout << "Linked lists:" << endl;
                        for (int j = 0; j < 3; j++){ //printing the values of slots
                            PrintValues(possible[j], impossible[j], j + 1);
                        }

                        for (int k = 0; k < 3; k++){
                            for (int j = 0; j < 10; j++) { //finding the missing one
                                if (Search(impossible[k], j) && possible[k] == NULL) { //finding the missing one
                                    Pos_finish++;
                                    missing = j;
                                    secret = true; //secret number is found and all values are certain
                                }
                            }
                        }
                    }
                    else if (Im_finish == 27 && Pos_finish == 3){ //no missing values
                        cout << "Linked lists:" << endl;
                        for (int j = 0; j < 3; j++){ //printing the values of slots
                            PrintValues(possible[j], impossible[j], j + 1);
                        }
                        secret = true;
                    }
                    if (secret == false) {
                        cout << "Linked lists:" << endl;
                        for (int j = 0; j < 3; j++) { //printing the values of slots
                            PrintValues(possible[j], impossible[j], j + 1);
                        }
                        Im_finish = 0;
                        Pos_finish = 0; //resetting the Pos_finish and Im_finish
                    } else {
                        string secretNumber = "";
                        for (int j = 0; j < 3; j++) { //finding the secret numbers
                            if (possible[j] != NULL){ //if we are not dealing with the missing value
                                secretNumber += to_string(possible[j]->digit);
                            }
                            else { //if we are in the missing value then we add missing number
                                secretNumber += to_string(missing);
                            }
                        }

                        cout << "The secret number is: " << secretNumber << endl;
                        cout << "Congrats! Now, deleting the lists...";
                        for (int j = 0; j < 3; j++) { //deleting the lists
                            DeleteList(impossible[j]);
                            DeleteList(possible[j]);
                        }
                        //quitting from the loop
                        check_2 = false;
                        check_1 = false;
                    }
                }
                else{
                    //if all the values are found for secret number then the missing numbers are added to impossibles
                    for (int j = 0; j < 3; j++){
                        for (int k = 0; k < 10; k++){
                            if (Search(impossible[j], k) && Search(possible[j], k))
                                Add(impossible[j], k);
                        }
                    }
                    cout << "Linked lists:" << endl;
                    for (int j = 0; j < 3; j++) { //printing the values of the slots
                        PrintValues(possible[j], impossible[j], j + 1);
                    }
                    string secretNumber = "";
                    for (int j = 0; j < 3; j++){ //taking all the correct possible values into secretNumber
                        secretNumber += to_string(possible[j]->digit);
                    }
                    cout << "The secret number is: " << secretNumber;
                    cout << endl << "Congrats! Now, deleting the lists...";
                    for (int j = 0; j < 3; j++) { //deleting the list
                        DeleteList(impossible[j]);
                        DeleteList(possible[j]);
                    }
                    //to quit the while loops
                    check_2 = false;
                    check_1 = false;
                }
            }
            else{
                cout << "Invalid guess. Enter your guess." << endl;
                cin >> guess;
                ask = "do not ask";
            }
        }
    }
}