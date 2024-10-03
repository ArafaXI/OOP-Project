#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include "Item.h"
#include "PrintedItem.h"
#include "Menu.h"

class TextInput {
public:
    sf::Text text;
    sf::RectangleShape box;
    bool active = false;

    TextInput(float x, float y, const std::string& placeholder, sf::Font& font) {
        // Setup the box
        box.setSize(sf::Vector2f(200, 40));
        box.setPosition(x, y);
        box.setFillColor(sf::Color::White);
        box.setOutlineThickness(2);
        box.setOutlineColor(sf::Color::Black);

        // Setup the text
        text.setFont(font);
        text.setString(placeholder);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x + 10, y + 5);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(box);
        window.draw(text);
    }

    void handleInput(sf::Event& event) {
        if (active && event.type == sf::Event::TextEntered) {
            if (event.text.unicode < 128) {
                if (event.text.unicode == 8 && !inputStr.empty()) {
                    inputStr.pop_back();  // Handle backspace
                } else if (event.text.unicode != 8) {
                    inputStr += static_cast<char>(event.text.unicode);  // Add new character
                }
                // Update the displayed text
                text.setString(inputStr);
            }
        }
    }

    void handleMouseClick(sf::Vector2i mousePos) {
        // Activate or deactivate based on whether the text box was clicked
        if (box.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            activate();
        } else {
            deactivate();
        }
    }

    void activate() {
        active = true;
        box.setOutlineColor(sf::Color::Blue);  // Highlight active box
    }

    void deactivate() {
        active = false;
        box.setOutlineColor(sf::Color::Black);  // Reset outline color
    }

    std::string getInput() const { return inputStr; }

private:
    std::string inputStr;
};

int main() {
    // Get the desktop mode; screen dimensions
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2i windowPosition((desktop.width - 800) / 2, (desktop.height - 600) / 2);

    // Create the window centered on the screen
    sf::RenderWindow window(sf::VideoMode(800, 600), "Library System");
    window.setPosition(windowPosition);
    window.setVerticalSyncEnabled(true);

    // Load a font for text input
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    // Define menu options
    std::vector<std::string> menuOptions = {"Add Item", "Register Member", "All items", "Find an Item", "Exit"};
    Menu menu(&window, menuOptions);

    // Create text input fields
    TextInput titleInput(250, 200, "Title", font);
    TextInput authorInput(250, 260, "Author", font);
    TextInput pageInput(250, 320, "Page Count", font);
    TextInput bindingInput(250, 380, "Binding Type", font);

    // Create a button to add the item
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

                            // Get item details from text input fields
                            std::string title = titleInput.getInput();
                            std::string author = authorInput.getInput();
                            int pageCount = std::stoi(pageInput.getInput());
                            std::string bindingType = bindingInput.getInput();

                            // Create a new PrintedItem with the details
                            PrintedItem* newItem = new PrintedItem(title, author, pageCount, bindingType);

                            // Add the new item to the itemList
                            itemList.push_back(newItem);

                            // Display the newly added item's information
                            std::cout << "Item added:\n";
                            newItem->displayInfo();

                            // Reset inputs and return to main menu
                            titleInput.deactivate();
                            authorInput.deactivate();
                            pageInput.deactivate();
                            bindingInput.deactivate();
                            inAddItemMode = false;
                        }
                        // Check if the "Back" button was clicked
                        else if (backButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                            std::cout << "Back Button Clicked!\n";
                            titleInput.deactivate();
                            authorInput.deactivate();
                            pageInput.deactivate();
                            bindingInput.deactivate();
                            inAddItemMode = false;  // Go back to the main menu
                        } else {
                            // Handle text input field clicks
                            titleInput.handleMouseClick(mousePos);
                            authorInput.handleMouseClick(mousePos);
                            pageInput.handleMouseClick(mousePos);
                            bindingInput.handleMouseClick(mousePos);
                        }
                    } else {
                        menu.handleMouseClick(mousePos);

                        int selectedItem = menu.getSelectedItem();
                        if (selectedItem != -1) {
                            if (selectedItem == 0) {  // Add Item Selected
                                std::cout << "Add item Selected!\n";
                                inAddItemMode = true;  // Switch to Add Item Mode
                                titleInput.activate();  // Activate text inputs
                                authorInput.activate();
                                pageInput.activate();
                                bindingInput.activate();
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
            } else if (event.type == sf::Event::TextEntered) {
                // Handle text input
                if (inAddItemMode) {
                    titleInput.handleInput(event);
                    authorInput.handleInput(event);
                    pageInput.handleInput(event);
                    bindingInput.handleInput(event);
                }
            }
        }

        window.clear();

        if (inAddItemMode) {
            // In Add Item Mode, show the input fields and buttons
            titleInput.draw(window);
            authorInput.draw(window);
            pageInput.draw(window);
            bindingInput.draw(window);
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