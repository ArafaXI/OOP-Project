#include "Ebook.h"

// Constructors
Ebook::Ebook() {
  this->setAuthor("");
  this->setTitle("");
  this->setfileSize(0);
  this->setFormat("");
  this->Borrow(0);
  this->genre = "";
  this->publicationDate = "";
}

Ebook::Ebook(std::string title, std::string author, double fileSize,
           std::string Format, std::string genre,
           std::string publicationDate) {
  this->setAuthor(author);
  this->setTitle(title);
  this->setfileSize(fileSize);
  this->setFormat(Format);
  this->Borrow(0);
  this->genre = genre;
  this->publicationDate = publicationDate;
}

// Getters and setters for genre attribute
void Ebook::setGenre(std::string genre) { this->genre = genre; }

std::string Ebook::getGenre() { return genre; }

// Getters and setters for publicationDate attribute
void Ebook::setPublicationDate(std::string publicationDate) {
  this->publicationDate = publicationDate;
}

std::string Ebook::getPublicationDate() { return publicationDate; }

// Displayinfo function

void Ebook::displayInfo() {
  std::cout << "Title: " << getTitle() << "\n"
            << "Author: " << getAuthor() << "\n"
            << "File Size: " << getfileSize() << "\n"
            << "Format: " << getFormat() << "\n"
            << "Genre: " << getGenre() << "\n"
            << "Publication Date: " << getPublicationDate() << "\n"
            << "Is Borrowed: " << (getisBorrowed() ? "Yes" : "No") << "\n";
}

Ebook::~Ebook() {}  // empty because nothing dynamically allocated here