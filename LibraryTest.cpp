#include "Library.h"
#include "Book.h"
#include "Magazine.h"
#include "Member.h"

void testLibrary() {
  Library library;

  // Test adding members
  std::cout << "Testing addMember:" << std::endl;
  library.addMember(new Member("Alice", 1));
  library.addMember(new Member("Bob", 2));
  library.displayMembers();  // Should display Alice and Bob

  // Test removing a member by index
  std::cout << "Testing removeMember (index 0):" << std::endl;
  library.removeMember(0);
  library.displayMembers();  // Should display Bob only

  // Test adding items
  std::cout << "Testing addItem:" << std::endl;
  library.addItem(new Book("The Great Gatsby", "F. Scott Fitzgerald", 180,
                           "Hardcover", "Fiction", "1925"));
  library.addItem(
      new Magazine("National Geographic", "Various", 30, "Monthly", "2021", 1));
  library.displayItems();  // Should display the added book and magazine

  // Test removing an item by index
  std::cout << "Testing removeItem (index 0):" << std::endl;
  library.removeItem(0);
  library.displayItems();  // Should display National Geographic only

  // Test borrowing and returning items
  std::cout << "Testing borrowItem:" << std::endl;
  library.borrowItem(
      0,
      0);  // Assuming Bob is at index 0 and National Geographic is at index 0
  library.returnItem(0, 0);  // Return National Geographic

  // Test removing items with invalid index
  std::cout << "Testing removeItem (invalid index):" << std::endl;
  library.removeItem(10);  // Invalid index, should display an error

  // Test removing members with invalid index
  std::cout << "Testing removeMember (invalid index):" << std::endl;
  library.removeMember(10);  // Invalid index, should display an error

  // Test displaying items when no items exist
  std::cout << "Testing displayItems (no items):" << std::endl;
  library.removeItem(0);   // Remove the remaining item
  library.displayItems();  // Should indicate no items added

  // Test displaying members when no members exist
  std::cout << "Testing displayMembers (no members):" << std::endl;
  library.removeMember(0);   // Remove the remaining member
  library.displayMembers();  // Should indicate no members added

  // Cleanup not necessary in this test case, as destructor will handle it
}

int main() {
  testLibrary();
  return 0;
}