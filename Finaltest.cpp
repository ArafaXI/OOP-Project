#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Library.h"
#include "Book.h"
#include "Magazine.h"
#include "Ebook.h"
#include "Menu.h"

int main() {
    // Get the desktop mode; screen dimensions
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2i windowPosition((desktop.width - 800) / 2, (desktop.height - 600) / 2);

    // Create the window centered on the screen
    sf::RenderWindow window(sf::VideoMode(800, 600), "Library System");
    window.setPosition(windowPosition);
    window.setVerticalSyncEnabled(true);

    // Load a font for the menu text
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    // Define menu options
    std::vector<std::string> menuOptions = {"Add Item", "Register Member", "All items", "Find an Item", "Exit"};
    Menu menu(&window, menuOptions);

    // Create a button to add the item (for now, this will be simulated with a placeholder)
    sf::RectangleShape addItemButton(sf::Vector2f(200, 50));
    addItemButton.setPosition(250, 440);
    addItemButton.setFillColor(sf::Color::Green);
    sf::Text addItemText("Add Item", font, 24);
    addItemText.setFillColor(sf::Color::White);
    addItemText.setPosition(290, 455);

    // Create a back button to return to the menu
    sf::RectangleShape backButton(sf::Vector2f(200, 50));
    backButton.setPosition(250, 510);
    backButton.setFillColor(sf::Color::Red);
    sf::Text backText("Back", font, 24);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(330, 525);

    // Assuming PrintedItem objects will be stored in a vector or similar container
    std::vector<Item*> itemList;

    bool inAddItemMode = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    if (inAddItemMode) {
                        // Check if the "Add Item" button was clicked
                        if (addItemButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                            std::cout << "Add Item Button Clicked!\n";

                            // Create a new PrintedItem with placeholder details (simulate adding an item)
                            PrintedItem* newItem = new PrintedItem("Placeholder Title", "Placeholder Author", 100, "Paperback");

                            // Add the new item to the itemList
                            itemList.push_back(newItem);

                            // Display the newly added item's information
                            std::cout << "Item added:\n";
                            newItem->displayInfo();

                            // Return to the main menu
                            inAddItemMode = false;
                        }
                        // Check if the "Back" button was clicked
                        else if (backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                            std::cout << "Back Button Clicked!\n";
                            inAddItemMode = false;  // Go back to the main menu
                        }
                    } else {
                        menu.handleMouseClick(mousePos);

                        int selectedItem = menu.getSelectedItem();
                        if (selectedItem != -1) {
                            if (selectedItem == 0) {  // Add Item Selected
                                std::cout << "Add item Selected!\n";
                                inAddItemMode = true;  // Switch to Add Item Mode
                            } else if (selectedItem == 1) {
                                std::cout << "Register Member Selected!\n";
                            } else if (selectedItem == 2) {
                                std::cout << "All items Selected!\n";
                                // Print all items in the list
                                for (auto item : itemList) {
                                    item->displayInfo();
                                }
                            } else if (selectedItem == 3) {
                                std::cout << "Find an Item Selected!\n";
                            } else if (selectedItem == 4) {
                                std::cout << "Exit Selected!\n";
                                window.close();  // Exit the application
                            }
                        }
                    }
                }
            }
        }

        window.clear();

        if (inAddItemMode) {
            // In Add Item Mode, show the add item button and back button
            window.draw(addItemButton);
            window.draw(addItemText);
            window.draw(backButton);
            window.draw(backText);
        } else {
            // In the main menu, display the menu
            menu.draw();
        }

        window.display();
    }

    // Cleanup dynamically allocated items
    for (auto item : itemList) {
        delete item;  // Ensure each item is deleted to avoid memory leaks
    }

    return 0;
}
