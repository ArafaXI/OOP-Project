#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>

// This class will act as a parent class for the classes PrintedItem and
// DigitalItem, and is a virtual pure class that is not meant to be
// instantiated on its own.

class Item {
private:
    std::string title;
    std::string author;

public:
    // Default constructor
    Item();

    // Parameterized constructor
    Item(std:: string title, std:: string author);

    // Getters
    std::string getTitle();

    std::string getAuthor();

    // Setters
    void setTitle(std:: string title);

    void setAuthor(std:: string author);

    // Pure virtual function to display item information
    virtual void displayInfo() = 0;

    // Virtual destructor
    virtual ~Item();
};

#endif