#include "Member.h"

// Default constructor: initializes a new member with no name, ID, or borrowed
// items
Member::Member() {
  this->name = "";
  this->ID = 0;
  this->borrowedSize = 0;
  this->borrowedItems = nullptr;  // No borrowed items yet
}

// Parameterized constructor: sets member's name and ID
Member::Member(std::string name, int ID) {
  this->name = name;
  this->ID = ID;
  this->borrowedSize = 0;
  this->borrowedItems = nullptr;  // No borrowed items yet
}

// Getter for member's name
std::string Member::getName() { return name; }

// Getter for member's ID
int Member::getID() { return ID; }

// Getter for the number of borrowed items
int Member::getBorrowedSize() { return borrowedSize; }

// Getter for the list of borrowed items (returns an array of pointers to items)
Item** Member::getBorrowedItems() { return borrowedItems; }

// Setter for member's name
void Member::setName(std::string newName) { name = newName; }

// Setter for member's ID
void Member::setID(int newID) { ID = newID; }

// Adds an item to the member's borrowed list
void Member::borrowItem(Item* item) {
  // Create a new array with extra space for the new item
  Item** temp_array = new Item*[borrowedSize + 1];

  // Copy existing items to the new array
  for (int i = 0; i < borrowedSize; i++) {
    temp_array[i] = borrowedItems[i];
  }

  // Add the new item at the end of the array
  temp_array[borrowedSize] = item;
  borrowedSize++;  // Increase the borrowed item count

  // Clean up the old array and assign the new one
  delete[] borrowedItems;
  borrowedItems = temp_array;
}

// Removes a specific item from the member's borrowed list
bool Member::returnItem(Item* item) {
  if (item == nullptr) {
    return false;  // Invalid item
  }

  // Find the item to be removed
  int indexToRemove = -1;
  for (int i = 0; i < borrowedSize; i++) {
    if (borrowedItems[i] == item) {
      indexToRemove = i;
      break;
    }
  }

  // If the item was not found, return false
  if (indexToRemove == -1) {
    return false;
  }

  // Create a new array with space for one fewer item
  Item** temp_array = new Item*[borrowedSize - 1];

  // Copy everything except the removed item
  for (int i = 0, j = 0; i < borrowedSize; i++) {
    if (i != indexToRemove) {
      temp_array[j++] = borrowedItems[i];
    }
  }

  // Decrease the count of borrowed items
  borrowedSize--;

  // Clean up the old array and assign the new one
  delete[] borrowedItems;
  borrowedItems = temp_array;

  return true;  // Item successfully returned
}

// Displays all borrowed items and allows the user to view details
void Member::displayBorrowedItems() {
  if (borrowedSize == 0) {
    std::cout << "This member does not currently have any borrowed items."
              << std::endl;
  } else {
    std::cout << "Here is a list of this member's items: " << std::endl;

    // Display each borrowed item
    for (int i = 0; i < borrowedSize; i++) {
      std::cout << i + 1 << ". " << borrowedItems[i]->getTitle() << " by "
                << borrowedItems[i]->getAuthor() << std::endl;
    }

    int choice;
    std::cout << "If you would like to view the details of a specific item, "
                 "enter the number, "
              << "else enter 0 if you would like to exit: ";
    std::cin >> choice;

    // Show details for the selected item
    if (choice > 0 && choice <= borrowedSize) {
      borrowedItems[choice - 1]->displayInfo();
    } else if (choice != 0) {
      std::cout << "Invalid choice. Exiting." << std::endl;
    }
  }
}

// Destructor: cleans up memory used by the borrowedItems array
Member::~Member() { delete[] borrowedItems; }
