#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "Book.h"
#include "Ebook.h"
#include "Library.h"
#include "Magazine.h"
#include "Menu.h"

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
      "Library System");  // Specify window size (800x600 for example)
  window.setPosition(windowPosition);
  window.setVerticalSyncEnabled(true);

  // Define menu options
  std::vector<std::string> menuOptions = {
      "Add Member",    "Add Item",      "Remove Item",
      "Remove Member", "Display Items", "Display Members",
      "Borrow Item",   "Return Item",   "Exit"};
  Menu menu(&window, menuOptions);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2i mousePos = sf::Mouse::getPosition(window);
          menu.handleMouseClick(mousePos);

          // Check if an option is selected
          int selectedItem = menu.getSelectedItem();
          if (selectedItem != -1) {
            if (selectedItem == 0) {
              std::cout << "Add Member Selected!\n";
            } else if (selectedItem == 1) {
              std::cout << "Add Item Selected!\n";
            } else if (selectedItem == 2) {
              std::cout << "Remove Item Selected!\n";
            } else if (selectedItem == 3) {
              std::cout << "Remove Member Selected!\n";
            } else if (selectedItem == 4) {
              std::cout << "Display Item Selected!\n";
            } else if (selectedItem == 5) {
              std::cout << "Display Members Selected!\n";
            } else if (selectedItem == 6) {
              std::cout << "Borrow Item Selected!\n";
            } else if (selectedItem == 7) {
              std::cout << "Return Item Selected!\n";
            } else if (selectedItem == 4) {
              std::cout << "Exit Selected!\n";
              window.close();  // Exit the application
            }
          }
        }
      }
    }

    window.clear();
    menu.draw();
    window.display();
  }

  return 0;
}