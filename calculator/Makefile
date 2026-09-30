CXX      = g++
CXXFLAGS = -Wall -O2 -std=c++17

SRC    = main.cpp
TARGET = calculator

all: $(TARGET)

$(TARGET): $(SRC)
    $(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
    rm -f $(TARGET)

run: $(TARGET)
    ./$(TARGET)

.PHONY: all clean run
