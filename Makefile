.PHONY: all clean directories

CXX = /usr/bin/g++
CXXFLAGS = -g -Wall -w -pedantic-errors -Wextra -Wconversion -std=c++11
LINKER = -lncurses

SOURCES = $(wildcard src/*.cpp)
HEADERS = $(wildcard include/*.h)

BUILD = build

INCLUDE = -Iinclude

MAZE_OBJECTS = $(BUILD)/maze.o $(BUILD)/cell.o
GENERATOR_OBJECTS = $(BUILD)/generator.o $(BUILD)/generator_driver.o $(BUILD)/union_find.o
SOLVER_OBJECTS = $(BUILD)/solver.o $(BUILD)/player.o $(BUILD)/solver_driver.o

DEPS := $(OBJECTS:%.o=%.d)

default: all
all: directories solver_driver generator_driver

-include $(DEPS)

$(BUILD)/%.o: src/%.cpp
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< $(INCLUDE) -o $@

generator_driver: $(GENERATOR_OBJECTS) $(MAZE_OBJECTS)
	@echo "Building $@"
	@$(CXX) $(CXXFLAGS) $^ $(LINKER) $(INCLUDE) -o $@
	@echo "Finished building generator_driver"

solver_driver: $(SOLVER_OBJECTS) $(MAZE_OBJECTS)
	@echo "Building $@"
	@$(CXX) $(CXXFLAGS) $^ $(LINKER) $(INCLUDE) -o $@
	@echo "Finished building solver_driver"

directories: $(BUILD)

$(BUILD):
	mkdir -p $(BUILD)

clean:
	-@rm -f core
	-@rm -f solver_driver
	-@rm -f generator_driver
	-@rm -f $(SOLVER_OBJECTS)
	-@rm -f $(GENERATOR_OBJECTS)
	-@rm -f $(MAZE_OBJECTS)
