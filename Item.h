#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <fstream> // Necessary for file operations such as loading and saving

// The Item class serves as a base class for PrintedItem and DigitalItem.
// It is a pure virtual class, meaning it is not designed to be instantiated directly.
// It provides common attributes and functions that will be inherited and implemented by derived classes.

class Item {
private:
    std::string title;   // Holds the title of the item
    std::string author;  // Holds the author of the item

public:
    // Default constructor
    // Initializes title and author to empty strings
    Item();

    // Parameterized constructor
    // Allows setting title and author at the time of object creation
    Item(std::string title, std::string author);

    // Getter for the title attribute
    // Returns the value of the title
    std::string getTitle();

    // Getter for the author attribute
    // Returns the value of the author
    std::string getAuthor();

    // Setter for the title attribute
    // Allows setting a new value for the title
    void setTitle(std::string title);

    // Setter for the author attribute
    // Allows setting a new value for the author
    void setAuthor(std::string author);

    // Pure virtual function to display item information
    // This will be implemented in derived classes, forcing them to define their own version of displayInfo.
    virtual void displayInfo() = 0;

    // Pure virtual function for borrowing or returning an item
    // This will be defined in the derived classes to handle borrowing logic.
    virtual void Borrow(bool borrow) = 0;
    
    // Pure virtual function to check borrowing status
    // The derived classes will implement this to return whether the item is borrowed.
    virtual bool getisBorrowed() = 0;

    // Pure virtual functions for saving and loading
    // Each derived class will have its own unique attributes to save and load, so these functions will be overridden.
    virtual std::string save() = 0;
    virtual void load(std::string& data) = 0;

    // Virtual destructor
    // Ensures that the derived class destructors are called properly when deleting an Item object.
    virtual ~Item();
};

#endif
