#include "Book.h"
#include <sstream>

// Constructors
Book::Book() {
  // Default constructor: Initializes all attributes to default values
  this->setAuthor("");               // Empty author
  this->setTitle("");                // Empty title
  this->setPageCount(0);             // Page count set to 0
  this->setBindingType("");          // Empty binding type
  this->Borrow(0);                   // Not borrowed by default (0)
  this->genre = "";                  // Empty genre
  this->publicationDate = "";        // Empty publication date
}

Book::Book(std::string title, std::string author, int PageCount,
           std::string BindingType, std::string genre,
           std::string publicationDate) {
  // Parameterized constructor: Allows initialization of all attributes
  this->setAuthor(author);           // Set author
  this->setTitle(title);             // Set title
  this->setPageCount(PageCount);     // Set page count
  this->setBindingType(BindingType); // Set binding type
  this->Borrow(0);                   // Not borrowed by default (0)
  this->genre = genre;               // Set genre
  this->publicationDate = publicationDate; // Set publication date
}

// Getters and setters for genre attribute
void Book::setGenre(std::string genre) { 
  // Set the genre attribute
  this->genre = genre; 
}

std::string Book::getGenre() { 
  // Return the genre attribute
  return genre; 
}

// Getters and setters for publicationDate attribute
void Book::setPublicationDate(std::string publicationDate) {
  // Set the publicationDate attribute
  this->publicationDate = publicationDate;
}

std::string Book::getPublicationDate() { 
  // Return the publicationDate attribute
  return publicationDate; 
}

// Displayinfo function
void Book::displayInfo() {
  // Displays all the details of the book object in a readable format
  std::cout << "Title: " << getTitle() << "\n"
            << "Author: " << getAuthor() << "\n"
            << "Page Count: " << getPageCount() << "\n"
            << "Binding Type: " << getBindingType() << "\n"
            << "Genre: " << getGenre() << "\n"
            << "Publication Date: " << getPublicationDate() << "\n"
            << "Is Borrowed: " << (getisBorrowed() ? "Yes" : "No") << "\n";
}

// Save
std::string Book::save() {
  // Creates a serialized string of the book object, formatted for easy saving
  // PrintedItem::save() saves the common attributes from the base class
  return "Book|" + PrintedItem::save() + "|" + genre + "|" + publicationDate;
}

// Load
void Book::load(std::string& data) {
    // Start by loading the PrintedItem attributes first
    PrintedItem::load(data); // Load the base class attributes
    
    std::istringstream ss(data);
    std::string type, tempTitle, tempAuthor, pageCountStr, bindingType, genre, publicationDate;
    int tempPageCount;

    // Parse the string 'data' and extract the attributes
    std::getline(ss, type, '|');               // Read type (e.g., "Book")
    std::getline(ss, tempTitle, '|');          // Read title
    std::getline(ss, tempAuthor, '|');         // Read author
    std::getline(ss, pageCountStr, '|');       // Read page count as a string
    std::getline(ss, bindingType, '|');        // Read binding type
    std::getline(ss, genre, '|');              // Read genre
    std::getline(ss, publicationDate, '|');    // Read publication date

    // Set the extracted attributes to the object
    setTitle(tempTitle);
    setAuthor(tempAuthor);

    try {
        // Convert page count from string to int
        int tempPageCount = std::stoi(pageCountStr);
        setPageCount(tempPageCount); // Set page count
    } catch (const std::invalid_argument& e) {
        // Handle error if the page count string isn't a valid number
        std::cerr << "error: invalid page count: " << pageCountStr << std::endl;
        return;
    } catch (const std::out_of_range& e) {
        // Handle error if the page count number is out of range for an int
        std::cerr << "Error: Page count out of range in stoi: " << pageCountStr << std::endl;
        return;
    }
    
    setBindingType(bindingType);       // Set the binding type
    this->genre = genre;               // Set the genre
    this->publicationDate = publicationDate; // Set the publication date
}

// Destructor
Book::~Book() {}  // No dynamic memory allocation, so nothing to clean up
