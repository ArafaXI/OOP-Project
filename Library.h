#ifndef LIBRARY_H
#define LIBRARY_H

#include "Member.h"
#include "Item.h"

class Library {
private:
    Member** memberList;   
    Item** itemList;  
    int memberSize;
    int itemSize;

public:
    Library();
    ~Library();

    void addMember(Member* member); // add members/items
    void addItem(Item* item);
    void removeItem(int index); // remove members/items
    void removeMember(int index);
    void displayItems(); // display all the items in the libary 
    void displayMembers();
    void borrowItem(int memberIndex, int itemIndex);
    void returnItem(int memberIndex, int itemIndex);
};

#endif