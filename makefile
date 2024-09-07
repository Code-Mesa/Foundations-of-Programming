# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror

# Source and object files
SRC = src/main.cpp src/Student.cpp src/Utility.cpp
OBJ = $(SRC:.cpp=.o)

# Executable file
TARGET = grade_management_system

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up object files and executable
clean:
	rm -f $(OBJ).o $(TARGET)
