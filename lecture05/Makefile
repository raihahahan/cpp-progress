# Makefile for SimpleVector project

CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2
TARGET = main
SRC = main.cpp

# default rule
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# clean rule
clean:
	rm -f $(TARGET)
