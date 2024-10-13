#include "Library.h"

// The Library class is responsible for managing members and items.
// It uses dynamically allocated arrays to store pointers to Member and Item
// objects.

// Constructor
Library::Library() {
  // Allocate initial capacity for members and items
  memberList = new Member*[10];  // Initially hold 10 members
  itemList = new Item*[10];      // Initially hold 10 items
  memberSize = 0;                // Number of members starts at 0
  itemSize = 0;                  // Number of items starts at 0
  memberCapacity = 10;           // Initial capacity for members
  itemCapacity = 10;             // Initial capacity for items
}

// Destructor
Library::~Library() {
  // Free memory allocated for members
  for (int i = 0; i < memberSize; i++) {
    delete memberList[i];  // Delete each member in the list
  }
  // Free memory allocated for items
  for (int i = 0; i < itemSize; i++) {
    delete itemList[i];  // Delete each item in the list
  }
  // Delete the arrays themselves
  delete[] memberList;  // Delete the array holding member pointers
  delete[] itemList;    // Delete the array holding item pointers
}

// Add a new member to the library
void Library::addMember(Member* member) {
  // Check if the member pointer is null
  if (member == nullptr) {
    std::cout << "Cannot add a null member!" << std::endl;
    return;
  }
  // If the current array is full, double the capacity
  if (memberSize >= memberCapacity) {
    memberCapacity *= 2;  // Double the capacity
    Member** newMemberList = new Member*[memberCapacity];
    // Copy existing members to the new array
    for (int i = 0; i < memberSize; i++) {
      newMemberList[i] = memberList[i];
    }
    delete[] memberList;         // Free the old array
    memberList = newMemberList;  // Point to the new, larger array
  }
  // Add the member to the array and increment memberSize
  memberList[memberSize++] = member;
}

// Remove a member by index
void Library::removeMember(int index) {
  // Validate the index
  if (index < 0 || index >= memberSize) {
    std::cout << "Invalid index!" << std::endl;
    return;
  }

  delete memberList[index];  // Delete the member at the given index

  // Shift the remaining members down to fill the gap
  for (int j = index; j < memberSize - 1; j++) {
    memberList[j] = memberList[j + 1];
  }

  memberSize--;  // Reduce the size of the member list
}

// Add a new item to the library
void Library::addItem(Item* item) {
  // Check if the item pointer is null
  if (item == nullptr) {
    std::cout << "Cannot add a null item!" << std::endl;
    return;
  }
  // If the current array is full, double the capacity
  if (itemSize >= itemCapacity) {
    itemCapacity *= 2;  // Double the capacity
    Item** newItemList = new Item*[itemCapacity];
    // Copy existing items to the new array
    for (int i = 0; i < itemSize; i++) {
      newItemList[i] = itemList[i];
    }
    delete[] itemList;       // Free the old array
    itemList = newItemList;  // Point to the new, larger array
  }
  // Add the item to the array and increment itemSize
  itemList[itemSize++] = item;
}

// Remove an item from the library by index
void Library::removeItem(int index) {
  // Validate the index
  if (index < 0 || index >= itemSize) {
    std::cout << "Invalid index!" << std::endl;
    return;
  }
  delete itemList[index];  // Delete the item at the given index

  // Shift the remaining items down to fill the gap
  for (int j = index; j < itemSize - 1; j++) {
    itemList[j] = itemList[j + 1];
  }

  itemSize--;  // Reduce the size of the item list
}

// Display all items in the library
void Library::displayItems() {
  std::cout << "Items in library:" << std::endl;

  // If there are no items, print a message
  if (itemSize == 0) {
    std::cout << "You have not yet added any items!" << std::endl;
    return;
  }

  // Loop through each item and display its title and author
  for (int i = 0; i < itemSize; i++) {
    std::cout << i + 1 << ". " << itemList[i]->getTitle() << " by "
              << itemList[i]->getAuthor() << std::endl;
  }
}

// Display all members in the library
void Library::displayMembers() {
  std::cout << "Members in library:" << std::endl;

  // If there are no members, print a message
  if (memberSize == 0) {
    std::cout << "You have not yet added any members!" << std::endl;
    return;
  }

  // Loop through each member and display their name and ID
  for (int i = 0; i < memberSize; i++) {
    std::cout << i + 1 << ". " << memberList[i]->getName()
              << " (ID: " << memberList[i]->getID() << ")" << std::endl;
  }
}

// Assign an item to a member (borrow)
void Library::borrowItem(int memberIndex, int itemIndex) {
  // Validate member and item indices
  if (itemIndex < 0 || itemIndex >= itemSize || memberIndex < 0 ||
      memberIndex >= memberSize) {
    std::cout << "Invalid member or item index." << std::endl;
    return;
  }
  // Mark the item as borrowed
  itemList[itemIndex]->Borrow(true);
  std::cout << "Item borrowed successfully." << std::endl;
}

// Return an item from a member (return)
void Library::returnItem(int memberIndex, int itemIndex) {
  // Validate member and item indices
  if (itemIndex < 0 || itemIndex >= itemSize || memberIndex < 0 ||
      memberIndex >= memberSize) {
    std::cout << "Invalid member or item index." << std::endl;
    return;
  }
  // Mark the item as returned
  itemList[itemIndex]->Borrow(false);
  std::cout << "Item returned successfully." << std::endl;
}

// Getter for the item list
Item** Library::getItemList() { return itemList; }

// Getter for the number of items in the library
int Library::getItemSize() { return itemSize; }

// Getter for the number of members in the library
int Library::getMemberSize() { return memberSize; }

// Getter for the member list
Member** Library::getMemberList() { return memberList; }

// Save the library's data to a file
void Library::saveToFile(const std::string& filename) {
  std::ofstream outFile(filename);  // Open the file for writing
  if (outFile.is_open()) {
    // Save the number of members
    outFile << memberSize << "\n";
    // Save each member's ID and name
    for (int i = 0; i < memberSize; i++) {
      outFile << memberList[i]->getID() << "|" << memberList[i]->getName()
              << "\n";
    }

    // Save the number of items
    outFile << itemSize << "\n";
    // Save each item using its specific save method
    for (int i = 0; i < itemSize; i++) {
      outFile << itemList[i]->save() << "\n";
    }

    outFile.close();
    std::cout << "Library saved successfully." << std::endl;
  } else {
    std::cerr << "Unable to open file for writing." << std::endl;
  }
}

// Load the library's data from a file
void Library::loadFromFile(const std::string& filename) {
  std::ifstream inFile(filename);  // Open the file for reading
  if (!inFile.is_open()) {
    std::cerr << "Unable to open file for reading." << std::endl;
    return;
  }

  // Load members
  int loadedMemberSize;
  inFile >> loadedMemberSize;
  inFile.ignore();  // Ignore the newline after the number of members

  for (int i = 0; i < loadedMemberSize; i++) {
    std::string memberData;
    std::getline(inFile, memberData);
    std::istringstream ss(memberData);

    int id;
    std::string name;

    ss >> id;                // Extract the ID
    ss.ignore(1);            // Ignore the '|' delimiter
    std::getline(ss, name);  // Extract the name

    // Create a new member and add to the library
    Member* member = new Member(name, id);
    addMember(member);
  }

  // Load items
  int loadedItemSize;
  inFile >> loadedItemSize;
  inFile.ignore();  // Ignore the newline after the number of items

  for (int i = 0; i < loadedItemSize; i++) {
    std::string itemData;
    std::getline(inFile, itemData);

    std::istringstream ss(itemData);
    std::string type;
    std::getline(ss, type, '|');  // Get the item type

    if (type == "Book") {
      Book* book = new Book();
      book->load(itemData);  // Load book-specific data
      addItem(book);
    } else if (type == "Ebook") {
      Ebook* ebook = new Ebook();
      ebook->load(itemData);  // Load ebook-specific data
      addItem(ebook);
    } else if (type == "Magazine") {
      Magazine* magazine = new Magazine();
      magazine->load(itemData);  // Load magazine-specific data
      addItem(magazine);
    }
  }

  inFile.close();
  std::cout << "Library loaded successfully." << std::endl;
}
