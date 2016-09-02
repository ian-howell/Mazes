HEADERS = $(wildcard *.h)
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)
LINKER = -lncurses -lmenu
C_FLAGS = -Wall --pedantic-errors -O2

CPP = g++

maze: ${OBJECTS} ${HEADERS}
	${CPP} ${C_FLAGS} ${OBJECTS} ${LINKER} -o maze

%.o: %.cpp ${HEADERS}
	${CPP} -c $<

.PHONY: clean debug

debug: C_FLAGS = -g -Wall --pedantic-errors
debug: maze

clean:
	-@rm -f *.o
	-@rm -f maze
