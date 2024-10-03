#include "Magazine.h"

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
                   std::string bindingType, std::string publicationDate, int issueNumber) {
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

std::string Magazine::getPublicationDate() {
    return publicationDate;
}

// Getters and setters for issueNumber attribute
void Magazine::setIssueNumber(int issueNumber) {
    this->issueNumber = issueNumber;
}

int Magazine::getIssueNumber() {
    return issueNumber;
}

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

// Destructor
Magazine::~Magazine() {}  // empty because nothing dynamically allocated here