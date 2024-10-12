#include "PrintedItem.h"

#include <sstream>

// Default constructor
PrintedItem::PrintedItem() {
  setAuthor("");
  setTitle("");
  this->PageCount = 0;
  this->BindingType = "";
  this->isBorrowed = false;
}

// Parameterized constructor
PrintedItem::PrintedItem(std::string title, std::string author, int PageCount,
                         std::string BindingType) {
  setAuthor(author);
  setTitle(title);
  this->PageCount = PageCount;
  this->BindingType = BindingType;  // Use the provided BindingType
  this->isBorrowed = false;
}

// Getter and setter for PageCount
void PrintedItem::setPageCount(int PageCount) { this->PageCount = PageCount; }

int PrintedItem::getPageCount() { return PageCount; }

// Getter and setter for BindingType
void PrintedItem::setBindingType(std::string BindingType) {
  this->BindingType = BindingType;
}

std::string PrintedItem::getBindingType() { return BindingType; }

// Borrowing and returning
void PrintedItem::Borrow(bool borrow) {
  this->isBorrowed = borrow;  // Set the borrowing status
}

bool PrintedItem::getisBorrowed() { return isBorrowed; }

// displaying information about the item
void PrintedItem::displayInfo() {
  std::cout << "Title: " << getTitle() << "\n"
            << "Author: " << getAuthor() << "\n"
            << "Page Count: " << getPageCount() << "\n"
            << "Binding Type: " << getBindingType() << "\n"
            << "Is Borrowed: " << (getisBorrowed() ? "Yes" : "No") << "\n";
}

// saving an item
std::string PrintedItem::save() {
  return  getTitle() + "|" + getAuthor()
  +"|" + std::to_string(PageCount) + "|" +
      BindingType;  // Saves the item's attributes, seperating the attributes
                    // by a |
}

// Load
void PrintedItem::load(std::string& data) {
    std::istringstream ss(data);
    std::string tempTitle, tempAuthor, pageCountStr, bindingType;

    // Read the first two attributes
    std::getline(ss, tempTitle, '|');    // Load title
    std::getline(ss, tempAuthor, '|');   // Load author

    // Set the attributes
    setTitle(tempTitle);
    setAuthor(tempAuthor);

    // Load PageCount
    std::getline(ss, pageCountStr, '|');  // Load page count string
    try {
        PageCount = std::stoi(pageCountStr);  // Convert to int
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: invalid page count: " << pageCountStr << std::endl;
        return;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Page count out of range in stoi: " << pageCountStr << std::endl;
        return;
    }

    // Load BindingType
    std::getline(ss, BindingType, '|');  // Load binding type
}

PrintedItem::~PrintedItem(){};  // destructor