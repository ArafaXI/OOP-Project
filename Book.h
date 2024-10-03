#ifndef BOOK_H
#define BOOK_H

#include "PrintedItem.h"

class Book: public PrintedItem{
    private:
    std:: string genre;
    std:: string publicationDate;
    public:
    // constructers
    Book();
    Book(std:: string title, std:: string author, int PageCount, std:: string BindingType, std:: string genre, std:: string publicationDate);

    // getters and setters for genre attribute

    void setGenre(std:: string genre);
    std:: string getGenre();

    // getters and setters for publicationdate attribute

    void setPublicationDate(std:: string publicationDate);
    std:: string getPublicationDate();

    // displayInfo function 
    void displayInfo();

    // destructor
    ~Book();
};

#endif