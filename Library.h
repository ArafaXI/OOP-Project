#ifndef LIBRARY_H
#define LIBRARY_H

#include "Member.h"
#include "Item.h"
#include "Book.h"
#include "Magazine.h"
#include "Ebook.h"
#include <vector>
#include <fstream> // For saving and loading
#include <sstream>

class Library {
private: // Set library attributes
    Member** memberList;   
    Item** itemList;  
    int memberSize;
    int itemSize;
    int memberCapacity = 10;
    int itemCapacity = 10;

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
    Item** getItemList();
    Member** getMemberList();

    int getItemSize();  // New function to get the number of items
    int getMemberSize();

    // Saving and Loading the library elements
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string&filename);


    std::vector<Item*> getItems() const; // Declaration
};

#endif

