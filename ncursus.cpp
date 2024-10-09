#include <ncurses.h>

#include <iostream>
#include <limits>  // For std::numeric_limits
#include <string>
#include <vector>

#include "Book.h"
#include "Ebook.h"  // Include your Ebook header
#include "Library.h"
#include "Magazine.h"  // Include your Magazine header
#include "Member.h"

// to compile: g++ -o ncursus ncursus.cpp Magazine.cpp Book.cpp Ebook.cpp PrintedItem.cpp DigitalItem.cpp Item.cpp Library.cpp -lncurses
// to run: ./ncursus

int main() {
    initscr();  // Start ncurses mode
    cbreak();   // Disable line buffering
    Library* library = new Library();
    int choice = 0;  // Variable to store the user's choice

  while (true) {
    clear();  // Clear the screen

    // Get the terminal size
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);  // Get the number of rows and columns

    // Draw the pillars on the left (column 0) and right (column maxX - 1)
    for (int i = 0; i < maxY; i++) {
      mvprintw(i, 30, "|");         // Left pillar at column 0
      mvprintw(i, maxX - 29, "|");  // Right pillar at column maxX - 1
    }

    // Centering the menu title
    std::string title = "Library Management System Menu:";
    mvprintw(maxY / 2 - 5, (maxX - title.length()) / 2, "%s", title.c_str());

    // Centering the menu options
    std::string options[] = {
        "1. Add Member",    "2. Add Item",    "3. Display Members",
        "4. Display Items", "5. Borrow Item", "6. Return Item",
        "7. Remove Member", "8. Remove Item", "9. Exit"};

    for (int i = 0; i < 9; i++) {
      mvprintw(maxY / 2 - 4 + i, (maxX - options[i].length()) / 2, "%s",
               options[i].c_str());
    }

    mvprintw(maxY / 2 + 5, (maxX - 31) / 2, "Please enter your choice (1-9): ");
    refresh();  // Refresh to show the output

        // Read an integer input from the user with error handling
        if (scanw("%d", &choice) != 1) {  // Check if input is a valid integer
            mvprintw(maxY / 2 + 6, (maxX - 36) / 2,
                     "Invalid input! Please enter a number between 1 and 9.\n");
            choice = 0;  // Reset choice to avoid executing any cases
            while (getch() != '\n')
                ;        // Clear input buffer until newline
            continue;  // Skip to the next iteration of the loop
        }

    // Handle the user's choice
    switch (choice) {
      case 1: {
        // Prompt for member name
        clear();
        mvprintw(maxY / 2 - 5, (maxX - 15) / 2, "Enter Member's name: ");
        refresh();
        char nameBuffer[100];
        scanw("%s", nameBuffer);        // Read title
        std::string name = nameBuffer;  // Convert to std::string

                            int memberID;
                            while (true) {  // Loop until valid input is received
                                mvprintw(maxY / 2 - 3, (maxX - 15) / 2, "Enter Member's ID: ");
                                refresh();
                                if (scanw("%d", &memberID) == 1 && memberID > 0) {
                                    break;  // Valid integer
                                } else {
                                    mvprintw(maxY / 2 - 1, (maxX - 52) / 2,
                                             "Invalid input! Please enter a valid positive "
                                             "integer for member's ID.\n");
                                    // Clear input buffer
                                    while (getch() != '\n')
                                        ;
                                }
                            }
                            library -> addMember(new Member(name, memberID));
                            mvprintw(maxY / 2 , (maxX - 15) / 2,
                                     "Member added successfully!\n");

        break;
        break;
      }
      case 2: {
        int itemChoice = 0;  // Variable to store the item choice
        while (true) {
          clear();  // Clear the screen

          // Centering the submenu for adding items
          mvprintw(maxY / 2 - 5, (maxX - 33) / 2,
                   "What kind of item are you adding?");
          std::string itemOptions[] = {"1. Book", "2. Magazine", "3. Ebook",
                                       "4. Go back to main menu"};

          for (int i = 0; i < 4; i++) {
            mvprintw(maxY / 2 - 4 + i, (maxX - itemOptions[i].length()) / 2,
                     "%s", itemOptions[i].c_str());
          }

          mvprintw(maxY / 2 + 5, (maxX - 31) / 2,
                   "Please enter your choice (1-4): ");
          refresh();  // Refresh to show the output

          scanw("%d", &itemChoice);  // Read the user's choice for item type

          switch (itemChoice) {
            case 1: {
              // Prompt for Book attributes
              clear();
              mvprintw(maxY / 2 - 5, (maxX - 15) / 2, "Enter Book Title: ");
              refresh();
              char titleBuffer[100];
              scanw("%s", titleBuffer);         // Read title
              std::string title = titleBuffer;  // Convert to std::string

              mvprintw(maxY / 2 - 4, (maxX - 17) / 2, "Enter Book Author: ");
              refresh();
              char authorBuffer[100];
              scanw("%s", authorBuffer);          // Read author
              std::string author = authorBuffer;  // Convert to std::string

                            int pageCount;
                            while (true) {  // Loop until valid input is received
                                mvprintw(maxY / 2 - 3, (maxX - 18) / 2, "Enter Page Count: ");
                                refresh();
                                if (scanw("%d", &pageCount) == 1 && pageCount > 0) {
                                    break;  // Valid integer
                                } else {
                                    mvprintw(maxY / 2 - 2, (maxX - 52) / 2,
                                             "Invalid input! Please enter a valid positive "
                                             "integer for page count.\n");
                                    // Clear input buffer
                                    while (getch() != '\n')
                                        ;
                                }
                            }

              mvprintw(maxY / 2 - 1, (maxX - 19) / 2, "Enter Binding Type: ");
              refresh();
              char bindingTypeBuffer[50];
              scanw("%s", bindingTypeBuffer);  // Read binding type
              std::string bindingType =
                  bindingTypeBuffer;  // Convert to std::string

              mvprintw(maxY / 2, (maxX - 13) / 2, "Enter Genre: ");
              refresh();
              char genreBuffer[50];
              scanw("%s", genreBuffer);         // Read genre
              std::string genre = genreBuffer;  // Convert to std::string

              mvprintw(maxY / 2 + 1, (maxX - 26) / 2,
                       "Enter Publication Date: ");
              refresh();
              char publicationDateBuffer[50];
              scanw("%s", publicationDateBuffer);  // Read publication date
              std::string publicationDate =
                  publicationDateBuffer;  // Convert to std::string

              // Create a Book object and set its attributes
              Book* newBook = new Book(title, author, pageCount, bindingType,
                                       genre, publicationDate);
              library->addItem(newBook);
              mvprintw(maxY / 2 + 2, (maxX - 26) / 2,
                       "Book added successfully:\n");

                            break;
                        }
                        case 2: {
                            // Prompt for Magazine attributes
                            clear();
                            mvprintw(maxY / 2 - 5, (maxX - 30) / 2, "Enter Magazine Title: ");
                            refresh();
                            char magazineTitleBuffer[100];
                            scanw("%s", magazineTitleBuffer);  // Read magazine title
                            std::string magazineTitle = magazineTitleBuffer;

                            mvprintw(maxY / 2 - 4, (maxX - 40) / 2, "Enter Issue Number: ");
                            refresh();
                            int issueNumber;
                            scanw("%d", &issueNumber);  // Read issue number

                            mvprintw(maxY / 2 - 3, (maxX - 30) / 2, "Enter Page Count: ");
                            refresh();
                            int magazinePageCount;
                            scanw("%d", &magazinePageCount);  // Read page count

                            mvprintw(maxY / 2 - 2, (maxX - 30) / 2, "Enter Binding Type: ");
                            refresh();
                            char magazineBindingTypeBuffer[50];
                            scanw("%s", magazineBindingTypeBuffer);  // Read binding type
                            std::string magazineBindingType = magazineBindingTypeBuffer;  // Convert to std::string

                            mvprintw(maxY / 2 - 1, (maxX - 30) / 2,
                                     "Enter Publication Date: ");
                            refresh();
                            char magazinePubDateBuffer[50];
                            scanw("%s", magazinePubDateBuffer);  // Read publication date
                            std::string magazinePubDate = magazinePubDateBuffer;  // Convert to std::string

                            // Create a Magazine object and set its attributes
                            Magazine* newMagazine = new Magazine(
                                magazineTitle, "Unknown Author", magazinePageCount,
                                magazineBindingType, magazinePubDate, issueNumber);
                            library->addItem(newMagazine);
                            mvprintw(maxY / 2 + 2, (maxX - 26) / 2,
                                     "Magazine added successfully:\n");

                            break;
                        }
                        case 3: {
                            // Prompt for Ebook attributes
                            clear();
                            mvprintw(maxY / 2 - 5, (maxX - 30) / 2, "Enter Ebook Title: ");
                            refresh();
                            char ebookTitleBuffer[100];
                            scanw("%s", ebookTitleBuffer);  // Read ebook title
                            std::string ebookTitle = ebookTitleBuffer;

              mvprintw(maxY / 2 - 4, (maxX - 40) / 2, "Enter Author: ");
              refresh();
              char ebookAuthorBuffer[100];
              scanw("%s", ebookAuthorBuffer);  // Read ebook author
              std::string ebookAuthor = ebookAuthorBuffer;

              mvprintw(maxY / 2 - 3, (maxX - 40) / 2, "Enter File Size (MB): ");
              refresh();
              float fileSize;
              scanw("%f", &fileSize);  // Read file size

              mvprintw(maxY / 2 - 2, (maxX - 40) / 2, "Enter Format: ");
              refresh();
              char ebookFormatBuffer[50];
              scanw("%s", ebookFormatBuffer);  // Read ebook format
              std::string ebookFormat = ebookFormatBuffer;

              mvprintw(maxY / 2 - 1, (maxX - 40) / 2, "Enter Ebook Genre: ");
              refresh();
              char ebookGenreBuffer[100];
              scanw("%s", ebookGenreBuffer);  // Read genre
              std::string ebookGenre = ebookGenreBuffer;

              mvprintw(maxY / 2, (maxX - 40) / 2, "Enter Publication Date: ");

              refresh();
              char ebookPubDatebuffer[100];
              scanw("%s", ebookPubDatebuffer);  // Read publicatiom date
              std::string ebookPubDate = ebookPubDatebuffer;

              // Create an Ebook object and set its attributes
              Ebook* newEbook =
                  new Ebook(ebookTitle, ebookAuthor, fileSize, ebookFormat,
                            ebookGenre, ebookPubDate);
              library->addItem(newEbook);
              mvprintw(maxY / 2 + 2, (maxX - 26) / 2,
                       "Ebook added successfully:\n");

              break;
            }
            case 4:
              break;  // Go back to main menu
            default:
              mvprintw(maxY / 2 + 6, (maxX - 30) / 2,
                       "Invalid choice! Please select a valid option.\n");
          }

                    mvprintw(maxY / 2 + 8, (maxX - 24) / 2,
                             "Press any key to continue...");
                    refresh();
                    getch();  // Wait for user to press a key
                    break;
                }
                break;
            }
            case 3: {
    clear();  // Clear the screen before displaying members
    
    Member** members = library->getMemberList();  // Assuming getMemberList() returns Member**
    int numMembers = library->getMemberSize();    // Get the number of members
    
    mvprintw(maxY / 2 - 5, (maxX - 15) / 2, "List of Members:");
    
    if (numMembers == 0) {
        mvprintw(maxY / 2 - 3, (maxX - 30) / 2, "No members found in the library.");
    } else {
        for (int i = 0; i < numMembers; i++) {
            mvprintw(maxY / 2 - 3 + i, (maxX - 50) / 2, "Member %d: Name: %s, ID: %d",
                     i + 1, members[i]->getName().c_str(), members[i]->getID());
        }
    }
    
    mvprintw(maxY / 2 + numMembers + 1, (maxX - 24) / 2, "Press any key to go back...");
    refresh();  // Show all the updated output on the screen
    getch();    // Wait for the user to press a key
    break;
}
            case 4:
                mvprintw(maxY / 2 + 6, (maxX - 26) / 2,
                         "Display Items functionality not implemented yet.\n");
                break;
            case 5:
                mvprintw(maxY / 2 + 6, (maxX - 26) / 2,
                         "Borrow Item functionality not implemented yet.\n");
                break;
            case 6:
                mvprintw(maxY / 2 + 6, (maxX - 26) / 2,
                         "Return Item functionality not implemented yet.\n");
                break;
 case 7: {
    clear();  // Clear the screen before displaying members

        Member** members =
            library
                ->getMemberList();  // Assuming getMemberList() returns Member**
        int numMembers = library->getMemberSize();  // Get the number of members

        if (numMembers == 0) {
          mvprintw(maxY / 2, (maxX - 30) / 2,
                   "No members found in the library.");
        } else {
          mvprintw(maxY / 2 - 5, (maxX - 15) / 2, "Select a member to remove:");

          // Display all members
          for (int i = 0; i < numMembers; i++) {
            mvprintw(maxY / 2 - 4 + i, (maxX - 50) / 2,
                     "Member %d: Name: %s, ID: %d", i + 1,
                     members[i]->getName().c_str(), members[i]->getID());
          }

          mvprintw(maxY / 2 + numMembers, (maxX - 35) / 2,
                   "Enter the index of the member to remove: ");
          refresh();

          int memberIndex = -1;
          scanw("%d", &memberIndex);  // Read the index input

          if (memberIndex < 1 || memberIndex > numMembers) {
            mvprintw(maxY / 2 + numMembers + 2, (maxX - 30) / 2,
                     "Invalid index! Press any key to go back.");
          } else {
            // Remove the selected member (subtract 1 to match 0-based index)
            library->removeMember(memberIndex - 1);
            mvprintw(maxY / 2 + numMembers + 2, (maxX - 30) / 2,
                     "Member removed successfully!");
          }
        }

    mvprintw(maxY / 2 + numMembers + 4, (maxX - 24) / 2, "Press any key to return to the main menu.");
    refresh();  // Show all the updated output on the screen
    getch();    // Wait for the user to press a key
    break;
}
            case 8:
                mvprintw(maxY / 2 + 6, (maxX - 26) / 2,
                         "Remove Item functionality not implemented yet.\n");
                break;
            case 9:
                // Exit the program
                endwin();  // End ncurses mode
                delete library;  // Clean up
                return 0;
            default:
                mvprintw(maxY / 2 + 6, (maxX - 30) / 2,
                         "Invalid choice! Please select a valid option.\n");
        }

    mvprintw(maxY / 2 + 8, (maxX - 24) / 2, "Press any key to continue...");
    refresh();
    getch();  // Wait for user to press a key
  }

  endwin();  // End ncurses mode
  return 0;
}