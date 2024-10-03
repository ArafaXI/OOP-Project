#include "Book.h"

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

Book::~Book() {}  // empty because nothing dynamically allocated here