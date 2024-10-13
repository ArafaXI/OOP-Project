#include "Item.h"

// Default constructor for the Item class
// Initializes title and author to empty strings
Item::Item() { 
    this->title = "";  // Set title to an empty string
    this->author = ""; // Set author to an empty string
}

// Parameterized constructor for the Item class
// Allows the initialization of title and author with specific values
Item::Item(std::string title, std::string author) { 
    this->title = title;    // Set the title with the provided value
    this->author = author;  // Set the author with the provided value
}

// Getter for the title attribute
// Returns the current value of the title
std::string Item::getTitle() {
    return this->title;
}

// Getter for the author attribute
// Returns the current value of the author
std::string Item::getAuthor() {
    return this->author;
}

// Setter for the title attribute
// Sets the title with a new value
void Item::setTitle(std::string title) {
    this->title = title;
}

// Setter for the author attribute
// Sets the author with a new value
void Item::setAuthor(std::string author) {
    this->author = author;
}

// Destructor for the Item class
// No dynamic memory to clean up, so it is left empty
Item::~Item() {}
