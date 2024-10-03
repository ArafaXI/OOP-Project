#include "Menu.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// Constructor to initialize menu
Menu::Menu(sf::RenderWindow* win, const std::vector<std::string>& menuOptions)
    : window(win), selectedItem(-1), normalColor(sf::Color::White), highlightColor(sf::Color::Red) {

    // Load font (make sure to replace with the actual path to your font file)
    if (!font.loadFromFile("Arial.ttf")) {
        std::cerr << "Error loading font\n";
    }

    options = menuOptions;
    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setCharacterSize(24);  // Default size
        text.setFillColor(normalColor);  // Default color
        text.setPosition(100, 100 + i * 50);  // Adjust position dynamically
        menuTexts.push_back(text);
    }
}

// Method to draw the menu
void Menu::draw() {
    for (const auto& text : menuTexts) {
        window->draw(text);
    }
}

// Method to handle mouse clicks
void Menu::handleMouseClick(sf::Vector2i mousePos) {
    for (size_t i = 0; i < menuTexts.size(); ++i) {
        sf::FloatRect boundingBox = menuTexts[i].getGlobalBounds();
        if (boundingBox.contains(static_cast<sf::Vector2f>(mousePos))) {
            selectedItem = i;
        }
    }
    highlightSelectedItem();  // Highlight the selected item after clicking
}

// Method to adjust the size of text
void Menu::adjustTextSize(int newSize) {
    for (auto& text : menuTexts) {
        text.setCharacterSize(newSize);
    }
}

// Method to get the selected item index
int Menu::getSelectedItem() const {
    return selectedItem;
}

// Method to highlight the selected menu item
void Menu::highlightSelectedItem() {
    for (size_t i = 0; i < menuTexts.size(); ++i) {
        if (static_cast<int>(i) == selectedItem) {
            menuTexts[i].setFillColor(highlightColor);  // Highlight selected item
        } else {
            menuTexts[i].setFillColor(normalColor);  // Reset others to normal color
        }
    }
}
