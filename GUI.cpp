#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Book.h"
#include "Ebook.h"
#include "Library.h"
#include "Magazine.h"
#include "Menu.h"

// To compile: g++ GUI.cpp Menu.cpp PrintedItem.cpp Item.cpp Book.cpp Library.cpp Member.cpp Magazine.cpp Ebook.cpp DigitalItem.cpp -o sfml-menu -lsfml-graphics -lsfml-window -lsfml-system 
// To run: /sfml-menu

// Textbox class to handle user input, with placeholder text
class Textbox {
public:
    Textbox(float x, float y, float width, float height, sf::Font &font, const std::string &placeholder) {
        box.setPosition(x, y);
        box.setSize(sf::Vector2f(width, height));
        box.setFillColor(sf::Color::White);
        box.setOutlineThickness(1);
        box.setOutlineColor(sf::Color::Black);

        text.setPosition(x + 5, y + 5);  // Some padding inside the box
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(24);
        text.setFont(font);

        this->placeholder = placeholder;
        text.setString(this->placeholder);
        isSelected = false;  // Initially, the textbox is not selected
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
                    text.setString(placeholder);  // Show placeholder if empty
                }
            }
        }

        if (isSelected && event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8 && !inputString.empty()) {  // Backspace
                inputString.pop_back();
            } else if (event.text.unicode < 128 && event.text.unicode > 31) {  // Printable chars
                inputString += static_cast<char>(event.text.unicode);
            }
            text.setString(inputString);  // Update the displayed text
        }
    }

    void draw(sf::RenderWindow &window) {
        window.draw(box);  // Draw the textbox box
        window.draw(text); // Draw the text inside the box
    }

    std::string getInput() {
        return inputString;  // Return the current input string
    }

private:
    sf::RectangleShape box; // The box for the textbox
    sf::Text text;          // The text inside the textbox
    std::string inputString; // Current input from user
    std::string placeholder; // Placeholder text when empty
    bool isSelected;        // Is the textbox selected?
};

// Button class for handling buttons like "Add to Library" and "Back"
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
        label.setPosition(x + 10, y + 5); // A bit of padding for the label
    }

    void draw(sf::RenderWindow &window) {
        window.draw(button); // Draw the button
        window.draw(label);  // Draw the label
    }

    bool isClicked(sf::RenderWindow &window) {
        // Check if the button is clicked
        return button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    }

private:
    sf::RectangleShape button; // The button shape
    sf::Text label;           // The text label on the button
};

int main() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::Vector2i windowPosition((desktop.width - 800) / 2, (desktop.height - 600) / 2);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Library Management System");
    window.setPosition(windowPosition);

    sf::Font font;
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Could not load font!\n";
        return -1;
    }

    // Textboxes for adding a book with placeholders
    Textbox titleBox(100, 100, 600, 40, font, "Enter Book Title");
    Textbox authorBox(100, 160, 600, 40, font, "Enter Book Author");
    Textbox pageCountBox(100, 220, 600, 40, font, "Enter Book Page Count");
    Textbox bindingTypeBox(100, 280, 600, 40, font, "Enter Book Binding Type");
    Textbox genreBox(100, 340, 600, 40, font, "Enter Book Genre");
    Textbox publicationDateBox(100, 400, 600, 40, font, "Enter Book Publication Date");

    // Textboxes for adding a magazine, same as book but with different attributes
    Textbox magazineTitleBox(100, 100, 600, 40, font, "Enter Magazine Title");
    Textbox magazineAuthorBox(100, 160, 600, 40, font, "Enter Magazine Author");
    Textbox magazinePageCountBox(100, 220, 600, 40, font, "Enter Magazine Page Count");
    Textbox magazineBindingTypeBox(100, 280, 600, 40, font, "Enter Magazine Binding Type");
    Textbox magazinePublicationDateBox(100, 340, 600, 40, font, "Enter Magazine Publication Date");
    Textbox issueNumberBox(100, 400, 600, 40, font, "Enter Issue Number");

    // Textboxes for adding an ebook, similar to book with its own attributes
    Textbox ebookTitleBox(100, 100, 600, 40, font, "Enter Ebook Title");
    Textbox ebookAuthorBox(100, 160, 600, 40, font, "Enter Ebook Author");
    Textbox fileSizeBox(100, 220, 600, 40, font, "Enter File Size (MB)");
    Textbox formatBox(100, 280, 600, 40, font, "Enter Format");
    Textbox ebookGenreBox(100, 340, 600, 40, font, "Enter Ebook Genre");
    Textbox ebookPublicationDateBox(100, 400, 600, 40, font, "Enter Ebook Publication Date");

    // Define buttons
    Button addButton(100, 460, 200, 50, "Add to Library", font);
    Button backButton(400, 460, 200, 50, "Back", font);

    // Define main menu options
    std::vector<std::string> menuOptions = {
        "Add Member", "Add Item", "Remove Item",
        "Remove Member", "Display Items", "Display Members",
        "Borrow Item", "Return Item", "Exit"};
    Menu menu(&window, menuOptions);

    // Define sub-menu options for adding items
    std::vector<std::string> addItemOptions = {"Book", "Magazine", "Ebook", "Back"};
    Menu addItemMenu(&window, addItemOptions);

    bool inAddItemMenu = false; // Are we in the add item menu?
    bool inAddBookMenu = false;  // Are we adding a book?
    bool inAddMagazineMenu = false; // Are we adding a magazine?
    bool inAddEbookMenu = false; // Are we adding an ebook?
    Library library; // Our library object

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            if (inAddBookMenu) {
                // Handle book input
                titleBox.handleEvent(event, window);
                authorBox.handleEvent(event, window);
                pageCountBox.handleEvent(event, window);
                bindingTypeBox.handleEvent(event, window);
                genreBox.handleEvent(event, window);
                publicationDateBox.handleEvent(event, window);

                if (event.type == sf::Event::MouseButtonPressed) {
                    if (addButton.isClicked(window)) {
                        // Gather inputs for book
                        std::string title = titleBox.getInput();
                        std::string author = authorBox.getInput();
                        int pageCount = std::stoi(pageCountBox.getInput());
                        std::string bindingType = bindingTypeBox.getInput();
                        std::string genre = genreBox.getInput();
                        std::string publicationDate = publicationDateBox.getInput();

                        // Add book to the library
                        library.addItem(new Book(title, author, pageCount, bindingType, genre, publicationDate));
                        std::cout << "Book added successfully!\n";
                        inAddBookMenu = false; // Go back to add-item menu
                        inAddItemMenu = true;
                    } else if (backButton.isClicked(window)) {
                        inAddBookMenu = false; // Go back to add-item menu
                        inAddItemMenu = true;
                    }
                }
            } else if (inAddMagazineMenu) {
                // Handle magazine input
                magazineTitleBox.handleEvent(event, window);
                magazineAuthorBox.handleEvent(event, window);
                magazinePageCountBox.handleEvent(event, window);
                magazineBindingTypeBox.handleEvent(event, window);
                magazinePublicationDateBox.handleEvent(event, window);
                issueNumberBox.handleEvent(event, window);

                if (event.type == sf::Event::MouseButtonPressed) { 
                    if (addButton.isClicked(window)) {
                        // Gather inputs for magazine
                        std::string title = magazineTitleBox.getInput();
                        std::string author = magazineAuthorBox.getInput();
                        int pageCount = std::stoi(magazinePageCountBox.getInput());
                        std::string bindingType = magazineBindingTypeBox.getInput();
                        std::string publicationDate = magazinePublicationDateBox.getInput();
                        int issueNumber = std::stoi(issueNumberBox.getInput());

                        // Add magazine to library
                        library.addItem(new Magazine(title, author, pageCount, bindingType, publicationDate, issueNumber));
                        std::cout << "Magazine added successfully!\n";
                        inAddMagazineMenu = false; // Go back to add-item menu
                        inAddItemMenu = true;
                    } else if (backButton.isClicked(window)) {
                        inAddMagazineMenu = false; // Go back to add-item menu
                        inAddItemMenu = true;
                    }
                }
            } else if (inAddEbookMenu) {
                // Handle ebook input
                ebookTitleBox.handleEvent(event, window);
                ebookAuthorBox.handleEvent(event, window);
                fileSizeBox.handleEvent(event, window);
                formatBox.handleEvent(event, window);
                ebookGenreBox.handleEvent(event, window);
                ebookPublicationDateBox.handleEvent(event, window);

                if (event.type == sf::Event::MouseButtonPressed) {
                    if (addButton.isClicked(window)) {
                        // Gather inputs for ebook
                        std::string title = ebookTitleBox.getInput();
                        std::string author = ebookAuthorBox.getInput();
                        float fileSize = std::stof(fileSizeBox.getInput());
                        std::string format = formatBox.getInput();
                        std::string genre = ebookGenreBox.getInput();
                        std::string publicationDate = ebookPublicationDateBox.getInput();

                        // Add ebook to the library
                        library.addItem(new Ebook(title, author, fileSize, format, genre, publicationDate));
                        std::cout << "Ebook added successfully!\n";
                        inAddEbookMenu = false; // Go back to add-item menu
                        inAddItemMenu = true;
                    } else if (backButton.isClicked(window)) {
                        inAddEbookMenu = false; // Go back to add-item menu
                        inAddItemMenu = true;
                    }
                }
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if (!inAddItemMenu) {
                    // Main menu interactions
                    menu.handleMouseClick(sf::Mouse::getPosition(window));
                    int selectedItem = menu.getSelectedItem();
                    if (selectedItem == 1) {
                        inAddItemMenu = true;  // Switch to add item menu
                    } else if (selectedItem == 8) {
                        window.close();  // Exit the program
                    }
                } else {
                    // Sub-menu interactions for adding items
                    addItemMenu.handleMouseClick(sf::Mouse::getPosition(window));
                    int selectedSubItem = addItemMenu.getSelectedItem();

                    if (selectedSubItem == 0) {
                        inAddBookMenu = true; // Switch to add book mode
                        inAddItemMenu = false;
                    } else if (selectedSubItem == 1) {
                        inAddMagazineMenu = true; // Switch to add magazine mode
                        inAddItemMenu = false;
                    } else if (selectedSubItem == 2) {
                        inAddEbookMenu = true; // Switch to add ebook mode
                        inAddItemMenu = false;
                    } else if (selectedSubItem == 3) {
                        inAddItemMenu = false; // Go back to main menu
                    }
                }
            }
        }

        window.clear();

        if (inAddBookMenu) {
            // Draw book textboxes and buttons
            titleBox.draw(window);
            authorBox.draw(window);
            pageCountBox.draw(window);
            bindingTypeBox.draw(window);
            genreBox.draw(window);
            publicationDateBox.draw(window);
            addButton.draw(window);
            backButton.draw(window);
        } else if (inAddMagazineMenu) {
            // Draw magazine textboxes and buttons
            magazineTitleBox.draw(window);
            magazineAuthorBox.draw(window);
            magazinePageCountBox.draw(window);
            magazineBindingTypeBox.draw(window);
            magazinePublicationDateBox.draw(window);
            issueNumberBox.draw(window);
            addButton.draw(window);
            backButton.draw(window);
        } else if (inAddEbookMenu) {
            // Draw ebook textboxes and buttons
            ebookTitleBox.draw(window);
            ebookAuthorBox.draw(window);
            fileSizeBox.draw(window);
            formatBox.draw(window);
            ebookGenreBox.draw(window);
            ebookPublicationDateBox.draw(window);
            addButton.draw(window);
            backButton.draw(window);
        } else if (inAddItemMenu) {
            // Draw add-item sub-menu
            addItemMenu.draw();
        } else {
            // Draw main menu
            menu.draw();
        }

        window.display(); // Update the window
    }

    return 0;
}