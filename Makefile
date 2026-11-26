CC      = gcc
CXX     = g++
CFLAGS  = -Wall -Wextra -O2
CXXFLAGS= -Wall -Wextra -O2 -std=c++17

all: calculator snake

calculator: currency-calculator/main.c
	$(CC) $(CFLAGS) $< -o $@

snake: snake-game/snake.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f calculator snake

.PHONY: all clean
