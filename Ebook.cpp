#include "Ebook.h"
#include <sstream>

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

// Saving
std::string Ebook::save() {
    return "Ebook|" + DigitalItem::save() + "|" + genre + "|" + publicationDate; // Call the base class save
}

// loading
void Ebook::load(std::string& data) {
    // Start by loading the DigitalItem attributes first
    DigitalItem::load(data);

    std::istringstream ss(data);
    std::string type, tempTitle, tempAuthor, fileSizeStr, Format, genre, publicationDate;
    int tempfileSize;

    // Read the necessary attributes for Ebook
    std::getline(ss,type, '|');
    std::getline(ss, tempTitle, '|');   // Title
    std::getline(ss, tempAuthor, '|');   // Author
    std::getline(ss, fileSizeStr, '|');  // File Size
    std::getline(ss, Format, '|');       // Format
    std::getline(ss, genre, '|');        // Genre
    std::getline(ss, publicationDate, '|');  // Release Date

    try {
        tempfileSize = std::stoi(fileSizeStr);  // Convert to int
    } catch (const std::invalid_argument& e) {
        std::cerr << "error: invalid file size: " << fileSizeStr << std::endl;
        return;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: File size out of range in stoi: " << fileSizeStr << std::endl;
        return;
    }

    // Set the attributes
    setTitle(tempTitle);
    setAuthor(tempAuthor);
    setfileSize(tempfileSize);
    setFormat(Format);
    setGenre(genre);
    setPublicationDate(publicationDate);
}


Ebook::~Ebook() {}  // empty because nothing dynamically allocated here