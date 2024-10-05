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

// Define sub-menu options for "Add Item"
  std::vector<std::string> addItemOptions = {"Book", "Magazine", "Ebook", "Back"};

   Menu addItemMenu(&window, addItemOptions);

  bool inAddItemMenu = false;  // State variable to track whether we're in the "Add Item" sub-menu

 while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2i mousePos = sf::Mouse::getPosition(window);

          if (!inAddItemMenu) {
            // Main menu interaction
            menu.handleMouseClick(mousePos);

            int selectedItem = menu.getSelectedItem();
            if (selectedItem != -1) {
              if (selectedItem == 0) {
                std::cout << "Add Member Selected!\n";
              } 
              else if (selectedItem == 1) {
                std::cout << "Add Item Selected!\n";
                inAddItemMenu = true;  // Switch to sub-menu
              } 
              else if (selectedItem == 2) {
                std::cout << "Remove Item Selected!\n";
              } else if (selectedItem == 3) {
                std::cout << "Remove Member Selected!\n";
              } else if (selectedItem == 4) {
                std::cout << "Display Items Selected!\n";
              } else if (selectedItem == 5) {
                std::cout << "Display Members Selected!\n";
              } else if (selectedItem == 6) {
                std::cout << "Borrow Item Selected!\n";
              } else if (selectedItem == 7) {
                std::cout << "Return Item Selected!\n";
              } else if (selectedItem == 8) {
                std::cout << "Exit Selected!\n";
                window.close();  // Exit the application
              }
            }
          } else {
            // Sub-menu interaction for "Add Item"
            addItemMenu.handleMouseClick(mousePos);
            int selectedSubItem = addItemMenu.getSelectedItem();
            
            if (selectedSubItem != -1) {
              if (selectedSubItem == 0) {
                std::cout << "Book Selected!\n";
                inAddItemMenu = false;  // Return to main menu
              } else if (selectedSubItem == 1) {
                std::cout << "Magazine Selected!\n";
                inAddItemMenu = false;  // Return to main menu
              } else if (selectedSubItem == 2) {
                std::cout << "Ebook Selected!\n";
                inAddItemMenu = false;  // Return to main menu
              } else if (selectedSubItem == 3) {
                std::cout << "Back Selected!\n";
                inAddItemMenu = false;  // Return to main menu
              }
            }
          }
        }
      }
    }

    window.clear();
    
    if (!inAddItemMenu) {
      menu.draw();  // Draw main menu
    } else {
      addItemMenu.draw();  // Draw sub-menu
    }

    window.display();
  }

  return 0;
}