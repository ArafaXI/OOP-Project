#include "Library.h" // This class is responsible for managing the library and is the backbone of the project, it contains a dynamically allocated array to pointer classes of members and items

// Constructor
Library::Library() {
  memberList = new Member*[10];  // Initial capacity
  itemList = new Item*[10];      // Initial capacity
  memberSize = 0;
  itemSize = 0;
  memberCapacity = 10;
  itemCapacity = 10;
}

// Destructor
Library::~Library() {
  for (int i = 0; i < memberSize; i++) {
    delete memberList[i];  // Delete each Member
  }
  for (int i = 0; i < itemSize; i++) {
    delete itemList[i];  // Delete each Item
  }
  delete[] memberList;  // Delete the member array
  delete[] itemList;    // Delete the item array
}

// Add a member
void Library::addMember(Member* member) {
  if (member == nullptr) {
    std::cout << "Cannot add a null member!"
              << std::endl;  // if program tries to input nothing
    return;
  }
  if (memberSize >= memberCapacity) {
    // Resize the array if needed
    memberCapacity *= 2;
    Member** newMemberList = new Member*[memberCapacity];
    for (int i = 0; i < memberSize; i++) {
      newMemberList[i] = memberList[i];
    }
    delete[] memberList;         // Free the old array
    memberList = newMemberList;  // Point to the new array
  }
  memberList[memberSize++] = member;  // Add the member
}

// remove a member by index
void Library::removeMember(int index) {
  if (index < 0 || index >= memberSize) {
    std::cout << "Invalid index!" << std::endl;
    return;
  }

  delete memberList[index];  // Delete the member

  // Shift remaining members down
  for (int j = index; j < memberSize - 1; j++) {
    memberList[j] = memberList[j + 1];
  }

  memberSize--;  // Decrease size
}

// Add an item
void Library::addItem(Item* item) {
  if (item == nullptr) {
    std::cout << "Cannot add a null item!" << std::endl;
    return;
  }
  if (itemSize >= itemCapacity) {
    // Resize the array if needed
    itemCapacity *= 2;
    Item** newItemList = new Item*[itemCapacity];
    for (int i = 0; i < itemSize; i++) {
      newItemList[i] = itemList[i];
    }
    delete[] itemList;       // Free the old array
    itemList = newItemList;  // Point to the new array
  }
  itemList[itemSize++] = item;  // Add the item
}

// Remove an item from the list
void Library::removeItem(int index) {
  if (index < 0 || index >= itemSize) {
    std::cout << "Invalid index!" << std::endl;
    return;
  }
  delete itemList[index];  // Delete the item
  for (int j = index; j < itemSize - 1; j++) {
    itemList[j] = itemList[j + 1];  // Shift remaining items down
  }
  itemSize--;  // Decrease size
}

// Display items
void Library::displayItems() {
  std::cout << "Items in library:" << std::endl;

  // Print no items if there are no items
  if (itemSize == 0) {
    std::cout << "You have not yet added any items!" << std::endl;
  }

  for (int i = 0; i < itemSize; i++) {
    std::cout << i + 1 << ". " << itemList[i]->getTitle() << " by "
              << itemList[i]->getAuthor() << std::endl;
  }
}

// Display members
void Library::displayMembers() {
  std::cout << "Members in library:" << std::endl;

  // Print no members if there are no members
  if (memberSize == 0) {
    std::cout << "You have not yet added any members!" << std::endl;
  }

  for (int i = 0; i < memberSize; i++) {
    std::cout << i + 1 << ". " << memberList[i]->getName()
              << " (ID: " << memberList[i]->getID() << ")" << std::endl;
  }
}

// Assigns an item to a member
void Library::borrowItem(int memberIndex, int itemIndex) {
  if (itemIndex < 0 || itemIndex >= itemSize || memberIndex < 0 ||
      memberIndex >= memberSize) {
    std::cout << "Invalid member or item index." << std::endl;
    return;
  }
  itemList[itemIndex]->Borrow(true);
  std::cout << "Item borrowed successfully." << std::endl;
}

// Removes an item from a member
void Library::returnItem(int memberIndex, int itemIndex) {
  if (itemIndex < 0 || itemIndex >= itemSize || memberIndex < 0 ||
      memberIndex >= memberSize) {
    std::cout << "Invalid member or item index." << std::endl;
    return;
  }
  itemList[itemIndex]->Borrow(false);
  std::cout << "Item returned successfully." << std::endl;
}

// getter for itemlist
Item** Library::getItemList() { return itemList; }

// Getter for item size
int Library::getItemSize() { return itemSize; }

// getter for member size
int Library::getMemberSize() { return memberSize; }

// getters for member list
Member** Library::getMemberList() { return memberList; }

// Saving to file
void Library::saveToFile(const std::string& filename) {
  std::ofstream outFile(filename);
  if (outFile.is_open()) {
    // Save members
    outFile << memberSize << "\n";  // Save the number of members
    for (int i = 0; i < memberSize; i++) {
      outFile << memberList[i]->getID() << "|" << memberList[i]->getName()
              << "\n";  // Save each member
    }

    // Save items
    outFile << itemSize << "\n";  // Save the number of items
    for (int i = 0; i < itemSize; i++) {
      outFile << itemList[i]->save() << "\n";  // Save each item
    }

    outFile.close();
    std::cout << "Library saved successfully." << std::endl;
  } else {
    std::cerr << "Unable to open file for writing." << std::endl;
  }
}

 // Loading from file
 void Library::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "Unable to open file for reading." << std::endl;
        return;
    }

    // Load members
    int loadedMemberSize;
    inFile >> loadedMemberSize;
    inFile.ignore(); // Ignore the newline after the number

    for (int i = 0; i < loadedMemberSize; i++) {
        std::string memberData;
        std::getline(inFile, memberData);
        std::istringstream ss(memberData);

        int id;
        std::string name;

        ss >> id;                      // Extract the ID (integer)
        ss.ignore(1);                   // Ignore the '|' delimiter
        std::getline(ss, name);         // Extract the name (string)

        Member* member = new Member(name, id); // Create new member with name and ID
        addMember(member);
    }

    // Load items (as in your current code)
    int loadedItemSize;
    inFile >> loadedItemSize;
    inFile.ignore(); // Ignore the newline after the number

    for (int i = 0; i < loadedItemSize; i++) {
        std::string itemData;
        std::getline(inFile, itemData);
        
        std::istringstream ss(itemData);
        std::string type;
        std::getline(ss, type, '|'); 

        if (type == "Book") {
            Book* book = new Book();
            book->load(itemData);
            addItem(book);
        } else if (type == "Ebook") {
            Ebook* ebook = new Ebook();
            ebook->load(itemData);
            addItem(ebook);
        } else if (type == "Magazine") {
            Magazine* magazine = new Magazine();
            magazine->load(itemData);
            addItem(magazine);
        }
    }

    inFile.close();
    std::cout << "Library loaded successfully." << std::endl;
}
