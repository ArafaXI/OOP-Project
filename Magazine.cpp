#include "Magazine.h"
#include <sstream>

// Constructors
Magazine::Magazine() {
  this->setAuthor("");
  this->setTitle("");
  this->setPageCount(0);
  this->setBindingType("");
  this->Borrow(0);
  this->publicationDate = "";
  this->issueNumber = 0;
}

Magazine::Magazine(std::string title, std::string author, int pageCount,
                   std::string bindingType, std::string publicationDate,
                   int issueNumber) {
  this->setAuthor(author);
  this->setTitle(title);
  this->setPageCount(pageCount);
  this->setBindingType(bindingType);
  this->Borrow(0);
  this->publicationDate = publicationDate;
  this->issueNumber = issueNumber;
}

// Getters and setters for publicationDate attribute
void Magazine::setPublicationDate(std::string publicationDate) {
  this->publicationDate = publicationDate;
}

std::string Magazine::getPublicationDate() { return publicationDate; }

// Getters and setters for issueNumber attribute
void Magazine::setIssueNumber(int issueNumber) {
  this->issueNumber = issueNumber;
}

int Magazine::getIssueNumber() { return issueNumber; }

// DisplayInfo function
void Magazine::displayInfo() {
  std::cout << "Title: " << getTitle() << "\n"
            << "Author: " << getAuthor() << "\n"
            << "Page Count: " << getPageCount() << "\n"
            << "Binding Type: " << getBindingType() << "\n"
            << "Publication Date: " << getPublicationDate() << "\n"
            << "Issue Number: " << getIssueNumber() << "\n"
            << "Is Borrowed: " << (getisBorrowed() ? "Yes" : "No") << "\n";
}

// Save
std::string Magazine::save() {
  return "Magazine|" + PrintedItem::save() + "|" + publicationDate + "|" +
         std::to_string(issueNumber);  // Call the base class save
}

// Load 
void Magazine::load(std::string& data) {
    // Start by loading the PrintedItem attributes first
    PrintedItem::load(data);

    std::istringstream ss(data);
    std::string type, tempTitle, tempAuthor, pageCountStr, bindingType, issueNumberStr, publicationDate;

    // Read the necessary attributes for Magazine
    std::getline(ss, type, '|'); // Read Type
    std::getline(ss, tempTitle, '|');          // Title
    std::getline(ss, tempAuthor, '|');         // Author
    std::getline(ss, pageCountStr, '|');       // Page Count
    std::getline(ss, bindingType, '|');        // Binding Type
    std::getline(ss, publicationDate, '|');     // Issue Number
    std::getline(ss, issueNumberStr, '|');    // Publication Date

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

    try {
        int tempIssueNumber = std::stoi(issueNumberStr);  // Convert to int
        setIssueNumber(tempIssueNumber);
    } catch (const std::invalid_argument& e) {
        std::cerr << "error: invalid issue number: " << issueNumberStr << std::endl;
        return;
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: Issue number out of range in stoi: " << issueNumberStr << std::endl;
        return;
    }

    this->publicationDate = publicationDate;  // Set publication date
}

// Destructor
Magazine::~Magazine() {}  // empty because nothing dynamically allocated here