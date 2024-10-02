#include <iostream>
#include "PrintedItem.h"

int main() {
    // Create a PrintedItem using the default constructor
    PrintedItem item1;
    
    // Display default values
    std::cout << "Default Item:\n";
    item1.displayInfo();
    
    // Set values using the parameterized constructor
    PrintedItem item2("The Great Gatsby", "F. Scott Fitzgerald", 180, "Hardcover");
    
    // Display values for item2
    std::cout << "\nParameterized Item:\n";
    item2.displayInfo();
    
    // Test setters
    item2.setPageCount(200);
    item2.setBindingType("Paperback");
    item2.Borrow(true); // Set item as borrowed
    
    // Display updated values
    std::cout << "\nUpdated Item:\n";
    item2.displayInfo();
    
    // Test getters
    std::cout << "\nGetters Test:\n";
    std::cout << "Title: " << item2.getTitle() << "\n";
    std::cout << "Author: " << item2.getAuthor() << "\n";
    std::cout << "Page Count: " << item2.getPageCount() << "\n";
    std::cout << "Binding Type: " << item2.getBindingType() << "\n";
    std::cout << "Is Borrowed: " << (item2.getisBorrowed() ? "Yes" : "No") << "\n";
    
    return 0;
}