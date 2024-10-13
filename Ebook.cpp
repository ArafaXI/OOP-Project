#include "Ebook.h"

#include <sstream>

// Default constructor
Ebook::Ebook() {
  // Initialize all attributes to default values
  this->setAuthor("");         // Set author to an empty string
  this->setTitle("");          // Set title to an empty string
  this->setfileSize(0);        // Set file size to 0
  this->setFormat("");         // Set format to an empty string
  this->Borrow(0);             // Initialize borrowing status to not borrowed
  this->genre = "";            // Set genre to an empty string
  this->publicationDate = "";  // Set publication date to an empty string
}

// Parameterized constructor
Ebook::Ebook(std::string title, std::string author, double fileSize,
             std::string Format, std::string genre,
             std::string publicationDate) {
  // Set the attributes using the provided parameters
  this->setAuthor(author);      // Set the author from the argument
  this->setTitle(title);        // Set the title from the argument
  this->setfileSize(fileSize);  // Set the file size from the argument
  this->setFormat(Format);      // Set the format from the argument
  this->Borrow(0);              // Initialize borrowing status to not borrowed
  this->genre = genre;          // Set the genre from the argument
  this->publicationDate =
      publicationDate;  // Set the publication date from the argument
}

// Getters and setters for the genre attribute
void Ebook::setGenre(std::string genre) {
  this->genre = genre;  // Set the genre attribute
}

std::string Ebook::getGenre() {
  return genre;  // Return the current genre
}

// Getters and setters for the publication date attribute
void Ebook::setPublicationDate(std::string publicationDate) {
  this->publicationDate =
      publicationDate;  // Set the publication date attribute
}

std::string Ebook::getPublicationDate() {
  return publicationDate;  // Return the current publication date
}

// Function to display information about the Ebook
void Ebook::displayInfo() {
  // Print out the details of the Ebook
  std::cout << "Title: " << getTitle() << "\n"
            << "Author: " << getAuthor() << "\n"
            << "File Size: " << getfileSize() << "\n"
            << "Format: " << getFormat() << "\n"
            << "Genre: " << getGenre() << "\n"
            << "Publication Date: " << getPublicationDate() << "\n"
            << "Is Borrowed: " << (getisBorrowed() ? "Yes" : "No") << "\n";
}

// Save function to serialize the Ebook attributes to a string
std::string Ebook::save() {
  // Call the base class's save function and append additional attributes
  return "Ebook|" + DigitalItem::save() + "|" + genre + "|" + publicationDate;
}

// Load function to deserialize the Ebook attributes from a string
void Ebook::load(std::string& data) {
  // Start by loading the DigitalItem attributes first
  DigitalItem::load(data);

  // Use a string stream to read the data
  std::istringstream ss(data);
  std::string type, tempTitle, tempAuthor, fileSizeStr, Format, genre,
      publicationDate;
  int tempfileSize;

  // Read necessary attributes for the Ebook
  std::getline(ss, type, '|');             // Read the type (should be "Ebook")
  std::getline(ss, tempTitle, '|');        // Read the title
  std::getline(ss, tempAuthor, '|');       // Read the author
  std::getline(ss, fileSizeStr, '|');      // Read the file size
  std::getline(ss, Format, '|');           // Read the format
  std::getline(ss, genre, '|');            // Read the genre
  std::getline(ss, publicationDate, '|');  // Read the publication date

  // Convert the file size string to an integer
  try {
    tempfileSize = std::stoi(fileSizeStr);  // Convert to int
  } catch (const std::invalid_argument& e) {
    std::cerr << "error: invalid file size: " << fileSizeStr
              << std::endl;  // Handle conversion error
    return;
  } catch (const std::out_of_range& e) {
    std::cerr << "Error: File size out of range in stoi: " << fileSizeStr
              << std::endl;  // Handle range error
    return;
  }

  // Set the attributes with the loaded data
  setTitle(tempTitle);        // Set title from the loaded data
  setAuthor(tempAuthor);      // Set author from the loaded data
  setfileSize(tempfileSize);  // Set file size from the loaded data
  setFormat(Format);          // Set format from the loaded data
  setGenre(genre);            // Set genre from the loaded data
  setPublicationDate(
      publicationDate);  // Set publication date from the loaded data
}

// Destructor
Ebook::~Ebook() {}  // No dynamic memory allocated, so no cleanup necessary
