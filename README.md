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
[Prim's Algorithm](https://en.wikipedia.org/wiki/Prim%27s_algorithm) is a
graphing algorithm used to find [Minimum Spanning Trees
(MST)](https://en.wikipedia.org/wiki/Minimum_spanning_tree). The algorithm
starts by picking a given node in the graph, with which it begins the MST. It
then finds the shortest edge from the MST to a node that is _not_ in the MST,
and adds that node. It continues this process until all nodes are in the MST.
The process of finding the shortest edge can be (and frequently is) optimized
by using a [Priority Queue](https://en.wikipedia.org/wiki/Priority_queue).

If we consider the console to be a fully connected graph, then we can slightly
modify this algorithm to create randomized mazes. Since the distance from a
node will always be `1`, we aren't able to pick the shortest edge (nor do we
want to). Instead, we will just randomly choose one of the edges that touches
the MST. This will result in a slowly spreading algorithm which will eventually
cut a complete maze from the grid. One of the properties of an MST is that
there are no cycles, therefore mazes generated with Prim's Algorithm with not
have loops.

![Randomized Prim's Algorithm for generating mazes](media/primgen.gif?raw=true
"Randomized Prim's")

### Randomized Depth-First Search
![Randomized Depth-First Search for generating mazes](media/dfsgen.gif?raw=true
"Randomized Depth-First Search")

### Randomized Kruskal's Algorithm
![Randomized Kruskal's Algorithm for generating mazes](media/kruskalgen.gif?raw=true
"Randomized Kruskal's Algorithm")

### Breadth-First Search
![Breadth-First Search for solving mazes](media/bfssolve.gif?raw=true
"Breadth-First Search")

### Depth-First Search
![Depth-First Search for solving mazes](media/dfssolve.gif?raw=true
"Depth-First Search")

### A\*
![A\* for solving mazes](media/astarsolve.gif?raw=true
"A\*")
