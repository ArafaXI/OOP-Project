#include "DigitalItem.h"

// Default constructor
DigitalItem::DigitalItem() {
    setAuthor("");
    setTitle("");
    this-> fileSize = 0;
    this->BindingType = "";
    this->isBorrowed = false;   
}

// Parameterized constructor
DigitalItem::DigitalItem(std::string title, std::string author, double fileSize, std::string BindingType) {
    setAuthor(author);
    setTitle(title);
    this-> fileSize =  fileSize;
    this->BindingType = BindingType;  // Use the provided BindingType
    this->isBorrowed = false;
}

// Getter and setter for  fileSize
void DigitalItem::setfileSize(double fileSize) {
    this-> fileSize =  fileSize;
} 

int DigitalItem::get fileSize() {
    return  fileSize;
}

// Getter and setter for BindingType
void DigitalItem::setBindingType(std::string BindingType) {
    this->BindingType = BindingType;
}

std::string DigitalItem::getBindingType() {
    return BindingType;
}

// Borrowing and returning
void DigitalItem::Borrow(bool borrow) {
    this->isBorrowed = borrow; // Set the borrowing status
}

bool DigitalItem:: getisBorrowed(){
    return isBorrowed;
}

// displaying information about the item 
void DigitalItem::displayInfo() {
    std::cout << "Title: " << getTitle() << "\n"
              << "Author: " << getAuthor() << "\n"
              << "Page Count: " << get fileSize() << "\n"
              << "Binding Type: " << getBindingType() << "\n"
              << "Is Borrowed: " << (getisBorrowed() ? "Yes" : "No") << "\n";
}

DigitalItem:: ~DigitalItem(){}; // destructor