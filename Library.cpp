#include "Library.h"
#include "Book.h"
#include "Magazine.h"

// Constructor
Library::Library() {
    memberList = new Member*[10];
    itemList = new Item*[10];
    memberSize = 0;
    itemSize = 0;
}

// Destructor
Library::~Library() {
    for (int i = 0; i < memberSize; i++) {
        delete memberList[i]; // Delete each Member
    }
    for (int i = 0; i < itemSize; i++) {
        delete itemList[i]; // Delete each Item
    }
    delete[] memberList; // Delete the array
    delete[] itemList;   // Delete the array
}

// Add a member
void Library::addMember(Member* member) {
    if (memberSize < 10) { // Assuming fixed size for simplicity
        memberList[memberSize++] = member; // Add member to list
    } else {
        std::cout << "Member list is full!" << std::endl;
    }
}

// Add an item
void Library::addItem(Item* item) {
    if (itemSize < 10) { // Assuming fixed size for simplicity
        itemList[itemSize++] = item; // Add item to list
    } else {
        std::cout << "Item list is full!" << std::endl;
    }
}

// Remove an item
void Library::removeItem(int index) {
    if (index < 0 || index >= itemSize) {
        std::cout << "Invalid index!" << std::endl;
        return;
    }
    delete itemList[index]; // Delete the item
    for (int i = index; i < itemSize - 1; i++) {
        itemList[i] = itemList[i + 1]; // Shift items left
    }
    itemSize--; // Reduce size
}

// Remove a member
void Library::removeMember(int index) {
    if (index < 0 || index >= memberSize) {
        std::cout << "Invalid index!" << std::endl;
        return;
    }
    delete memberList[index]; // Delete the member
    for (int i = index; i < memberSize - 1; i++) {
        memberList[i] = memberList[i + 1]; // Shift members left
    }
    memberSize--; // Reduce size
}


// Display items
void Library::displayItems() {
    std::cout << "Items in library:" << std::endl;
    for (int i = 0; i < itemSize; i++) {
        std::cout << i + 1 << ". " << itemList[i]->getTitle() << " by "
                  << itemList[i]->getAuthor() << std::endl;
    }
}

// Display members
void Library::displayMembers() {
    std::cout << "Members in library:" << std::endl;
    for (int i = 0; i < memberSize; i++) {
        std::cout << i + 1 << ". " << memberList[i]->getName() << " (ID: "
                  << memberList[i]->getID() << ")" << std::endl;
    }
}

void Library::borrowItem(int memberIndex, int itemIndex) {
    if (itemIndex < 0 || itemIndex >= itemSize || memberIndex < 0 || memberIndex >= memberSize) {
        std::cout << "Invalid member or item index." << std::endl;
        return;
    }
    itemList[itemIndex]->Borrow(true);
    std::cout << "Item borrowed successfully." << std::endl;
}

void Library::returnItem(int memberIndex, int itemIndex) {
    if (itemIndex < 0 || itemIndex >= itemSize || memberIndex < 0 || memberIndex >= memberSize) {
        std::cout << "Invalid member or item index." << std::endl;
        return;
    }
    itemList[itemIndex]->Borrow(false);
    std::cout << "Item returned successfully." << std::endl;
}