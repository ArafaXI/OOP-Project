#ifndef DIGITALITEM_H
#define DIGITALITEM_H

#include "Item.h"

class DigitalItem : public Item {
 private:
  int fileSize;
  std::string Format;
  bool isBorrowed;

 public:
  // Constructers
  DigitalItem();
  DigitalItem(std::string title, std::string author, int fileSize,
              std::string Format);

  // Getters and Setters for pagecount
  void setfileSize(int fileSize);
  int getfileSize();

  // Getters and setters for Format
  void setFormat(std::string Format);
  std::string getFormat();

  // Borrowing conditions
  void Borrow(bool BorrowCondition); // For both borrowing and returning
  bool getisBorrowed();

  // displayitems
  virtual void displayInfo();

  // saving and loading
  virtual std::string save();
  virtual void load(std::string& data);
  // destructor
  virtual ~DigitalItem();
};

#endif