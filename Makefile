CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra -Iinclude -pthread

SRC = src/main.cpp src/core/poseidon.cpp src/shell/shell.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = poseidon-vfs

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm -f $(OBJ) $(TARGET)
