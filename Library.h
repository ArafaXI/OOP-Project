#ifndef LIBRARY_H
#define LIBRARY_H

#include <fstream>  // To allow file saving and loading
#include <sstream>  // To work with streams (e.g., for parsing data)
#include <vector>

#include "Book.h"
#include "Ebook.h"
#include "Item.h"
#include "Magazine.h"
#include "Member.h"

// The Library class is responsible for managing members and items (like books,
// magazines, and ebooks). It keeps track of these in dynamically allocated
// arrays and provides methods for borrowing, returning, displaying, saving, and
// loading library data.

class Library {
 private:
  Member**
      memberList;   // Dynamically allocated array of pointers to Member objects
  Item** itemList;  // Dynamically allocated array of pointers to Item objects
  int memberSize;   // Current number of members in the library
  int itemSize;     // Current number of items in the library
  int memberCapacity = 10;  // Initial capacity for members (how many members
                            // the array can hold before resizing)
  int itemCapacity = 10;    // Initial capacity for items (how many items the
                            // array can hold before resizing)

 public:
  // Constructor: Initializes the library with an empty member list and item
  // list.
  Library();

  // Destructor: Cleans up dynamically allocated memory (deletes the members and
  // items from memory).
  ~Library();

  // Adds a new member to the library. If the member list is full, it
  // automatically resizes.
  void addMember(Member* member);

  // Adds a new item (like a book, magazine, or ebook) to the library.
  // Automatically resizes if full.
  void addItem(Item* item);

  // Removes an item from the library by its index. Also deletes the item from
  // memory.
  void removeItem(int index);

  // Removes a member from the library by its index and deletes the member from
  // memory.
  void removeMember(int index);

  // Displays all the items in the library, listing their titles and authors.
  void displayItems();

  // Displays all the members in the library, showing their names and IDs.
  void displayMembers();

  // Assigns an item to a member (i.e., marks an item as borrowed by a specific
  // member).
  void borrowItem(int memberIndex, int itemIndex);

  // Returns an item that was borrowed, making it available again.
  void returnItem(int memberIndex, int itemIndex);

  // Returns the list of all items in the library (as an array of pointers).
  Item** getItemList();

  // Returns the list of all members in the library (as an array of pointers).
  Member** getMemberList();

  // Returns the number of items currently in the library.
  int getItemSize();

  // Returns the number of members currently in the library.
  int getMemberSize();

  // Saves all library data (members and items) to a file so that it can be
  // restored later.
  void saveToFile(const std::string& filename);

  // Loads library data (members and items) from a file.
  void loadFromFile(const std::string& filename);

  // Not implemented yet: A method that would return a list of items in a vector
  // format.
  std::vector<Item*> getItems() const;  // Declaration
};

#endif
