#ifndef PRINTEDITEM_H
#define PRINTEDITEM_H

#include "Item.h"  // Includes the base class

class PrintedItem : public Item {  // Derived class from Item
 private:
  int PageCount;  // Number of pages
  std::string BindingType;  // Type of binding
  bool isBorrowed;  // Borrowing status

 public:
  // Constructors
  PrintedItem();  // Default
  PrintedItem(std::string title, std::string author, int PageCount, std::string BindingType);  // Parameterized

  // Getters and setters for page count
  void setPageCount(int PageCount);
  int getPageCount();

  // Getters and setters for binding type
  void setBindingType(std::string BindingType);
  std::string getBindingType();

  // Borrowing management
  void Borrow(bool BorrowCondition);  // Set borrowing status
  bool getisBorrowed();  // Check if borrowed

  // Display item information
  virtual void displayInfo();

  // Saving and loading data
  virtual std::string save();  // Save to string
  virtual void load(std::string& data);  // Load from string

  // destructor
  virtual ~PrintedItem();
};

#endif