#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "PrintedItem.h"

class Magazine: public PrintedItem {
private:
    std::string publicationDate;
    int issueNumber;
public:
    // Constructors
    Magazine();
    Magazine(std::string title, std::string author, int pageCount, std::string bindingType, std::string publicationDate, int issueNumber);

    // Getters and setters for publicationDate attribute
    void setPublicationDate(std::string publicationDate);
    std::string getPublicationDate();

    // Getters and setters for issueNumber attribute
    void setIssueNumber(int issueNumber);
    int getIssueNumber();

    // DisplayInfo function 
    void displayInfo();

    // Destructor
    ~Magazine();
};

#endif