# Makefile for the library management system

# Compiler
CXX = g++
CXXFLAGS = -Wall -g

# Source files
SRCS = Librarymanagement.cpp Member.cpp Library.cpp Item.cpp PrintedItem.cpp DigitalItem.cpp Book.cpp Magazine.cpp Ebook.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = library_management

# Default target to build the executable
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lncurses

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Clean target to remove object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# Run target to execute the program
run: $(TARGET)
	./$(TARGET)