.PHONY: all clean

CXX = /usr/bin/g++
CXXFLAGS = -g -Wall -w -pedantic-errors -Wextra -Wconversion -std=c++11
LINKER = -lncurses

SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)

OBJECTS = $(SOURCES:%.cpp=%.o)

default: driver

%.o: %.cpp
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

driver: $(OBJECTS)
	@echo "Building $@"
	@$(CXX) $(CXXFLAGS) $(OBJECTS) $(LINKER) -o $@
	@echo "Finished building driver"

clean:
	-@rm -f core
	-@rm -f driver
	-@rm -f depend
	-@rm -f $(OBJECTS)

depend: $(SOURCES) $(HEADERS)
	@echo "Generating dependencies"
	@$(CXX) -std=c++11 -MM *.cpp > $@

-include depend
