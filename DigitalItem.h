#ifndef DIGITALITEM_H
#define DIGITALITEM_H

#include "Item.h"  // Include the base class header for Item

// DigitalItem class inherits from Item
class DigitalItem : public Item {
private:
    int fileSize;             // Size of the digital item file, in bytes
    std::string Format;       // Format of the digital item (e.g., PDF, MP3)
    bool isBorrowed;          // Indicates if the digital item is currently borrowed

public:
    // Constructors
    DigitalItem();  // Default constructor that initializes attributes to default values
    DigitalItem(std::string title, std::string author, int fileSize,
                std::string Format);  // Parameterized constructor to set specific attributes

    // Getter and setter for fileSize
    void setfileSize(int fileSize);  // Set the size of the digital item file
    int getfileSize();                // Retrieve the size of the digital item file

    // Getter and setter for Format
    void setFormat(std::string Format); // Set the format of the digital item
    std::string getFormat();             // Retrieve the format of the digital item

    // Methods for handling borrowing conditions
    void Borrow(bool BorrowCondition); // Set borrowing status (true for borrow, false for return)
    bool getisBorrowed();              // Check if the digital item is currently borrowed

    // Method to display information about the digital item
    virtual void displayInfo(); // Outputs the details of the digital item

    // Methods for saving and loading digital item data
    virtual std::string save(); // Serialize the digital item's attributes to a string
    virtual void load(std::string& data); // Load and restore the digital item's attributes from a string

    // Destructor
    virtual ~DigitalItem(); // Clean up resources associated with the digital item
};

#endif // End of the header guard for DigitalItem.h
