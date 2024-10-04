#include <limits>  // for input validation

#include "Book.h"
#include "Library.h"
#include "Magazine.h"
#include "Member.h"

int main() {
    Library library;
    int choice;

    while (true) {
        std::cout << "Library Management System\n";
        std::cout << "1. Add Member\n";
        std::cout << "2. Add Item\n";
        std::cout << "3. Display Members\n";
        std::cout << "4. Display Items\n";
        std::cout << "5. Borrow Item\n";
        std::cout << "6. Return Item\n";
        std::cout << "7. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        // Clear the input buffer in case of invalid input
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input, please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                std::string name;
                int ID;
                std::cout << "Enter member name: ";
                std::cin.ignore(); // Clear the newline from the buffer
                std::getline(std::cin, name);  // Allow spaces in name
                std::cout << "Enter member ID: ";
                std::cin >> ID;
                library.addMember(new Member(name, ID)); // Adjusted to match constructor
                std::cout << "Member added successfully.\n";
                break;
            }
            case 2: {
                int itemType;
                std::cout << "Select item type:\n1. Book\n2. Magazine\n";
                std::cin >> itemType;

                if (itemType == 1) {
                    std::string title, author, bindingType, genre, publicationDate;
                    int pageCount;

                    std::cout << "Enter title: ";
                    std::cin.ignore(); // Clear the newline from the buffer
                    std::getline(std::cin, title);  // Allow spaces in title
                    std::cout << "Enter author: ";
                    std::getline(std::cin, author);  // Allow spaces in author

                    // Input validation for page count
                    std::cout << "Enter page count: ";
                    while (!(std::cin >> pageCount)) {
                        std::cout << "Invalid input. Please enter a number for page count: ";
                        std::cin.clear();  // Clear the error flag
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore bad input
                    }

                    std::cout << "Enter binding type: ";
                    std::cin.ignore(); // Clear the newline from the buffer
                    std::getline(std::cin, bindingType);  // Allow spaces in binding type
                    std::cout << "Enter genre: ";
                    std::getline(std::cin, genre);  // Allow spaces in genre
                    std::cout << "Enter publication date: ";
                    std::getline(std::cin, publicationDate);  // Allow spaces in publication date

                    library.addItem(new Book(title, author, pageCount, bindingType, genre, publicationDate));
                    std::cout << "Book added successfully.\n";

                } else if (itemType == 2) {
                    std::string title, author, bindingType, publicationDate;
                    int pageCount, issueNumber;

                    std::cout << "Enter title: ";
                    std::cin.ignore(); // Clear the newline from the buffer
                    std::getline(std::cin, title);  // Allow spaces in title
                    std::cout << "Enter author: ";
                    std::getline(std::cin, author);  // Allow spaces in author

                    // Input validation for page count
                    std::cout << "Enter page count: ";
                    while (!(std::cin >> pageCount)) {
                        std::cout << "Invalid input. Please enter a number for page count: ";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }

                    std::cout << "Enter binding type: ";
                    std::cin.ignore(); // Clear the newline from the buffer
                    std::getline(std::cin, bindingType);  // Allow spaces in binding type

                    // Input validation for issue number
                    std::cout << "Enter issue number: ";
                    while (!(std::cin >> issueNumber)) {
                        std::cout << "Invalid input. Please enter a number for issue number: ";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }

                    std::cout << "Enter publication date: ";
                    std::cin.ignore(); // Clear the newline from the buffer
                    std::getline(std::cin, publicationDate);  // Allow spaces in publication date

                    library.addItem(new Magazine(title, author, pageCount, bindingType, publicationDate, issueNumber));
                    std::cout << "Magazine added successfully.\n";
                } else {
                    std::cout << "Invalid item type.\n";
                }
                break;
            }
            case 3:
                library.displayMembers();
                break;
            case 4:
                library.displayItems();
                break;
            case 5: {
                int memberID;
                std::string itemTitle;
                std::cout << "Enter member ID: ";
                std::cin >> memberID;
                std::cout << "Enter item title to borrow: ";
                std::cin.ignore(); // Clear the newline from the buffer
                std::getline(std::cin, itemTitle);  // Allow spaces in item title
                // Implement the borrowing logic as needed
                break;
            }
            case 6: {
                int memberID;
                std::string itemTitle;
                std::cout << "Enter member ID: ";
                std::cin >> memberID;
                std::cout << "Enter item title to return: ";
                std::cin.ignore(); // Clear the newline from the buffer
                std::getline(std::cin, itemTitle);  // Allow spaces in item title
                // Implement the returning logic as needed
                break;
            }
            case 7:
                std::cout << "Exiting the program.\n";
                return 0;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }
    return 0;
}