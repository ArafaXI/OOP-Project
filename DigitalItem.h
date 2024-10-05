#ifndef DIGITALITEM_H
#define DIGITALITEM_H

#include "Item.h"

class DigitalItem : public Item {
 private:
  double fileSize;
  std::string Format;
  bool isBorrowed;

 public:
  // Constructers
  DigitalItem();
  DigitalItem(std::string title, std::string author, double fileSize,
              std::string Format);

  // Getters and Setters for pagecount
  void setPageCount(double fileSize);
  int getPageCount();

  // Getters and setters for Format
  void setFormat(std::string Format);
  std::string getFormat();

  // Borrowing conditions
  void Borrow(bool BorrowCondition); // For both borrowing and returning
  bool getisBorrowed();

  // displayitems
  virtual void displayInfo();

  // destructor
  virtual ~DigitalItem();
};

#endif