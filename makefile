# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Executable name
EXEC = proj3.mine.x

# Source files
SRC = bet.cpp proj3_driver.cpp
HEADERS = bet.h

# Object files
OBJ = $(SRC:.cpp=.o)

# Default target
all: $(EXEC)

# Link object files to create executable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJ)

# Compile source files into object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJ) $(EXEC)