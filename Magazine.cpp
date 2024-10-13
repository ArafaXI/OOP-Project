#include "Magazine.h"
#include <sstream>

// Default constructor: Initializes all Magazine attributes to default values (empty strings, zeroes, not borrowed).
Magazine::Magazine() {
  this->setAuthor("");  
  this->setTitle("");   
  this->setPageCount(0);  
  this->setBindingType("");  
  this->Borrow(0);  
  this->publicationDate = "";  
  this->issueNumber = 0;  
}

// Parameterized constructor: Initializes a Magazine object with specific values for title, author, etc.
Magazine::Magazine(std::string title, std::string author, int pageCount, std::string bindingType, std::string publicationDate, int issueNumber) {
  this->setAuthor(author);  
  this->setTitle(title);  
  this->setPageCount(pageCount);  
  this->setBindingType(bindingType);  
  this->Borrow(0);  
  this->publicationDate = publicationDate;  
  this->issueNumber = issueNumber;  
}

// Setter for the publication date
void Magazine::setPublicationDate(std::string publicationDate) {
  this->publicationDate = publicationDate;
}

// Getter for the publication date
std::string Magazine::getPublicationDate() {
  return publicationDate;
}

// Setter for the issue number
void Magazine::setIssueNumber(int issueNumber) {
  this->issueNumber = issueNumber;
}

// Getter for the issue number
int Magazine::getIssueNumber() {
  return issueNumber;
}

// Displays all the information about the magazine, such as title, author, and issue number.
void Magazine::displayInfo() {
  std::cout << "Title: " << getTitle() << "\n"
            << "Author: " << getAuthor() << "\n"
            << "Page Count: " << getPageCount() << "\n"
            << "Binding Type: " << getBindingType() << "\n"
            << "Publication Date: " << getPublicationDate() << "\n"
            << "Issue Number: " << getIssueNumber() << "\n"
            << "Is Borrowed: " << (getisBorrowed() ? "Yes" : "No") << "\n";
}

// Save function: Converts the magazine's data into a string format that can be written to a file.
std::string Magazine::save() {
  return "Magazine|" + PrintedItem::save() + "|" + publicationDate + "|" + std::to_string(issueNumber);  
  // Combines the data into a single string with '|' as the delimiter.
}

// Load function: Takes a string (typically from a file) and extracts the magazine's information from it.
void Magazine::load(std::string& data) {
    // Load the common attributes first from the base class (PrintedItem).
    PrintedItem::load(data);

    std::istringstream ss(data);  // Create a string stream to parse the data
    std::string type, tempTitle, tempAuthor, pageCountStr, bindingType, issueNumberStr, publicationDate;

    // Extract different parts of the data, separated by '|'
    std::getline(ss, type, '|');  
    std::getline(ss, tempTitle, '|');  
    std::getline(ss, tempAuthor, '|');  
    std::getline(ss, pageCountStr, '|');  
    std::getline(ss, bindingType, '|');  
    std::getline(ss, publicationDate, '|');  
    std::getline(ss, issueNumberStr, '|');  

    // Set the extracted values to the magazine object
    setTitle(tempTitle);
    setAuthor(tempAuthor);

    // Convert the page count from a string to an integer and set it
    try {
        int tempPageCount = std::stoi(pageCountStr);
        setPageCount(tempPageCount);
    } catch (const std::invalid_argument& e) {
        std::cerr << "error: invalid page count: " << pageCountStr << std::endl;
        return;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Page count out of range in stoi: " << pageCountStr << std::endl;
        return;
    }

    setBindingType(bindingType);  // Set binding type

    // Convert the issue number from a string to an integer and set it
    try {
        int tempIssueNumber = std::stoi(issueNumberStr);
        setIssueNumber(tempIssueNumber);
    } catch (const std::invalid_argument& e) {
        std::cerr << "error: invalid issue number: " << issueNumberStr << std::endl;
        return;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Issue number out of range in stoi: " << issueNumberStr << std::endl;
        return;
    }

    this->publicationDate = publicationDate;  // Set the publication date
}

// Destructor: Empty because there's no dynamically allocated memory to clean up for Magazine objects.
Magazine::~Magazine() {}
