#include "Book.h"
#include <sstream>

// Constructors
Book::Book() {
  this->setAuthor("");
  this->setTitle("");
  this->setPageCount(0);
  this->setBindingType("");
  this->Borrow(0);
  this->genre = "";
  this->publicationDate = "";
}

Book::Book(std::string title, std::string author, int PageCount,
           std::string BindingType, std::string genre,
           std::string publicationDate) {
  this->setAuthor(author);
  this->setTitle(title);
  this->setPageCount(PageCount);
  this->setBindingType(BindingType);
  this->Borrow(0);
  this->genre = genre;
  this->publicationDate = publicationDate;
}

// Getters and setters for genre attribute
void Book::setGenre(std::string genre) { this->genre = genre; }

std::string Book::getGenre() { return genre; }

// Getters and setters for publicationDate attribute
void Book::setPublicationDate(std::string publicationDate) {
  this->publicationDate = publicationDate;
}

std::string Book::getPublicationDate() { return publicationDate; }

// Displayinfo function

void Book::displayInfo() {
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
  return "Book|" + PrintedItem::save() + "|" + genre + "|" +
         publicationDate;  // Call the base class save
}

// Load
void Book::load(std::string& data) {
    // Start by loading the PrintedItem attributes first
    PrintedItem::load(data);

    std::istringstream ss(data);
    std::string type, tempTitle, tempAuthor, pageCountStr, bindingType, genre, publicationDate;
    int tempPageCount;

    // Read the necessary attributes for Book
    std::getline(ss, type, '|');               // Read type (could be Book)
    std::getline(ss, tempTitle, '|');          // Title
    std::getline(ss, tempAuthor, '|');         // Author
    std::getline(ss, pageCountStr, '|');       // Page Count
    std::getline(ss, bindingType, '|');        // Binding Type
    std::getline(ss, genre, '|');              // Genre
    std::getline(ss, publicationDate, '|');    // Publication Date

    // Set the attributes
    setTitle(tempTitle);
    setAuthor(tempAuthor);

    try {
        int tempPageCount = std::stoi(pageCountStr);  // Convert to int
        setPageCount(tempPageCount);
    } catch (const std::invalid_argument& e) {
        std::cerr << "error: invalid page count: " << pageCountStr << std::endl;
        return;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Page count out of range in stoi: " << pageCountStr << std::endl;
        return;
    }
    
    setBindingType(bindingType);
    this->genre = genre;
    this->publicationDate = publicationDate;
}

Book::~Book() {}  // empty because nothing dynamically allocated here