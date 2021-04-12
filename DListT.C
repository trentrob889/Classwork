/*
    Homework 4: Spinning in Circles
    Programmer: Trenton Roberts
    Class: CSCI330.001, Fall 2020
    Short Description: This program tests a song lists
    basic function such as changing songs, copying song lists,
    inserting songs, and deleting songs using a doubly linked list.

    Narrative: This program simulates a playlist where the user can 
    navigate around the list that loops around back to the beginning.
    The user can move left, right, or to the first song in a playlist.
    The user can also delete and insert songs to playlists, as well
    as copy playlists using either the overloaded assignment operator or
    the copy constructor. 
*/

#include <iostream>
#include "DListT.h"

using namespace std;

struct DListNodeT {
    string songTitle;
    DListNodeT * left;
    DListNodeT * right;
};

/*
This struct contains a pointer to the left
and right of the current node and a string
containing a song title.
*/



size_t DListT::FindCurrent(const DListT & playlist){
    size_t listSize = playlist.Size();
    size_t pos = 0;
    DListNodeT * temp = nullptr;
	
    temp = playlist.head;
    for(size_t i = 0; i < listSize; i++){
    	if(playlist.current == temp) {
	    pos = i;
	}
	temp = temp->right;	
    }
    return pos;
}

DListT::DListT() {
    head = nullptr;
    current = nullptr;
    nodeCount = 0;
    return;
}


//This constructor sets the classes pointers
//to null and the nodeCount to 0.


DListT::DListT(const DListT & src){
    size_t sourceSize = src.Size();
    size_t reducedSize = 0;
    size_t currentPos = 0;
    DListNodeT * temp = nullptr;
    DListNodeT * newNode = nullptr;
    DListNodeT * secondNode = nullptr;
    DListNodeT * nextNode = nullptr;
    DListNodeT * previous = nullptr;


    if(sourceSize != 0){
        //Set the heads pointers to itself and copy data
        newNode = new DListNodeT;
        newNode->right = newNode->left = newNode;
        newNode->songTitle = src.head->songTitle;
        head = newNode;
	current = head;

        if(sourceSize > 1){
            secondNode = new DListNodeT;
            head->right = head->left = secondNode;
            nextNode = src.head->right;
            secondNode->left = secondNode->right = head;
            secondNode->songTitle = nextNode->songTitle;
            previous = secondNode;
	    
            //set the second nodes pointers to the head and copy data
            if(sourceSize > 2) {
                reducedSize = sourceSize - 2;
                //If needed, copy the rest of the data and keep track of previous node
                for(size_t i=0; i<reducedSize; i++){
                   newNode = new DListNodeT;
                   previous->right = newNode;
                   newNode->left = previous;
                   nextNode = nextNode->right;
                   newNode->songTitle = nextNode->songTitle;
                   previous = newNode;
                }
                newNode->right = head;
                head->left = newNode;
            }
        }
	currentPos = FindCurrent(src);
	temp = src.head;
	for(size_t i = 0; i < currentPos; i++){
            temp = temp->right;
	}
        current = temp;
    } else {
        head = nullptr;
        current = nullptr;
    }
    nodeCount = sourceSize;
    return;
}

//This copy constuctor copies
//all the data from one object
//into another object.

DListT::~DListT(){
    size_t playlistSize = nodeCount;
    DListNodeT * temp = nullptr;

    current = head;

    for(size_t i=0; i<playlistSize; i++) {
    	temp = current;
	current = current->right;
	delete temp;
    }
   
    head = nullptr;
    current = nullptr;
    return;
}

/*
This destructor deletes all the dynamic data
in a doubly linked list and then sets the current
and head pointers to null.
*/


DListT & DListT::operator = (const DListT & rhs) {
    size_t playlistSize = rhs.Size();
    size_t reducedSize = 0;
    size_t currentPos = 0;
    DListNodeT * temp = nullptr;
   // DListNodeT * cur = nullptr;
	DListNodeT * tempDelete = nullptr;
    DListNodeT * newNode = nullptr;
    DListNodeT * secondNode = nullptr;
    DListNodeT * nextNode = nullptr;
    DListNodeT * previous = nullptr;

    
	if(this == & rhs){
		return * this;
	} else {
	
	    if(nodeCount > 0){
	        current = head;
	        for(size_t j = 0; j<nodeCount; j++){
	            tempDelete = current;
	       	    current = current->right;
		    delete tempDelete;		
	        }
	    }			
			
	    if(playlistSize == 0){
	        head = nullptr;
		current = nullptr;				
	    } else{
	        //Set the heads pointers to itself and copy data
                newNode = new DListNodeT;
	        newNode->right = newNode->left = newNode;
	        newNode->songTitle = rhs.head->songTitle;
	        head = newNode;

		if(playlistSize > 1){
	            secondNode = new DListNodeT;
		    head->right = head->left = secondNode;
	            nextNode = rhs.head->right;
		    secondNode->left = secondNode->right = head;
		    secondNode->songTitle = nextNode->songTitle;
		    previous = secondNode;
		//set the second nodes pointers to the head and copy data
	            if(playlistSize > 2) {
		        reducedSize = playlistSize - 2;
		//If needed, copy the rest of the data and keep track of previous node
			for(size_t i=0; i<reducedSize; i++){
		            newNode = new DListNodeT;
			    previous->right = newNode;
		            newNode->left = previous;
		            nextNode = nextNode->right;
		            newNode->songTitle = nextNode->songTitle;
		            previous = newNode;
			}
			newNode->right = head;
			head->left = newNode;
		     }
	        }
		currentPos = FindCurrent(rhs);
		temp = rhs.head;
		for(size_t i = 0; i < currentPos; i++){
	            temp = temp->right;
		}

		current = temp;
            }
	}
    nodeCount = playlistSize;
    return *this;
}

/*
This overloaded assignment operator
copies all the data from the object
on the right hand side of the equation
to the object on the left hand side.
*/

void DListT::Home() {
    if(nodeCount == 0){
        current = nullptr;
    } else {
        current = head;
    }
    return;
}

//This function moves the current pointer
//to the head if it exists, otherwise it sets
//current to null.


void DListT::Left() {
    if(nodeCount == 0){
        current = nullptr;
    } else {
        current = current->left;
    }
    return;
}

//This function sets the current pointer to
//the left node of the current position.
//If the list is empty, set the current to null.

void DListT::Right() {
    if(nodeCount == 0) {
        current = nullptr;
    } else {
        current = current->right;
    }
    return;
}

//Set the current pointer to the right node
//of the current position, if the list is empty
//set current to null.

string DListT::Data() const{
    if(current != nullptr) {
        return current->songTitle;
    } else {
        cout << "Error: Attempt to access Empty List.\n";
        return "NO DATA";
    }
}

//This function returns the current song in
//the playlist, unless it is empty then it
//returns an error and the "NO DATA" string.

size_t DListT::Size() const{
    return nodeCount;
}

//This function returns the nodeCount
//for a given playlist.

void DListT::Insert(string newData){
    DListNodeT * newNode = nullptr;
    bool currentHead = false;

    newNode = new DListNodeT;

    if(nodeCount == 0){
        head = newNode;
        current = head;
        newNode->right = newNode->left = head;
    } else if(nodeCount == 1) {
        newNode->right = newNode->left = head;
        head->right = head->left = newNode;
        current = head = newNode;
    } else {
        //to make sure the head stays as the current pointer
        if(current == head) {
            currentHead = true;
        }
        //adjust newNode and current
        newNode->right = current;
        newNode->left = current->left;
        current->left->right = newNode;
        current->left = newNode;
        current = newNode;

        if(currentHead) {
            head = current;
        }
    }
    newNode->songTitle = newData;
    nodeCount++;
    return;
}

/*
This function inserts a new node, or song, into
a playlist. The data is inserted either at
the head or before an element in the playlist
and the nodeCount is incremented.
*/

void DListT::InsertAfter(string newData){
    DListNodeT * newNode = nullptr;

    newNode = new DListNodeT;

    if(nodeCount == 0) {
        head = newNode;
        current = head;
        newNode->right = head;
        newNode->left = head;
    } else {
        if(nodeCount == 1) {
            newNode->right = head;
            newNode->left = head;
            head->right = newNode;
            head->left = newNode;
            current = newNode;
        } else {
            newNode->right = current->right;
            newNode->left = current;
            current->right->left = newNode;
            current->right = newNode;
            current = newNode;
        }
    }
    newNode->songTitle = newData;
    nodeCount++;
    return;
}

/*
This function inserts a song into
a playlist after the current song or
at the head if the playlist is empty.
*/

void DListT::Delete(){
    DListNodeT * temp = nullptr;
    DListNodeT * leftNode = nullptr;
    DListNodeT * rightNode = nullptr;

    if(nodeCount != 0) {
        if(nodeCount == 1) {
            temp = current;
            delete temp;
            current = nullptr;
            head = nullptr;
        } else if(current == head) {
            if(nodeCount == 2) {
                rightNode = head->right;
                rightNode->left = head->left;
                rightNode->right = head->right;
            } else {
                rightNode = head->right;
                rightNode->left = head->left;
                leftNode = head->left;
                leftNode->right = rightNode;
            }
            temp = head;
            delete temp;
            head = current = rightNode;
        } else {
            if(nodeCount == 2) {
                temp = head->right;
                head->left = head->right = head;
                delete temp;
                current = head;
            } else {
                temp = current;
                leftNode = current->left;
                rightNode = current->right;
                //correct left and right nodes to connect
                leftNode->right = current->right;
                rightNode->left = current->left;
                current = leftNode;
                delete temp;
            }
        }
        nodeCount--;
    } else {
        cout << "Error: Attempt to delete in an Empty List.\n";
    }
    return;
}

/*
This function deletes a song from a
playlist as long as the playlist contains
at least one song. Else, if the playlist is
empty an error is output to the user.
*/


