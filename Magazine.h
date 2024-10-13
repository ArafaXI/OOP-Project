#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "PrintedItem.h"

class Magazine : public PrintedItem {
private:
    std::string publicationDate;  // Date of publication
    int issueNumber;  // Issue number of the magazine

public:
    Magazine();  // Default constructor
    Magazine(std::string title, std::string author, int pageCount, std::string bindingType, std::string publicationDate, int issueNumber);  // Constructor with parameters

    // Set and get the publication date
    void setPublicationDate(std::string publicationDate);
    std::string getPublicationDate();

    // Set and get the issue number
    void setIssueNumber(int issueNumber);
    int getIssueNumber();

    void displayInfo();  // Display magazine details

    std::string save();  // Save the magazine info to a string
    void load(std::string& data);  // Load magazine info from a string

    ~Magazine();  // Destructor
};

#endif
