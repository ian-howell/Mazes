HEADERS = $(wildcard *.h)
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)
LINKER = -lncurses -lmenu
CFLAGS =

CPP = g++

maze: ${OBJECTS}
	${CPP} ${C_FLAGS} ${OBJECTS} ${LINKER} -o $@

%.o: %.cpp
	${CPP} ${C_FLAGS} -c $< -o $@

.PHONY: clean debug

debug: C_FLAGS = -g -Wall --pedantic-errors
debug: maze

clean:
	-@rm -f *.o
	-@rm -f maze
	-@rm -f depend

depend: $(SOURCES) $(HEADERS)
	@g++ -MM *.cpp > $@

-include depend
