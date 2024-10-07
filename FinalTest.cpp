#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "Book.h"
#include "Ebook.h"
#include "Library.h"
#include "Magazine.h"
#include "Menu.h"

// To compile: FinalTest.cpp Menu.cpp PrintedItem.cpp Item.cpp Book.cpp Library.cpp Member.cpp Magazine.cpp Ebook.cpp DigitalItem.cpp -o sfml-menu -lsfml-graphics -lsfml-window -lsfml-system 
// To run: ./sfml-menu

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

// Function to display items in the library
void displayItems(sf::RenderWindow &window, Library &library, sf::Font &font) {
    std::ostringstream itemDisplay;
    itemDisplay << "Items in Library:\n";
    
    // Assuming Library has a method to retrieve all items
    const std::vector<Item*>& items = library.getItemList(); // You'll need to implement this function in your Library class

    for (const Item* item : items) {
        if (Book* book = dynamic_cast<Book*>(item)) {
            itemDisplay << "Book: " << book->getTitle() << ", Author: " << book->getAuthor() << "\n"; // Ensure these methods exist
        } else if (Magazine* magazine = dynamic_cast<Magazine*>(item)) {
            itemDisplay << "Magazine: " << magazine->getTitle() << ", Author: " << magazine->getAuthor() << "\n"; // Ensure these methods exist
        } else if (Ebook* ebook = dynamic_cast<Ebook*>(item)) {
            itemDisplay << "Ebook: " << ebook->getTitle() << ", Author: " << ebook->getAuthor() << "\n"; // Ensure these methods exist
        }
    }

    // Create a text object to display the item list
    sf::Text displayText(itemDisplay.str(), font, 24);
    displayText.setFillColor(sf::Color::Black);
    displayText.setPosition(100, 100); // Adjust position as necessary

    // Draw the text on the window
    window.clear();
    window.draw(displayText);
    window.display();

    // Wait for a moment before returning to the main menu
    sf::sleep(sf::seconds(3)); // Adjust duration as necessary
}

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

     // Textboxes for adding a member
    Textbox memberNameBox(100, 100, 600, 40, font, "Enter Member Name");
    Textbox memberIDBox(100, 160, 600, 40, font, "Enter Member ID");

    // Define buttons
    Button addLibraryButton(100, 460, 200, 50, "Add to Library", font);
    Button backButton(350, 460, 200, 50, "Back", font);
    Button displayItemsButton(600, 460, 200, 50, "Display Items", font);

    Library library; // Your library instance

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle textbox events
            titleBox.handleEvent(event, window);
            authorBox.handleEvent(event, window);
            pageCountBox.handleEvent(event, window);
            bindingTypeBox.handleEvent(event, window);
            genreBox.handleEvent(event, window);
            publicationDateBox.handleEvent(event, window);

            // Handle magazine textboxes
            magazineTitleBox.handleEvent(event, window);
            magazineAuthorBox.handleEvent(event, window);
            magazinePageCountBox.handleEvent(event, window);
            magazineBindingTypeBox.handleEvent(event, window);
            magazinePublicationDateBox.handleEvent(event, window);
            issueNumberBox.handleEvent(event, window);

            // Handle ebook textboxes
            ebookTitleBox.handleEvent(event, window);
            ebookAuthorBox.handleEvent(event, window);
            fileSizeBox.handleEvent(event, window);
            formatBox.handleEvent(event, window);
            ebookGenreBox.handleEvent(event, window);
            ebookPublicationDateBox.handleEvent(event, window);

            // Handle member textboxes
            memberNameBox.handleEvent(event, window);
            memberIDBox.handleEvent(event, window);

            // Check if the add button is clicked
            if (addLibraryButton.isClicked(window)) {
                // Add logic for adding items to the library
                // Use the textbox values to create books, magazines, ebooks etc.
                std::string title = titleBox.getInput();
                std::string author = authorBox.getInput();
                int pageCount = std::stoi(pageCountBox.getInput());
                std::string bindingType = bindingTypeBox.getInput();
                std::string genre = genreBox.getInput();
                std::string publicationDate = publicationDateBox.getInput();

                Book newBook(title, author, pageCount, bindingType, genre, publicationDate);
                library.addItem(&newBook);  // Assuming this method exists

                // Clear the input fields
                titleBox = Textbox(100, 100, 600, 40, font, "Enter Book Title");
                authorBox = Textbox(100, 160, 600, 40, font, "Enter Book Author");
                pageCountBox = Textbox(100, 220, 600, 40, font, "Enter Book Page Count");
                bindingTypeBox = Textbox(100, 280, 600, 40, font, "Enter Book Binding Type");
                genreBox = Textbox(100, 340, 600, 40, font, "Enter Book Genre");
                publicationDateBox = Textbox(100, 400, 600, 40, font, "Enter Book Publication Date");
            }

            // Check if the display items button is clicked
            if (displayItemsButton.isClicked(window)) {
                displayItems(window, library, font);
            }

            // Check if the back button is clicked
            if (backButton.isClicked(window)) {
                // Handle going back to the previous menu or functionality
            }
        }

        // Drawing the current menu layout
        window.clear(sf::Color::White);
        titleBox.draw(window);
        authorBox.draw(window);
        pageCountBox.draw(window);
        bindingTypeBox.draw(window);
        genreBox.draw(window);
        publicationDateBox.draw(window);
        addLibraryButton.draw(window);
        displayItemsButton.draw(window);
        backButton.draw(window);
        window.display();
    }

    return 0;
}