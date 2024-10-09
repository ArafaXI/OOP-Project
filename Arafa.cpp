#include <ncurses.h>

#include <iostream>
#include <limits>  // for error handling
#include <string>
#include <vector>

#include "Book.h"
#include "Ebook.h"
#include "Library.h"
#include "Magazine.h"
#include "Member.h"

// to compile: g++ -o ncursus Arafa.cpp Member.cpp Magazine.cpp Book.cpp
// Ebook.cpp PrintedItem.cpp DigitalItem.cpp Item.cpp Library.cpp -lncurses to
// run:
// ./Arafa

int main() {
  initscr();  // Start ncurses mode
  Library* library = new Library();
  int choice = 0;  // Variable to store the user's choice

  while (true) {
    clear();  // Clear the screen

    // Get the terminal size
    int maxY, maxX;
    getmaxyx(stdscr, maxY, maxX);  // Get the number of rows and columns

    // Draw an Ascii book on the left
    mvprintw(maxY/2 - 5, 0 , R"(
        _.-"\
    _.-"     \
 ,-"          \
( \            \
 \ \            \
  \ \            \
   \ \         _.-;
    \ \    _.-"   :
     \ \,-"    _.-"
      \(   _.-"  -shimrod
       `--")");

           // Draw an Ascii book on the right
    mvprintw(maxY/2 - 5, 20 , R"(
        _.-"\
    _.-"     \
 ,-"          \
( \            \
 \ \            \
  \ \            \
   \ \         _.-;
    \ \    _.-"   :
     \ \,-"    _.-"
      \(   _.-"  
       `--")");

    

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
    if (scanw("%d", &choice) !=
        1) {  // Check if input is a valid integer for error handling
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
        std::string name = nameBuffer;  // converts to string

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
        library->addMember(new Member(name, memberID));
        mvprintw(maxY / 2, (maxX - 15) / 2, "Member added successfully!\n");

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
              clear();  // Clear the screen for adding a magazine
              mvprintw(maxY / 2 - 6, (maxX - 26) / 2, "Enter Magazine title: ");

              char title[50];
              getstr(title);  // Get magazine title

              mvprintw(maxY / 2 - 4, (maxX - 26) / 2,
                       "Enter Magazine author: ");

              char author[50];
              getstr(author);  // Get magazine author

              mvprintw(maxY / 2 - 2, (maxX - 26) / 2, "Enter Page count: ");

              int pageCount;
              scanw("%d", &pageCount);  // Get page count

              mvprintw(maxY / 2, (maxX - 26) / 2,
                       "Enter Binding type (e.g., Hardcover, Paperback): ");

              char bindingType[50];
              getstr(bindingType);  // Get binding type

              mvprintw(maxY / 2 + 2, (maxX - 26) / 2,
                       "Enter Publication date (e.g., 01/01/2023): ");

              char publicationDate[50];
              getstr(publicationDate);  // Get publication date

              mvprintw(maxY / 2 + 4, (maxX - 26) / 2, "Enter Issue number: ");

              int issueNumber;
              scanw("%d", &issueNumber);  // Get issue number

              // Now create the Magazine object using the input values
              Magazine* newMagazine = new Magazine(
                  title, author, pageCount, bindingType, publicationDate,
                  issueNumber);  // Use the constructor with all 6 arguments

              // Add the magazine to the library
              library->addItem(newMagazine);

              mvprintw(maxY / 2 + 6, (maxX - 26) / 2,
                       "Magazine added successfully!\nPress any key to return "
                       "to the menu.");
              getch();  // Wait for the user to press a key
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

        Member** members =
            library
                ->getMemberList();  // Assuming getMemberList() returns Member**
        int numMembers = library->getMemberSize();  // Get the number of members

        mvprintw(maxY / 2 - 5, (maxX - 15) / 2, "List of Members:");

        if (numMembers == 0) {
          mvprintw(maxY / 2 - 3, (maxX - 30) / 2,
                   "No members found in the library.");
        } else {
          for (int i = 0; i < numMembers; i++) {
            mvprintw(maxY / 2 - 3 + i, (maxX - 50) / 2,
                     "Member %d: Name: %s, ID: %d", i + 1,
                     members[i]->getName().c_str(), members[i]->getID());
          }
        }

        mvprintw(maxY / 2 + numMembers + 1, (maxX - 24) / 2,
                 "Press any key to go back...");
        refresh();  // Show all the updated output on the screen
        getch();    // Wait for the user to press a key
        break;
      }
      case 4: {
        int itemChoice;  // Variable to store the item choice
        while (true) {
          clear();

          Item** items =
              library->getItemList();  // Assuming getItemList() returns Item**
          int numItems = library->getItemSize();  // Get the number of items

          mvprintw(maxY / 2 + 6, (maxX - 26) / 2, "List of Items:\n");

          if (numItems == 0) {
            mvprintw(maxY / 2 - 3, (maxX - 30) / 2,
                     "No items found in the library.");
          } else {
            for (int i = 0; i < numItems; i++) {
              std::string itemType;

              // Determine the type of the item
              if (dynamic_cast<Book*>(items[i])) {
                itemType = "Book";
              } else if (dynamic_cast<Magazine*>(items[i])) {
                itemType = "Magazine";
              } else if (dynamic_cast<Ebook*>(items[i])) {
                itemType = "Ebook";
              } else {
                itemType = "Unknown";  // Fallback for safety
              }

              // Print item details including type
              mvprintw(maxY / 2 - 3 + i, (maxX - 60) / 2, "%d. [%s] %s by %s",
                       i + 1, itemType.c_str(), items[i]->getTitle().c_str(),
                       items[i]->getAuthor().c_str());
            }
          }

          // Ask the user to select an item to view more details or 0 to go back
          mvprintw(maxY / 2 + numItems + 1, (maxX - 30) / 2,
                   "Enter the item number to view details or 0 to go back: ");
          refresh();

          scanw("%d", &itemChoice);  // Read the user's choice for item number

          if (itemChoice == 0) {
            break;  // Exit the loop to go back to the main menu
          } else if (itemChoice > 0 && itemChoice <= numItems) {
            clear();
            Item* selectedItem =
                items[itemChoice - 1];  // Get the selected item

            // Display detailed information based on the item type
            mvprintw(maxY / 2 - 5, (maxX - 40) / 2, "Item Details:\n");
            mvprintw(maxY / 2 - 4, (maxX - 50) / 2, "Title: %s",
                     selectedItem->getTitle().c_str());
            mvprintw(maxY / 2 - 3, (maxX - 50) / 2, "Author: %s",
                     selectedItem->getAuthor().c_str());

            // You can extend this to include more specific details
            if (dynamic_cast<Book*>(selectedItem)) {
              Book* book = dynamic_cast<Book*>(selectedItem);
              mvprintw(maxY / 2 - 2, (maxX - 50) / 2, "Page Count: %d",
                       book->getPageCount());
              mvprintw(maxY / 2 - 1, (maxX - 50) / 2, "Binding Type: %s",
                       book->getBindingType().c_str());
              mvprintw(maxY / 2, (maxX - 50) / 2, "Genre: %s",
                       book->getGenre().c_str());
              mvprintw(maxY / 2 + 1, (maxX - 50) / 2, "Publication Date: %s",
                       book->getPublicationDate().c_str());
            } else if (dynamic_cast<Magazine*>(selectedItem)) {
              Magazine* magazine = dynamic_cast<Magazine*>(selectedItem);
              mvprintw(maxY / 2 - 2, (maxX - 50) / 2, "Issue Number: %d",
                       magazine->getIssueNumber());
              mvprintw(maxY / 2 - 1, (maxX - 50) / 2, "Page Count: %d",
                       magazine->getPageCount());
              mvprintw(maxY / 2, (maxX - 50) / 2, "Binding Type: %s",
                       magazine->getBindingType().c_str());
              mvprintw(maxY / 2 + 1, (maxX - 50) / 2, "Publication Date: %s",
                       magazine->getPublicationDate().c_str());
            } else if (dynamic_cast<Ebook*>(selectedItem)) {
              Ebook* ebook = dynamic_cast<Ebook*>(selectedItem);
              mvprintw(maxY / 2 - 2, (maxX - 50) / 2, "File Size: %d MB",
                       ebook->getfileSize());
              mvprintw(maxY / 2 - 1, (maxX - 50) / 2, "Format: %s",
                       ebook->getFormat().c_str());
              mvprintw(maxY / 2, (maxX - 50) / 2, "Genre: %s",
                       ebook->getGenre().c_str());
              mvprintw(maxY / 2 + 1, (maxX - 50) / 2, "Publication Date: %s",
                       ebook->getPublicationDate().c_str());
            }

            mvprintw(maxY / 2 + 2, (maxX - 30) / 2,
                     "Press any key to go back...");
            refresh();
            getch();  // Wait for the user to press a key
          } else {
            // Invalid choice
            mvprintw(maxY / 2 + numItems + 3, (maxX - 30) / 2,
                     "Invalid choice! Press any key to try again...");
            refresh();
            getch();  // Wait for the user to press a key
          }
        }

        break;  // Exit the case to return to the main menu
      }
      case 5: {
        // Get the number of members and items
        int memberCount =
            library->getMemberSize();            // Method to get member count
        int itemCount = library->getItemSize();  // Method to get item count

        // Create arrays to store member and item pointers
        Member** membersArray = new Member*[memberCount];
        Item** itemsArray = new Item*[itemCount];

        // Populate member and item arrays
        for (int i = 0; i < memberCount; ++i) {
          membersArray[i] = library->getMemberList()[i];
        }
        for (int j = 0; j < itemCount; ++j) {
          itemsArray[j] = library->getItemList()[j];
        }

        // Member Selection Submenu
        int memberIndex = -1;
        while (true) {
          clear();  // Clear screen for the submenu
          mvprintw(maxY / 2 - 6, (maxX - 30) / 2,
                   "Select a member to borrow an item:");
          for (int i = 0; i < memberCount; ++i) {
            mvprintw(maxY / 2 - 5 + i, (maxX - 30) / 2, "%d: %s (ID: %d)",
                     i + 1, membersArray[i]->getName().c_str(),
                     membersArray[i]->getID());
          }

          // Get user input for member selection
          mvprintw(maxY / 2 + memberCount - 4, (maxX - 30) / 2,
                   "Enter member index (or 0 to go back): ");
          scanw("%d", &memberIndex);

          if (memberIndex == 0) {
            break;  // Go back to main menu
          }

          // Validate member index
          if (memberIndex < 1 || memberIndex > memberCount) {
            mvprintw(maxY / 2 + memberCount - 3, (maxX - 30) / 2,
                     "Invalid member index!\nPress any key to try again.");
            getch();
            continue;
          }

          memberIndex--;  // Adjust index to zero-based

          // Item Selection Submenu
          int itemIndex = -1;
          while (true) {
            clear();  // Clear screen for item selection
            mvprintw(maxY / 2 - 6, (maxX - 30) / 2,
                     "Select an item to borrow:");
            for (int j = 0; j < itemCount; ++j) {
              mvprintw(maxY / 2 - 5 + j, (maxX - 30) / 2, "%d: %s (Author: %s)",
                       j + 1, itemsArray[j]->getTitle().c_str(),
                       itemsArray[j]->getAuthor().c_str());
            }

            // Get user input for item selection
            mvprintw(maxY / 2 + itemCount - 4, (maxX - 30) / 2,
                     "Enter item index (or 0 to go back): ");
            scanw("%d", &itemIndex);

            if (itemIndex == 0) {
              break;  // Go back to member selection
            }

            // Validate item index
            if (itemIndex < 1 || itemIndex > itemCount) {
              mvprintw(maxY / 2 + itemCount - 3, (maxX - 30) / 2,
                       "Invalid item index!\nPress any key to try again.");
              getch();
              continue;
            }

            itemIndex--;  // Adjust index to zero-based

            // Call borrowItem function for the selected member and item
            membersArray[memberIndex]->borrowItem(itemsArray[itemIndex]);

            mvprintw(
                maxY / 2 + itemCount - 2, (maxX - 30) / 2,
                "Item borrowed successfully!\nPress any key to continue...");
            getch();  // Wait for user input
            break;    // Exit after item borrowing
          }

          if (itemIndex == 0) {
            continue;  // Go back to member selection
          }
          break;  // Exit after borrowing
        }

        // Clean up dynamic arrays
        delete[] membersArray;
        delete[] itemsArray;

        break;
      }
      case 6: {
        // Get the number of members
        int memberCount = library->getMemberSize();  // Assuming you have a
                                                     // method to get the count

        // Create dynamic arrays to store member pointers
        Member** membersArray = new Member*[memberCount];

        // Store members in the dynamic array
        for (int i = 0; i < memberCount; ++i) {
          membersArray[i] = library->getMemberList()[i];
        }

        // Member Selection Submenu
        int memberIndex = -1;
        while (true) {
          clear();  // Clear the screen for the submenu
          mvprintw(maxY / 2 - 6, (maxX - 30) / 2,
                   "Select a member to return an item:");
          for (int i = 0; i < memberCount; ++i) {
            mvprintw(maxY / 2 - 5 + i, (maxX - 30) / 2, "%d: %s (ID: %d)",
                     i + 1, membersArray[i]->getName().c_str(),
                     membersArray[i]->getID());
          }

          // Get user input for member selection
          mvprintw(maxY / 2 + memberCount - 4, (maxX - 30) / 2,
                   "Enter member index (or 0 to go back): ");
          scanw("%d", &memberIndex);

          if (memberIndex == 0) {
            break;  // Go back to main menu
          }

          // Validate member index
          if (memberIndex < 1 || memberIndex > memberCount) {
            mvprintw(maxY / 2 + memberCount - 3, (maxX - 30) / 2,
                     "Invalid member index!\nPress any key to try again.");
            getch();
            continue;
          }

          memberIndex--;  // Adjust index to zero-based

          // Get borrowed items from the selected member
          Item** borrowedItems = membersArray[memberIndex]->getBorrowedItems();
          int borrowedSize =
              membersArray[memberIndex]
                  ->getBorrowedSize();  // Get the number of borrowed items

          // Item Selection Submenu
          int itemIndex = -1;
          while (true) {
            clear();  // Clear screen for item selection
            mvprintw(maxY / 2 - 6, (maxX - 30) / 2,
                     "Select an item to return:");
            for (int j = 0; j < borrowedSize; j++) {
              mvprintw(maxY / 2 - 5 + j, (maxX - 30) / 2, "%d: %s (Author: %s)",
                       j + 1, borrowedItems[j]->getTitle().c_str(),
                       borrowedItems[j]->getAuthor().c_str());
            }

            // Get user input for item selection
            mvprintw(maxY / 2 + borrowedSize - 4, (maxX - 30) / 2,
                     "Enter item index (or 0 to go back): ");
            scanw("%d", &itemIndex);

            if (itemIndex == 0) {
              break;  // Go back to member selection
            }

            // Validate item index
            if (itemIndex < 1 || itemIndex > borrowedSize) {
              mvprintw(maxY / 2 + borrowedSize - 3, (maxX - 30) / 2,
                       "Invalid item index!\nPress any key to try again.");
              getch();
              continue;
            }

            itemIndex--;  // Adjust index to zero-based

            // Call returnItem function for the selected member and item
            membersArray[memberIndex]->returnItem(borrowedItems[itemIndex]);

            mvprintw(
                maxY / 2 + borrowedSize - 2, (maxX - 30) / 2,
                "Item returned successfully!\nPress any key to continue...");
            getch();  // Wait for user input
            break;    // Exit after item return
          }

          if (itemIndex == 0) {
            continue;  // Go back to member selection
          }
          break;  // Exit after item return
        }

        // Clean up dynamic arrays
        delete[] membersArray;

        break;
      }
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

        mvprintw(maxY / 2 + numMembers + 4, (maxX - 24) / 2,
                 "Press any key to return to the main menu.");
        refresh();  // Show all the updated output on the screen
        getch();    // Wait for the user to press a key
        break;
      }
      case 8: {
        clear();
        Item** items =
            library->getItemList();  // Assuming getItemList() returns Item**
        int numItems = library->getItemSize();  // Get the number of items

        if (numItems == 0) {
          mvprintw(maxY / 2 - 3, (maxX - 30) / 2,
                   "No items found in the library.");
        } else {
          mvprintw(maxY / 2 - 5, (maxX - 15) / 2, "Select a item to remove:");
          for (int i = 0; i < numItems; i++) {
            mvprintw(maxY / 2 - 3 + i, (maxX - 50) / 2, "%d. ( %s ) by ( %s )",
                     i + 1, items[i]->getTitle().c_str(),
                     items[i]->getAuthor().c_str());
          }
          mvprintw(maxY / 2 + numItems, (maxX - 35) / 2,
                   "Enter the index of the item to remove: ");
          refresh();

          int itemIndex = -1;
          scanw("%d", &itemIndex);  // Read the index input

          if (itemIndex < 1 || itemIndex > numItems) {
            mvprintw(maxY / 2 + numItems + 2, (maxX - 30) / 2,
                     "Invalid index! Press any key to go back.");
          } else {
            // Remove the selected member (subtract 1 to match 0-based index)
            library->removeItem(itemIndex - 1);
            mvprintw(maxY / 2 + numItems + 2, (maxX - 30) / 2,
                     "Item removed successfully!");
          }
        }

        mvprintw(maxY / 2 + numItems + 4, (maxX - 24) / 2,
                 "Press any key to return to the main menu.");
        refresh();  // Show all the updated output on the screen
        getch();    // Wait for the user to press a key
        break;
      }
      case 9:
        // Exit the program
        endwin();        // End ncurses mode
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