#include <iostream>
#include "Magazine.h"

void testDefaultConstructor() {
    Magazine mag;
    std::cout << "Testing Default Constructor:\n";
    mag.displayInfo();
    std::cout << "Expected: \n"
              << "Title: \n"
              << "Author: \n"
              << "Page Count: 0\n"
              << "Binding Type: \n"
              << "Publication Date: \n"
              << "Issue Number: 0\n\n";
}

void testParameterizedConstructor() {
    Magazine mag("National Geographic", "John Doe", 100, "Softcover", "2023-10-05", 42);
    std::cout << "Testing Parameterized Constructor:\n";
    mag.displayInfo();
    std::cout << "Expected: \n"
              << "Title: National Geographic\n"
              << "Author: John Doe\n"
              << "Page Count: 100\n"
              << "Binding Type: Softcover\n"
              << "Publication Date: 2023-10-05\n"
              << "Issue Number: 42\n\n";
}

void testSettersAndGetters() {
    Magazine mag;
    mag.setTitle("Time Magazine");
    mag.setAuthor("Jane Smith");
    mag.setPageCount(50);
    mag.setBindingType("Hardcover");
    mag.setPublicationDate("2023-11-01");
    mag.setIssueNumber(10);

    std::cout << "Testing Setters and Getters:\n";
    std::cout << "Title: " << mag.getTitle() << " (Expected: Time Magazine)\n";
    std::cout << "Author: " << mag.getAuthor() << " (Expected: Jane Smith)\n";
    std::cout << "Page Count: " << mag.getPageCount() << " (Expected: 50)\n";
    std::cout << "Binding Type: " << mag.getBindingType() << " (Expected: Hardcover)\n";
    std::cout << "Publication Date: " << mag.getPublicationDate() << " (Expected: 2023-11-01)\n";
    std::cout << "Issue Number: " << mag.getIssueNumber() << " (Expected: 10)\n\n";
}

void testDisplayInfo() {
    Magazine mag("Forbes", "Alice Brown", 80, "Digital", "2023-10-01", 15);
    std::cout << "Testing displayInfo Method:\n";
    mag.displayInfo();
}

int main() {
    testDefaultConstructor();
    testParameterizedConstructor();
    testSettersAndGetters();
    testDisplayInfo();

    return 0;
}