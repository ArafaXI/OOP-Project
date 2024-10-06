#include <iostream>
#include "Member.h"
#include "Book.h"    
#include "Magazine.h" 

void testDefaultConstructor() {
    Member member;
    std::cout << "Testing Default Constructor:\n";
    std::cout << "Name: " << member.getName() << " (Expected: )\n";
    std::cout << "ID: " << member.getID() << " (Expected: 0)\n";
    std::cout << "Borrowed Size: " << member.getBorrowedSize() << " (Expected: 0)\n\n";
}

void testParameterizedConstructor() {
    Member member("Alice", 1);
    std::cout << "Testing Parameterized Constructor:\n";
    std::cout << "Name: " << member.getName() << " (Expected: Alice)\n";
    std::cout << "ID: " << member.getID() << " (Expected: 1)\n";
    std::cout << "Borrowed Size: " << member.getBorrowedSize() << " (Expected: 0)\n\n";
}

void testSetters() {
    Member member;
    member.setName("Bob");
    member.setID(2);
    
    std::cout << "Testing Setters:\n";
    std::cout << "Name: " << member.getName() << " (Expected: Bob)\n";
    std::cout << "ID: " << member.getID() << " (Expected: 2)\n\n";
}

void testBorrowingAndReturning() {
    Member member("Charlie", 3);
    
    // Create Book and Magazine objects with the correct constructor parameters
    Book book("The Great Gatsby", "F. Scott Fitzgerald", 180, "Hardcover", "Fiction", "1925-04-10");
    Magazine magazine("National Geographic", "Various", 100, "Softcover", "2023-10-05", 42);
    
    // Borrow the items
    member.borrowItem(&book);
    member.borrowItem(&magazine);
    
    std::cout << "Testing Borrowing:\n";
    std::cout << "Borrowed Size: " << member.getBorrowedSize() << " (Expected: 2)\n";
    member.displayBorrowedItems();  // Show borrowed items

    member.returnItem(&book);
    std::cout << "Testing Returning:\n";
    std::cout << "Borrowed Size: " << member.getBorrowedSize() << " (Expected: 1)\n";
    member.displayBorrowedItems();  // Show borrowed items after returning one
}

void testDisplayBorrowedItems() {
    Member member("Dave", 4);
    
    // Create a Book object with the correct constructor parameters
    Book book("1984", "George Orwell", 328, "Paperback", "Dystopian", "1949-06-08");
    
    member.borrowItem(&book);
    std::cout << "Testing displayBorrowedItems Method:\n";
    member.displayBorrowedItems();  // Should prompt to display details of the item
}

int main() {
    testDefaultConstructor();
    testParameterizedConstructor();
    testSetters();
    testBorrowingAndReturning();
    testDisplayBorrowedItems();

    return 0;
}