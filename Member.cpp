#include "Member.h"

// Constructors
Member::Member() {
    this->name = "";
    this->ID = 0;
    this->borrowedSize = 0;
    this->borrowedItems = nullptr;
}

Member::Member(std::string name, int ID) {
    this->name = name;
    this->ID = ID;
    this->borrowedSize = 0;
    this->borrowedItems = nullptr;
}

// Getter for name
std::string Member::getName() { return name; }

// Getter for ID
int Member::getID() { return ID; }

// Getter for borrowedSize
int Member::getBorrowedSize() { return borrowedSize; }

// Getter for borrowedItems
Item** Member::getBorrowedItems() {
    return borrowedItems;  // Return the dynamic array
}

// Setter for name
void Member::setName(std::string newName) { name = newName; }

// Setter for ID
void Member::setID(int newID) { ID = newID; }

// Borrow item
void Member::borrowItem(Item* item) {
    // Create a new temporary array with +1 size and copy everything from the old borrowedItems array to the new
    Item** temp_array = new Item*[borrowedSize + 1];

    for (int i = 0; i < borrowedSize; i++) {
        temp_array[i] = borrowedItems[i];
    }

    temp_array[borrowedSize] = item;  // Add the latest item
    borrowedSize++;                    // Increment

    delete[] borrowedItems;
    borrowedItems = temp_array;
}

// Return item
void Member::returnItem(Item* item) {
    if (item == nullptr) {
        return;  // Handle the case of a null pointer if necessary
    }

    // Find the index of the item to be removed
    int indexToRemove = -1;
    for (int i = 0; i < borrowedSize; i++) {
        if (borrowedItems[i] == item) {
            indexToRemove = i;
            break;
        }
    }

    // If the item was not found, do nothing
    if (indexToRemove == -1) {
        return;
    }

    // Create a new temporary array with -1 size
    Item** temp_array = new Item*[borrowedSize - 1];

    // Copy items from old array to new one, skipping the removed item
    for (int i = 0, j = 0; i < borrowedSize; i++) {
        if (i != indexToRemove) {
            temp_array[j++] = borrowedItems[i];
        }
    }

    // Update borrowedSize
    borrowedSize--;

    // Delete the old array
    delete[] borrowedItems;

    // Assign the new array to borrowedItems
    borrowedItems = temp_array;
}

// Display borrowed items and prompt for details
void Member::displayBorrowedItems() {
    if (borrowedSize == 0) {
        std::cout << "This member does not currently have any borrowed items." << std::endl;
    } else {
        std::cout << "Here is a list of this member's items: " << std::endl;

        for (int i = 0; i < borrowedSize; i++) {
            std::cout << i + 1 << ". " << borrowedItems[i]->getTitle() << " by "
                      << borrowedItems[i]->getAuthor() << std::endl;
        }

        int choice;
        std::cout << "If you would like to view the details of a specific item, "
                     "enter the number, "
                  << "else enter 0 if you would like to exit: ";
        std::cin >> choice;

        if (choice > 0 && choice <= borrowedSize) {
            // Show details for the chosen item
            borrowedItems[choice - 1]->displayInfo(); 
        } else if (choice != 0) {
            std::cout << "Invalid choice. Exiting." << std::endl;
        }
    }
}

// Destructor
Member::~Member() { delete[] borrowedItems; }