#include "Member.h"

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
Item* Member::getBorrowedItems() {
  return borrowedItems;  // Consider returning a pointer to the dynamic array
}

// Setter for name
void Member::setName(std::string newName) { name = newName; }

// Setter for ID
void Member::setID(int newID) { ID = newID; }

void Item::borrowItem(Item* item) {
  // Create a new temporary array with +1 size and copy everything from the old
  // borroweditems array to the new
  Item** temp_array = new Item*[borrowedSize + 1];

  for (int i = 0; i < borrowedSize; i++) {
    temp_array[i] = borrowedItems[i];
  }

  temp_array[borrowedSize] = item;  // Add the latest item
  borrowedSize++;                   // Increment

  delete[] borrowedItems;
  borrowedItems = temp_array;
}

void Item::returnItem(Item* item) {
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

void Item::displayBorrowedItems() {
  if (borrowedSize == 0) {
    std::cout << "This member does not currently have any borrowed Items"
              << std::endl;
  } else {
    std::cout << "Here is a list of this member's Items: " << std::endl;

    for (int i = 0; i < borrowedSize; i++) {
      std::cout << borrowedItems[i]->getName() << " by "
                << borrowedItems[i]->getAuthor() << std::endl;
    }
  }
}

Member::~Member() { delete[] borrowedItems; }