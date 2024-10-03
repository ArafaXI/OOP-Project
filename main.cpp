#include <SFML/Graphics.hpp>
#include <iostream>
#include "Item.h"
#include "PrintedItem.h"
#include "Menu.h"  // Assuming PrintedItem inherits from Item

int main() {
  // Get the desktop mode; screen dimensions
  sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
  sf::Vector2i windowPosition((desktop.width - 800) / 2, (desktop.height - 600) / 2);

  // Create the window centered on the screen
  sf::RenderWindow window(sf::VideoMode(800, 600), "Library System");
  window.setPosition(windowPosition);
  window.setVerticalSyncEnabled(true);

  // Define menu options
  std::vector<std::string> menuOptions = {"Add Item", "Register Member",
                                          "All items", "Find an Item", "Exit"};
  Menu menu(&window, menuOptions);

  // Assuming PrintedItem objects will be stored in a vector or similar container
  std::vector<Item*> itemList;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();

      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          sf::Vector2i mousePos = sf::Mouse::getPosition(window);
          menu.handleMouseClick(mousePos);

          int selectedItem = menu.getSelectedItem();
          if (selectedItem != -1) {
            if (selectedItem == 0) {  // Add Item Selected
              std::cout << "Add item Selected!\n";

              // Get item details
              std::string title, author, bindingType;
              int pageCount;

              std::cout << "Enter title: ";
              std::cin >> title;
              std::cout << "Enter author: ";
              std::cin >> author;
              std::cout << "Enter page count: ";
              std::cin >> pageCount;
              std::cout << "Enter binding type: ";
              std::cin >> bindingType;

              // Create a new PrintedItem with the details
              PrintedItem* newItem = new PrintedItem(title, author, pageCount, bindingType);

              // Add the new item to the itemList
              itemList.push_back(newItem);

              // Display the newly added item's information
              std::cout << "Item added:\n";
              newItem->displayInfo();  // Call the virtual method to display info
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

    window.clear();
    menu.draw();
    window.display();
  }

  // Cleanup dynamically allocated items
  for (auto item : itemList) {
    delete item;  // Ensure each item is deleted to avoid memory leaks
  }

  return 0;
}
