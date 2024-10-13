#ifndef EBOOK_H
#define EBOOK_H

#include "DigitalItem.h"  // Include the base class header for DigitalItem
// The Ebook class is derived from the DigitalItem class and represents an
// electronic book.
class Ebook : public DigitalItem {
 private:
  std::string genre;  // The genre of the eBook (e.g., fiction, non-fiction)
  std::string publicationDate;  // The publication date of the eBook

 public:
  // Default constructor initializes an eBook with default values
  Ebook();

  // Parameterized constructor initializes an eBook with specific values
  Ebook(std::string title, std::string author, double fileSize,
        std::string Format, std::string genre, std::string publicationDate);

  // Setter for the genre attribute
  void setGenre(std::string genre);

  // Getter for the genre attribute
  std::string getGenre();

  // Setter for the publication date attribute
  void setPublicationDate(std::string publicationDate);

  // Getter for the publication date attribute
  std::string getPublicationDate();

  // Function to display information about the eBook
  void displayInfo();

  // Function to save the eBook's data to a string format
  std::string save();

  // Function to load the eBook's data from a string format
  void load(std::string& data);

  // Destructor to clean up resources (if any)
  ~Ebook();
};

#endif