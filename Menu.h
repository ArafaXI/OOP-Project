#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
private:
    std::vector<std::string> options;
    sf::Font font;
    std::vector<sf::Text> menuTexts;
    int selectedItem;
    sf::RenderWindow* window;
    sf::Color normalColor;
    sf::Color highlightColor;

public:
    Menu(sf::RenderWindow* win, const std::vector<std::string>& menuOptions);
    void draw();
    void handleMouseClick(sf::Vector2i mousePos);
    void adjustTextSize(int newSize);  // Method to adjust text size
    int getSelectedItem() const;
    void highlightSelectedItem();  // Method to highlight the selected item
        bool isItemSelected(const std::string& item) const {
        if (selectedItem < 0 || selectedItem >= options.size()) {
            return false;  // No item selected
        }
        return options[selectedItem] == item;
    }
};


#endif
