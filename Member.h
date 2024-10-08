#ifndef MEMBER_H
#define MEMBER_H

#include "Item.h"
#include "Ebook.h"
#include "Book.h"
#include "Magazine.h"

class Member {
 private:
    std::string name;
    int ID;
    int borrowedSize; // Integer to keep track of how many items the Member has borrowed
    Item** borrowedItems; // Dynamic array of pointers to Items

 public:
    // Constructers
    Member();
    Member(std::string name, int ID);

    // Getters
    std::string getName();
    int getID();
    int getBorrowedSize();
    Item** getBorrowedItems(); 

    // Setters
    void setName(std::string newName);
    void setID(int newID);
    void setBorrowedSize(int newSize);

    // Unique functions
    void borrowItem(Item* item); // Adds an Item to the member's collection of items.
    bool returnItem(Item* item); // Removes an Item from the member's borrowed list
    void displayBorrowedItems(); // Prints out the whole collection of Items that the user currently has, including their Title and author

    // Destructors
    ~Member();
};

#endif