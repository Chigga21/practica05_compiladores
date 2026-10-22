CXX ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -O2

FUENTES := $(wildcard src/*.cpp)
OBJETOS := $(FUENTES:src/%.cpp=build/%.o)

slr: $(OBJETOS)
	$(CXX) $(CXXFLAGS) -o $@ $^

build/%.o: src/%.cpp $(wildcard src/*.hpp) | build
	$(CXX) $(CXXFLAGS) -c -o $@ $<

build:
	mkdir -p build

test: slr
	./tests/run.sh

clean:
	rm -rf build temp slr

.PHONY: test clean
