.PHONY: all clean

CXX = /usr/bin/g++
CXXFLAGS = -g -Wall -w -pedantic-errors -Wextra -Wconversion -std=c++11
LINKER = -lncurses

SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)

MAZE_OBJECTS = maze.o cell.o
GENERATOR_OBJECTS = generator.o generator_driver.o
SOLVER_OBJECTS = solver.o player.o solver_driver.o

default: generator_driver

%.o: %.cpp
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

generator_driver: $(GENERATOR_OBJECTS) $(MAZE_OBJECTS)
	@echo "Building $@"
	@$(CXX) $(CXXFLAGS) $^ $(LINKER) -o $@
	@echo "Finished building generator_driver"

solver_driver: $(SOLVER_OBJECTS) $(MAZE_OBJECTS)
	@echo "Building $@"
	@$(CXX) $(CXXFLAGS) $^ $(LINKER) -o $@
	@echo "Finished building solver_driver"

clean:
	-@rm -f core
	-@rm -f solver_driver
	-@rm -f generator_driver
	-@rm -f depend
	-@rm -f $(SOLVER_OBJECTS)
	-@rm -f $(GENERATOR_OBJECTS)
	-@rm -f $(MAZE_OBJECTS)

depend: $(SOURCES) $(HEADERS)
	@echo "Generating dependencies"
	@$(CXX) -std=c++11 -MM *.cpp > $@

-include depend
