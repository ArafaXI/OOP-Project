#include "PrintedItem.h"

// Default constructor
PrintedItem::PrintedItem() {
    setAuthor("");
    setTitle("");
    this->PageCount = 0;
    this->BindingType = "";
    this->isBorrowed = false;   
}

// Parameterized constructor
PrintedItem::PrintedItem(std::string title, std::string author, int PageCount, std::string BindingType) {
    setAuthor(author);
    setTitle(title);
    this->PageCount = PageCount;
    this->BindingType = BindingType;  // Use the provided BindingType
    this->isBorrowed = false;
}

// Getter and setter for PageCount
void PrintedItem::setPageCount(int PageCount) {
    this->PageCount = PageCount;
} 

int PrintedItem::getPageCount() {
    return PageCount;
}

// Getter and setter for BindingType
void PrintedItem::setBindingType(std::string BindingType) {
    this->BindingType = BindingType;
}

std::string PrintedItem::getBindingType() {
    return BindingType;
}

// Borrowing and returning
void PrintedItem:: Borrow(bool BorrowCondition){
    this -> isBorrowed = BorrowCondition;
}

bool PrintedItem:: getisBorrowed(){
    return isBorrowed;
}

// displaying information about the item 
void PrintedItem::displayInfo() {
    std::cout << "Title: " << getTitle() << "\n"
              << "Author: " << getAuthor() << "\n"
              << "Page Count: " << getPageCount() << "\n"
              << "Binding Type: " << getBindingType() << "\n"
              << "Is Borrowed: " << (getisBorrowed() ? "Yes" : "No") << "\n";
}

PrintedItem:: ~PrintedItem(){}; // destructor