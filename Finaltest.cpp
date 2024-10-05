#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>

#include "Book.h"
#include "Ebook.h"
#include "Library.h"
#include "Magazine.h"
#include "Menu.h"
//To compile type this g++ Finaltest.cpp Menu.cpp PrintedItem.cpp Item.cpp Book.cpp Library.cpp  Member.cpp Magazine.cpp Ebook.cpp DigitalItem.cpp -o sfml-menu -lsfml-graphics -lsfml-window -lsfml-system
// To run: ./sfml-menu
// Textbox class to handle user input with placeholder text
class Textbox {
public:
    Textbox(float x, float y, float width, float height, sf::Font &font, const std::string &placeholder) {
        box.setPosition(x, y);
        box.setSize(sf::Vector2f(width, height));
        box.setFillColor(sf::Color::White);
        box.setOutlineThickness(1);
        box.setOutlineColor(sf::Color::Black);

        text.setPosition(x + 5, y + 5);  // Padding inside the box
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(24);
        text.setFont(font);

        this->placeholder = placeholder;
        text.setString(this->placeholder);
        isSelected = false;
    }

    void handleEvent(const sf::Event &event, sf::RenderWindow &window) {
        if (event.type == sf::Event::MouseButtonPressed) {
            // Check if the textbox is clicked
            if (box.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                isSelected = true;
                text.setString(inputString);  // Show current input when clicked
            } else {
                isSelected = false;
                if (inputString.empty()) {
                    text.setString(placeholder);  // Show placeholder when not selected and empty
                }
            }
        }

        if (isSelected && event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8 && !inputString.empty()) {  // Backspace
                inputString.pop_back();
            } else if (event.text.unicode < 128 && event.text.unicode > 31) {  // Printable characters
                inputString += static_cast<char>(event.text.unicode);
            }
            text.setString(inputString);
        }
    }

    void draw(sf::RenderWindow &window) {
        window.draw(box);
        window.draw(text);
    }

    std::string getInput() {
        return inputString;
    }

private:
    sf::RectangleShape box;
    sf::Text text;
    std::string inputString;
    std::string placeholder;
    bool isSelected;
};

// Button class for "Add to Library" and "Back" buttons
class Button {
public:
    Button(float x, float y, float width, float height, const std::string &labelText, sf::Font &font) {
        button.setPosition(x, y);
        button.setSize(sf::Vector2f(width, height));
        button.setFillColor(sf::Color::White);
        button.setOutlineThickness(2);
        button.setOutlineColor(sf::Color::Black);

        label.setString(labelText);
        label.setFont(font);
        label.setCharacterSize(24);
        label.setFillColor(sf::Color::Black);
        label.setPosition(x + 10, y + 5);

    }

    void draw(sf::RenderWindow &window) {
        window.draw(button);
        window.draw(label);
    }

    bool isClicked(sf::RenderWindow &window) {
        return button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    }

private:
    sf::RectangleShape button;
    sf::Text label;
};

int main() {
    // Get the desktop mode; screen dimensions
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    // Calculate the window's position (centered)
    sf::Vector2i windowPosition(
        (desktop.width - 800) / 2,
        (desktop.height - 600) / 2);  // Assuming 800x600 window size

    // Create the window centered on the screen
    sf::RenderWindow window(
        sf::VideoMode(800, 600),
        "Library System");  // Specify window size (800x600)
    window.setPosition(windowPosition);

    // Load font for textboxes and buttons
    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Could not load font!\n";
        return -1;
    }

    // Define textboxes for adding a book with placeholder text
    Textbox titleBox(100, 100, 600, 40, font, "Enter Title");
    Textbox authorBox(100, 160, 600, 40, font, "Enter Author");
    Textbox pageCountBox(100, 220, 600, 40, font, "Enter Page Count");
    Textbox bindingTypeBox(100, 280, 600, 40, font, "Enter Binding Type");
    Textbox genreBox(100, 340, 600, 40, font, "Enter Genre");
    Textbox publicationDateBox(100, 400, 600, 40, font, "Enter Publication Date");

    // Define buttons for "Add to Library" and "Back"
    Button addButton(100, 460, 200, 50, "Add to Library", font);
    Button backButton(400, 460, 200, 50, "Back", font);

    // Define menu options
    std::vector<std::string> menuOptions = {
        "Add Member", "Add Item", "Remove Item",
        "Remove Member", "Display Items", "Display Members",
        "Borrow Item", "Return Item", "Exit"};
    Menu menu(&window, menuOptions);

    // Define sub-menu options for "Add Item"
    std::vector<std::string> addItemOptions = {"Book", "Magazine", "Ebook", "Back"};
    Menu addItemMenu(&window, addItemOptions);

<<<<<<< HEAD
    // Create a back button to return to the menu
    sf::RectangleShape backButton(sf::Vector2f(200, 50));
    backButton.setPosition(250, 510);
    backButton.setFillColor(sf::Color::Red);
    sf::Text backText("Back", font, 24);
    backText.setFillColor(sf::Color::White);
    backText.setPosition(330, 525);

    return 0;
}
=======
    bool inAddItemMenu = false;  // State variable to track whether we're in the "Add Item" sub-menu
    bool inAddBookMenu = false;  // Track whether we're in the "Add Book" sub-menu
    Library library;  // Library to manage items

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (inAddBookMenu) {
                // Handle textbox inputs when adding a book
                titleBox.handleEvent(event, window);
                authorBox.handleEvent(event, window);
                pageCountBox.handleEvent(event, window);
                bindingTypeBox.handleEvent(event, window);
                genreBox.handleEvent(event, window);
                publicationDateBox.handleEvent(event, window);

                // Handle button clicks
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (addButton.isClicked(window)) {
                        // Gather input from textboxes
                        std::string title = titleBox.getInput();
                        std::string author = authorBox.getInput();
                        int pageCount = std::stoi(pageCountBox.getInput());
                        std::string bindingType = bindingTypeBox.getInput();
                        std::string genre = genreBox.getInput();
                        std::string publicationDate = publicationDateBox.getInput();

                        // Add the book to the library
                        library.addItem(new Book(title, author, pageCount, bindingType, genre, publicationDate));

                        std::cout << "Book added successfully!\n";
                        inAddBookMenu = false;  // Return to add-item sub-menu after adding
                        inAddItemMenu = true;
                    } else if (backButton.isClicked(window)) {
                        inAddBookMenu = false;  // Return to add-item sub-menu
                        inAddItemMenu = true;
                    }
                }
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (!inAddItemMenu) {
                    // Main menu interaction
                    menu.handleMouseClick(sf::Mouse::getPosition(window));

                    int selectedItem = menu.getSelectedItem();
                    if (selectedItem == 1) {
                        inAddItemMenu = true;  // Switch to sub-menu for adding items
                    } else if (selectedItem == 8) {
                        window.close();  // Exit
                    }
                } else {
                    // Sub-menu interaction for adding items
                    addItemMenu.handleMouseClick(sf::Mouse::getPosition(window));
                    int selectedSubItem = addItemMenu.getSelectedItem();

                    if (selectedSubItem == 0) {
                        inAddBookMenu = true;  // Switch to add book mode
                        inAddItemMenu = false;
                    } else if (selectedSubItem == 3) {
                        inAddItemMenu = false;  // Go back to main menu
                    }
                }
            }
        }

        window.clear();

        if (inAddBookMenu) {
            // Draw textboxes for book details
            titleBox.draw(window);
            authorBox.draw(window);
            pageCountBox.draw(window);
                       bindingTypeBox.draw(window);
            genreBox.draw(window);
            publicationDateBox.draw(window);

            // Draw the "Add to Library" and "Back" buttons
            addButton.draw(window);
            backButton.draw(window);
        } else if (inAddItemMenu) {
            // Draw add-item sub-menu
            addItemMenu.draw();
        } else {
            // Draw main menu
            menu.draw();
        }

        window.display();
    }

    return 0;
}

>>>>>>> 2aadc6f4cd6575e60078fe13ce05f25786da9994
