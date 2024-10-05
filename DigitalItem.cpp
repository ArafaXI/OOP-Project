#include "DigitalItem.h"

// Default constructor
DigitalItem::DigitalItem() {
    setAuthor("");
    setTitle("");
    this-> fileSize = 0;
    this->Format = "";
    this->isBorrowed = false;   
}

// Parameterized constructor
DigitalItem::DigitalItem(std::string title, std::string author, double fileSize, std::string Format) {
    setAuthor(author);
    setTitle(title);
    this-> fileSize =  fileSize;
    this->Format = Format;  // Use the provided Format
    this->isBorrowed = false;
}

// Getter and setter for  fileSize
void DigitalItem::setfileSize(double fileSize) {
    this-> fileSize =  fileSize;
} 

int DigitalItem::getfileSize() {
    return  fileSize;
}

// Getter and setter for Format
void DigitalItem::setFormat(std::string Format) {
    this->Format = Format;
}

std::string DigitalItem::getFormat() {
    return Format;
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
              << "File Size: " << getfileSize() << "\n"
              << "Format: " << getFormat() << "\n"
              << "Is Borrowed: " << (getisBorrowed() ? "Yes" : "No") << "\n";
}

DigitalItem:: ~DigitalItem(){}; // destructor