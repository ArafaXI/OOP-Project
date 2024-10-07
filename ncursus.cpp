#include <ncurses.h>
#include <iostream>
#include <string>
#include <limits> // For std::numeric_limits

#include "Library.h"
#include "Member.h"
#include "Book.h"

// to compile: g++ -o ncursus ncursus.cpp Magazine.cpp Book.cpp Ebook.cpp PrintedItem.cpp DigitalItem.cpp Item.cpp Library.cpp -lncurses
// to run: ./ncursus

int main() {
    initscr();            // Start ncurses mode
    cbreak();             // Disable line buffering
    Library* library = new Library();
    int choice = 0;      // Variable to store the user's choice

    while (true) {
        clear(); // Clear the screen

        // Display the main menu
        printw("Library Management System Menu:\n");
        printw("1. Add Member\n");
        printw("2. Add Item\n");
        printw("3. Display Members\n");
        printw("4. Display Items\n");
        printw("5. Borrow Item\n");
        printw("6. Return Item\n");
        printw("7. Remove Member\n");
        printw("8. Remove Item\n");
        printw("9. Exit\n");
        printw("Please enter your choice (1-9): ");
        refresh(); // Refresh to show the output

        scanw("%d", &choice); // Read an integer input from the user

        // Handle the user's choice
        switch (choice) {
            case 1:
                printw("Add Member functionality not implemented yet.\n");
                break;
            case 2: {
                int itemChoice = 0; // Variable to store the item choice
                while (true) {
                    clear(); // Clear the screen

                    // Display the submenu for adding items
                    printw("What kind of item are you adding?\n");
                    printw("1. Book\n");
                    printw("2. Magazine\n");
                    printw("3. Ebook\n");
                    printw("4. Go back to main menu\n");
                    printw("Please enter your choice (1-4): ");
                    refresh(); // Refresh to show the output

                    scanw("%d", &itemChoice); // Read the user's choice for item type

                    switch (itemChoice) {
                        case 1: {
                            // Prompt for Book attributes
                            clear();
                            printw("Enter Book Title: ");
                            refresh();
                            char title[100];
                            scanw("%s", title); // Read title

                            printw("Enter Book Author: ");
                            refresh();
                            char author[100];
                            scanw("%s", author); // Read author

                            int pageCount;
                            while (true) { // Loop until valid input is received
                                printw("Enter Page Count: ");
                                refresh();
                                if (scanw("%d", &pageCount) == 1) { // Check if input is an integer
                                    if (pageCount > 0) break; // Valid integer
                                    else printw("Page count must be a positive integer. Please try again.\n");
                                } else {
                                    printw("Invalid input! Please enter a valid integer for page count.\n");
                                    // Clear input buffer
                                    while (getch() != '\n');
                                }
                            }

                            printw("Enter Binding Type: ");
                            refresh();
                            char bindingType[50];
                            scanw("%s", bindingType); // Read binding type

                            printw("Enter Genre: ");
                            refresh();
                            char genre[50];
                            scanw("%s", genre); // Read genre

                            printw("Enter Publication Date: ");
                            refresh();
                            char publicationDate[50];
                            scanw("%s", publicationDate); // Read publication date

                            // Create a Book object and set its attributes
                            Book* newBook = new Book(title, author, pageCount, bindingType, genre, publicationDate);
                            library ->addItem(newBook);
                            printw("Book added successfully:\n");

                            break;
                        }
                        case 2:
                            printw("Adding a Magazine (functionality not implemented yet).\n");
                            break;
                        case 3:
                            printw("Adding an Ebook (functionality not implemented yet).\n");
                            break;
                        case 4:
                            goto mainMenu; // Go back to the main menu
                        default:
                            printw("Invalid choice! Please try again.\n");
                            break;
                    }

                    // Wait for user input before going back to the submenu
                    printw("Press any key to continue...");
                    refresh();
                    getch(); // Wait for user input
                }
                mainMenu: // Label to jump back to the main menu
                break;
            }
            case 3:
                printw("Display Members functionality not implemented yet.\n");
                break;
            case 4:
                printw("Display Items functionality not implemented yet.\n");
                break;
            case 5:
                printw("Borrow Item functionality not implemented yet.\n");
                break;
            case 6:
                printw("Return Item functionality not implemented yet.\n");
                break;
            case 7:
                printw("Remove Member functionality not implemented yet.\n");
                break;
            case 8:
                printw("Remove Item functionality not implemented yet.\n");
                break;
            case 9:
                printw("Exiting...\n");
                endwin(); // End ncurses mode
                return 0; // Exit the program
            default:
                printw("Invalid choice! Please try again.\n");
                break;
        }

        // Wait for user input before going back to the menu
        printw("Press any key to continue...");
        refresh();
        getch(); // Wait for user input
    }

    // delete the library, and every other dynamically allocated object along with it
    delete library;
    endwin(); // End ncurses mode
    return 0;
}