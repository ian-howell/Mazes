# Mazes
The maze project is a fun and interactive means of experimenting with and
demonstrating knowledge of graphing algorithms and their use cases. Using
ncurses, the maze project acts a visualizer for how graphing algorithms can be
used in the generation and solving of mazes.

## Getting Started
The following will get the project ready to run on your local machine.

### Requirements
In order to run the maze program, you will need the following:
* Python (at least 3.4)
* ncurses (readily available on most Linux Distros)

### Installation and Use
To use the maze program, simply clone it from this repo
``` bash
git clone git@github.com:ian-howell/Mazes.git
```

Once you have the project on your machine, you can build it with
``` bash
make
```

This will generate 2 binaries: `generator_driver` and `solver_driver`. These
binaries _can_ be used independently, but it's easier to simply run the python
script titled `maze.py`, which will guide you through their use.
``` bash
python3 maze.py
```

## About
The maze project is capable of generating mazes using 3 different algorithms:
* Randomized Prim's
* Randomized Depth-First Search
* Randomized Kruskal's

There are 4 automated solving algorithms:
* Recursive Backtracking
* Breadth-First Search
* Depth-First Search
* A\*

There is also a 5th option for solving; using the arrow keys, the user can
attempt to navigate through the maze manually.

The following details the machinations of each algorithm.

### Randomized Prim's
![Randomized Prim's Algorithm for generating mazes](/media/primgen.gif?raw=true
"Randomized Prim's")

### Randomized Depth-First Search
![Randomized Depth-First Search for generating mazes](/media/dfsgen.gif?raw=true
"Randomized Depth-First Search")
