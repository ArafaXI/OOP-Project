#ifndef EBOOK_H
#define EBOOK_H

#include "DigitalItem.h"

class Ebook: public DigitalItem{
    private:
    std:: string genre;
    std:: string publicationDate;
    public:
    // constructers
    Ebook();
    Ebook(std:: string title, std:: string author, int fileSize, std:: string Format, std:: string genre, std:: string publicationDate);

    // getters and setters for genre attribute

    void setGenre(std:: string genre);
    std:: string getGenre();

    // getters and setters for publicationdate attribute

    void setPublicationDate(std:: string publicationDate);
    std:: string getPublicationDate();

    // displayInfo function 
    void displayInfo();

    // destructor
    ~Ebook();
};

#endif