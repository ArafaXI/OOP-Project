#ifndef PRINTEDITEM_H
#define PRINTEDITEM_H

#include "Item.h"

class PrintedItem : public Item {
 private:
  int PageCount;
  std::string BindingType;
  bool isBorrowed;

 public:
  // Constructers
  PrintedItem();
  PrintedItem(std::string title, std::string author, int PageCount, std::string BindingType);

  // Getters and Setters for pagecount
  void setPageCount(int PageCount);
  int getPageCount();

  // Getters and setters for bindingtype
  void setBindingType(std::string BindingType);
  std::string getBindingType();

  // Borrowing conditions
  void Borrow(bool BorrowCondition);  // For both borrowing and returning
  bool getisBorrowed();

  // displayitems
  virtual void displayInfo();

  // destructor
  virtual ~PrintedItem();
};

#endif