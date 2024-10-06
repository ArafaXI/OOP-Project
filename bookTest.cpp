#include <iostream>
#include "Book.h"

void testDefaultConstructor() {
    Book book;
    std::cout << "Testing Default Constructor:\n";
    book.displayInfo();
    std::cout << "Expected: All fields should be empty or zero.\n\n";
}

void testParameterizedConstructor() {
    Book book("The Great Gatsby", "F. Scott Fitzgerald", 180, "Hardcover", "Fiction", "1925-04-10");
    std::cout << "Testing Parameterized Constructor:\n";
    book.displayInfo();
    std::cout << "Expected: Title = 'The Great Gatsby', Author = 'F. Scott Fitzgerald', Page Count = 180, "
                 "Binding Type = 'Hardcover', Genre = 'Fiction', Publication Date = '1925-04-10'.\n\n";
}

void testGettersAndSetters() {
    Book book;
    book.setTitle("1984");
    book.setAuthor("George Orwell");
    book.setPageCount(328);
    book.setBindingType("Paperback");
    book.setGenre("Dystopian");
    book.setPublicationDate("1949-06-08");
    
    std::cout << "Testing Getters and Setters:\n";
    std::cout << "Title: " << book.getTitle() << " (Expected: 1984)\n";
    std::cout << "Author: " << book.getAuthor() << " (Expected: George Orwell)\n";
    std::cout << "Page Count: " << book.getPageCount() << " (Expected: 328)\n";
    std::cout << "Binding Type: " << book.getBindingType() << " (Expected: Paperback)\n";
    std::cout << "Genre: " << book.getGenre() << " (Expected: Dystopian)\n";
    std::cout << "Publication Date: " << book.getPublicationDate() << " (Expected: 1949-06-08)\n\n";
}

void testBorrowing() {
    Book book("The Catcher in the Rye", "J.D. Salinger", 277, "Paperback", "Fiction", "1951-07-16");
    
    std::cout << "Testing Borrowing Status:\n";
    std::cout << "Before borrowing, Is Borrowed: " << (book.getisBorrowed() ? "Yes" : "No") << " (Expected: No)\n";
    book.Borrow(true); // Simulating borrowing
    std::cout << "After borrowing, Is Borrowed: " << (book.getisBorrowed() ? "Yes" : "No") << " (Expected: Yes)\n\n";
}

int main() {
    testDefaultConstructor();
    testParameterizedConstructor();
    testGettersAndSetters();
    testBorrowing();

    return 0;
}