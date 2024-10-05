#include <iostream>
#include "Ebook.h"

int main() {
    // Test 1: Default Constructor Test
    std::cout << "Test 1: Default Constructor Test\n";
    Ebook ebook1;
    ebook1.displayInfo();
    
    // Test 2: Parameterized Constructor Test
    std::cout << "\nTest 2: Parameterized Constructor Test\n";
    Ebook ebook2("Digital Fortress", "Dan Brown", 5.5, "PDF", "Thriller", "2008");
    ebook2.displayInfo();
    
    // Test 3: Getters and Setters Test
    std::cout << "\nTest 3: Getters and Setters Test\n";
    ebook2.setTitle("The Alchemist");
    ebook2.setAuthor("Paulo Coelho");
    ebook2.setfileSize(3.2);
    ebook2.setFormat("EPUB");
    ebook2.setGenre("Fiction");
    ebook2.setPublicationDate("1988");
    ebook2.Borrow(true);  // Set ebook as borrowed

    // Check values via getters and display them
    std::cout << "Title: " << ebook2.getTitle() << "\n";
    std::cout << "Author: " << ebook2.getAuthor() << "\n";
    std::cout << "File Size: " << ebook2.getfileSize() << "\n";
    std::cout << "Format: " << ebook2.getFormat() << "\n";
    std::cout << "Genre: " << ebook2.getGenre() << "\n";
    std::cout << "Publication Date: " << ebook2.getPublicationDate() << "\n";
    std::cout << "Is Borrowed: " << (ebook2.getisBorrowed() ? "Yes" : "No") << "\n";
    
    // Test 4: Display Info Test
    std::cout << "\nTest 4: Display Info Test\n";
    ebook2.displayInfo();

    // Test 5: Borrowing and Returning Test
    std::cout << "\nTest 5: Borrowing and Returning Test\n";
    ebook2.Borrow(false);  // Return the ebook
    ebook2.displayInfo();  // Display info after returning
    
    return 0;
}
