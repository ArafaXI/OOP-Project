#ifndef BOOK_H
#define BOOK_H

#include "PrintedItem.h"

//Book class inheris from PrintedItem
class Book: public PrintedItem{
    private:
    std:: string genre;   //Genre of the book
    std:: string publicationDate; //Publication of the book
    public:
    // constructers
    Book();
    Book(std:: string title, std:: string author, int PageCount, std:: string BindingType, std:: string genre, std:: string publicationDate);

    // getters and setters for genre attribute

    void setGenre(std:: string genre); //Set genre of the book
    std:: string getGenre();          //Get genre of the book

    // getters and setters for publicationdate attribute

    void setPublicationDate(std:: string publicationDate);
    std:: string getPublicationDate();

    // displayInfo function 
    void displayInfo(); //Outputs the book's details

    // Saving and Loading:
    // Converts the book's attributes into a formatted string for storage 
    std:: string save(); 
    // Parses a formatted string to restore the book's attributes
    void load(std:: string& data);

    // destructor
    ~Book();
};

#endif