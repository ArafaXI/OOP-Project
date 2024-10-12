#include "DigitalItem.h"

#include <sstream>

// Default constructor
DigitalItem::DigitalItem() {
  setAuthor("");
  setTitle("");
  this->fileSize = 0;
  this->Format = "";
  this->isBorrowed = false;
}

// Parameterized constructor
DigitalItem::DigitalItem(std::string title, std::string author, int fileSize,
                         std::string Format) {
  setAuthor(author);
  setTitle(title);
  this->fileSize = fileSize;
  this->Format = Format;  // Use the provided Format
  this->isBorrowed = false;
}

// Getter and setter for  fileSize
void DigitalItem::setfileSize(int fileSize) { this->fileSize = fileSize; }

int DigitalItem::getfileSize() { return fileSize; }

// Getter and setter for Format
void DigitalItem::setFormat(std::string Format) { this->Format = Format; }

std::string DigitalItem::getFormat() { return Format; }

// Borrowing and returning
void DigitalItem::Borrow(bool borrow) {
  this->isBorrowed = borrow;  // Set the borrowing status
}

bool DigitalItem::getisBorrowed() { return isBorrowed; }

// displaying information about the item
void DigitalItem::displayInfo() {
  std::cout << "Title: " << getTitle() << "\n"
            << "Author: " << getAuthor() << "\n"
            << "File Size: " << getfileSize() << "\n"
            << "Format: " << getFormat() << "\n"
            << "Is Borrowed: " << (getisBorrowed() ? "Yes" : "No") << "\n";
}

// Save
std::string DigitalItem::save() {
  return  getTitle() + "|" + getAuthor() + "|" +
         std::to_string(fileSize) + "|" + Format;  // Exclude isBorrowed
}

// Load
void DigitalItem::load(std::string& data) {
    std::istringstream ss(data);
    std::string tempTitle, tempAuthor;

    // Read the first three attributes
    std::getline(ss, tempTitle, '|');    // Load title
    std::getline(ss, tempAuthor, '|');   // Load author
    std::string fileSizeStr;             // Temporary string for file size
    std::getline(ss, fileSizeStr, '|');  // Load file size string

    // Set the attributes
    setTitle(tempTitle);
    setAuthor(tempAuthor);

    try {
        fileSize = std::stoi(fileSizeStr);  // Convert to int
    } catch (const std::invalid_argument& e) {
        std::cerr << "error: invalid file size: " << fileSizeStr << std::endl;
        return;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: File size out of range in stoi: " << fileSizeStr << std::endl;
        return;
    }

    std::getline(ss, Format, '|');  // Load format
}

DigitalItem::~DigitalItem(){};  // destructor