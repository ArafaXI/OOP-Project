#ifndef MEMBER_H
#define MEMBER_H

#include "Book.h"      // Include the Book class
#include "Ebook.h"     // Include the Ebook class
#include "Item.h"      // Include the Item class
#include "Magazine.h"  // Include the Magazine class

class Member {
 private:
  std::string name;      // Member's name
  int ID;                // Unique identifier for the member
  int borrowedSize;      // Number of items currently borrowed
  Item** borrowedItems;  // Dynamic array of pointers to borrowed items

 public:
  // Constructors
  Member();                          // Default constructor
  Member(std::string name, int ID);  // Constructor with parameters

  // Getters
  std::string getName();      // Returns the member's name
  int getID();                // Returns the member's ID
  int getBorrowedSize();      // Returns the number of borrowed items
  Item** getBorrowedItems();  // Returns the list of borrowed items

  // Setters
  void setName(std::string newName);  // Sets the member's name
  void setID(int newID);              // Sets the member's ID
  void setBorrowedSize(
      int newSize);  // Updates the borrowed size (not typically needed)

  // Unique functions
  void borrowItem(Item* item);  // Adds an item to the member's borrowed list
  bool returnItem(
      Item* item);  // Removes an item from the member's borrowed list
  void displayBorrowedItems();  // Displays all items currently borrowed by the
                                // member

  // Destructor
  ~Member();  // Cleans up resources
};

#endif
