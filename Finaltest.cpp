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

    return 0;
}