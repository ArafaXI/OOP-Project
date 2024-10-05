#include <SFML/Graphics.hpp>
#include <iostream>
#include <limits>
#include "Library.h"
#include "Book.h"
#include "Magazine.h"
#include "Member.h"

int main() {
    Library library;

    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Library Management System");

    // Fonts and Text setup
    sf::Font font;
    if (!font.loadFromFile("path/to/your/font.ttf")) { // Adjust the path to your font file
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    sf::Text feedback("", font, 20);
    feedback.setFillColor(sf::Color::White);
    feedback.setPosition(50, 400); // Position feedback text

    // Create buttons for each functionality
    sf::RectangleShape addMemberButton(sf::Vector2f(200, 50));
    addMemberButton.setFillColor(sf::Color::Green);
    addMemberButton.setPosition(50, 50);

    sf::RectangleShape addItemButton(sf::Vector2f(200, 50));
    addItemButton.setFillColor(sf::Color::Blue);
    addItemButton.setPosition(50, 120);

    sf::RectangleShape removeMemberButton(sf::Vector2f(200, 50));
    removeMemberButton.setFillColor(sf::Color::Red);
    removeMemberButton.setPosition(50, 190);

    sf::RectangleShape removeItemButton(sf::Vector2f(200, 50));
    removeItemButton.setFillColor(sf::Color::Yellow);
    removeItemButton.setPosition(50, 260);

    sf::RectangleShape displayMembersButton(sf::Vector2f(200, 50));
    displayMembersButton.setFillColor(sf::Color::Cyan);
    displayMembersButton.setPosition(50, 330);

    sf::RectangleShape displayItemsButton(sf::Vector2f(200, 50));
    displayItemsButton.setFillColor(sf::Color::Magenta);
    displayItemsButton.setPosition(50, 400);

    sf::RectangleShape borrowItemButton(sf::Vector2f(200, 50));
    borrowItemButton.setFillColor(sf::Color::White);
    borrowItemButton.setPosition(300, 50);

    sf::RectangleShape returnItemButton(sf::Vector2f(200, 50));
    returnItemButton.setFillColor(sf::Color::Black);
    returnItemButton.setPosition(300, 120);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                // Check if each button is clicked
                if (addMemberButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    std::string name;
                    int ID;
                    std::cout << "Enter member name: ";
                    std::getline(std::cin, name);
                    std::cout << "Enter member ID: ";
                    while (!(std::cin >> ID)) {
                        std::cout << "Invalid input. Please enter a number for ID: ";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    std::cin.ignore();
                    library.addMember(new Member(name, ID));
                    feedback.setString("Member added successfully!");
                }
                else if (addItemButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    int itemType;
                    std::cout << "Select item type:\n1. Book\n2. Magazine\n";
                    std::cin >> itemType;

                    std::cin.ignore();
                    if (itemType == 1) {
                        std::string title, author, bindingType, genre, publicationDate;
                        int pageCount;

                        std::cout << "Enter title: ";
                        std::getline(std::cin, title);
                        std::cout << "Enter author: ";
                        std::getline(std::cin, author);
                        std::cout << "Enter page count: ";
                        while (!(std::cin >> pageCount)) {
                            std::cout << "Invalid input. Please enter a number for page count: ";
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                        std::cin.ignore();
                        std::cout << "Enter binding type: ";
                        std::getline(std::cin, bindingType);
                        std::cout << "Enter genre: ";
                        std::getline(std::cin, genre);
                        std::cout << "Enter publication date: ";
                        std::getline(std::cin, publicationDate);

                        library.addItem(new Book(title, author, pageCount, bindingType, genre, publicationDate));
                        feedback.setString("Book added successfully!");
                    } else if (itemType == 2) {
                        std::string title, author, bindingType, publicationDate;
                        int pageCount, issueNumber;

                        std::cout << "Enter title: ";
                        std::getline(std::cin, title);
                        std::cout << "Enter author: ";
                        std::getline(std::cin, author);
                        std::cout << "Enter page count: ";
                        while (!(std::cin >> pageCount)) {
                            std::cout << "Invalid input. Please enter a number for page count: ";
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                        std::cin.ignore();
                        std::cout << "Enter binding type: ";
                        std::getline(std::cin, bindingType);
                        std::cout << "Enter issue number: ";
                        while (!(std::cin >> issueNumber)) {
                            std::cout << "Invalid input. Please enter a number for issue number: ";
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                        std::cin.ignore();
                        std::cout << "Enter publication date: ";
                        std::getline(std::cin, publicationDate);

                        library.addItem(new Magazine(title, author, pageCount, bindingType, publicationDate, issueNumber));
                        feedback.setString("Magazine added successfully!");
                    } else {
                        feedback.setString("Invalid item type.");
                    }
                }
                else if (removeMemberButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    int memberId;
                    std::cout << "Enter member ID to remove: ";
                    std::cin >> memberId;
                    library.removeMember(memberId);
                    feedback.setString("Member removed successfully!");
                }
                else if (removeItemButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    int itemId;
                    std::cout << "Enter item ID to remove: ";
                    std::cin >> itemId;
                    library.removeItem(itemId);
                    feedback.setString("Item removed successfully!");
                }
                else if (displayMembersButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    std::cout << "Members in library:\n";
                    library.displayMembers();
                    feedback.setString("Displayed members in console.");
                }
                else if (displayItemsButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    std::cout << "Items in library:\n";
                    library.displayItems();
                    feedback.setString("Displayed items in console.");
                }
                else if (borrowItemButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    int memberId, itemId;
                    std::cout << "Enter member ID: ";
                    std::cin >> memberId;
                    std::cout << "Enter item ID: ";
                    std::cin >> itemId;

                    library.borrowItem(memberId, itemId);
                    feedback.setString("Item borrowed successfully!");
                }
                else if (returnItemButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                    int memberId, itemId;
                    std::cout << "Enter member ID: ";
                    std::cin >> memberId;
                    std::cout << "Enter item ID: ";
                    std::cin >> itemId;

                    library.returnItem(memberId, itemId);
                    feedback.setString("Item returned successfully!");
                }
            }
        }

        window.clear();
        // Draw buttons
        window.draw(addMemberButton);
        window.draw(addItemButton);
        window.draw(removeMemberButton);
        window.draw(removeItemButton);
        window.draw(displayMembersButton);
        window.draw(displayItemsButton);
        window.draw(borrowItemButton);
        window.draw(returnItemButton);
        // Draw feedback
        window.draw(feedback);
        window.display();
    }

    return 0;
}