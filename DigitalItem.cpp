#include "DigitalItem.h"
#include <sstream>

// Default constructor: Initializes a digital item with default values
DigitalItem::DigitalItem() {
  setAuthor("");        // Sets the author to an empty string
  setTitle("");         // Sets the title to an empty string
  this->fileSize = 0;   // Initializes file size to 0
  this->Format = "";    // Sets the file format to an empty string
  this->isBorrowed = false; // Indicates that the item is not borrowed
}

// Parameterized constructor: Initializes a digital item with specified values
DigitalItem::DigitalItem(std::string title, std::string author, int fileSize,
                         std::string Format) {
  setAuthor(author);    // Sets the author using the provided argument
  setTitle(title);      // Sets the title using the provided argument
  this->fileSize = fileSize; // Sets the file size
  this->Format = Format;      // Sets the file format using the provided argument
  this->isBorrowed = false;   // Indicates that the item is not borrowed
}

// Setter for fileSize: Updates the file size of the digital item
void DigitalItem::setfileSize(int fileSize) { 
  this->fileSize = fileSize; 
}

// Getter for fileSize: Returns the current file size
int DigitalItem::getfileSize() { 
  return fileSize; 
}

// Setter for Format: Updates the format of the digital item
void DigitalItem::setFormat(std::string Format) { 
  this->Format = Format; 
}

// Getter for Format: Returns the current format of the digital item
std::string DigitalItem::getFormat() { 
  return Format; 
}

// Method to update the borrowing status of the digital item
void DigitalItem::Borrow(bool borrow) {
  this->isBorrowed = borrow; // Sets the borrowing status (true or false)
}

// Getter for borrowing status: Returns whether the item is borrowed
bool DigitalItem::getisBorrowed() { 
  return isBorrowed; 
}

// Method to display information about the digital item
void DigitalItem::displayInfo() {
  std::cout << "Title: " << getTitle() << "\n"
            << "Author: " << getAuthor() << "\n"
            << "File Size: " << getfileSize() << "\n"
            << "Format: " << getFormat() << "\n"
            << "Is Borrowed: " << (getisBorrowed() ? "Yes" : "No") << "\n";
}

// Method to serialize the digital item's attributes into a string for saving
std::string DigitalItem::save() {
  return getTitle() + "|" + getAuthor() + "|" +
         std::to_string(fileSize) + "|" + Format;  // Excludes the isBorrowed status
}

// Method to deserialize data from a formatted string and restore the digital item's attributes
void DigitalItem::load(std::string& data) {
    std::istringstream ss(data); // Create a string stream for parsing
    std::string tempTitle, tempAuthor;

    // Read the title, author, and file size attributes
    std::getline(ss, tempTitle, '|');    // Load the title
    std::getline(ss, tempAuthor, '|');   // Load the author
    std::string fileSizeStr;             // Temporary string to hold the file size
    std::getline(ss, fileSizeStr, '|');  // Load the file size as a string

    // Set the attributes for title and author
    setTitle(tempTitle);
    setAuthor(tempAuthor);

    // Attempt to convert the file size from string to integer
    try {
        fileSize = std::stoi(fileSizeStr);  // Convert to int
    } catch (const std::invalid_argument& e) {
        // Handle invalid argument error when converting file size
        std::cerr << "error: invalid file size: " << fileSizeStr << std::endl;
        return;
    } catch (const std::out_of_range& e) {
        // Handle out of range error when converting file size
        std::cerr << "Error: File size out of range in stoi: " << fileSizeStr << std::endl;
        return;
    }

    std::getline(ss, Format, '|');  // Load the format attribute
}

// Destructor: Clean up resources (if any) associated with the digital item
DigitalItem::~DigitalItem(){}; 
