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

## Table of Contents
**[Maze Generation](#maze-generation)**<br>
* **[Randomized Prim's](#randomized-prims)**<br>
* **[Randomized Depth-First Search](#randomized-depth-first-search)**<br>
* **[Randomized Kruskal's](#randomized-kruskals)**<br>

**[Maze Solving](#maze-solving)**<br>
* **[Breadth-First Search](#breadth-first-search)**<br>
* **[Depth-First Search](#depth-first-search)**<br>
  * **[Recursive Backtracking](#recursive-backtracking)**<br>
* **[A*](#a)**<br>

There is also a 5th option for solving; using the arrow keys, the user can
attempt to navigate through the maze manually.

## Maze Generation
The following are explanations and demonstrations of algorithms that can be
used to generate mazes.

### Randomized Prim's
[Prim's Algorithm][prims] is a graphing algorithm used to find [Minimum
Spanning Trees (MST)][mst]. The algorithm starts by picking a given node in the
graph, with which it begins the MST. It then finds the shortest edge from the
MST to a node that is _not_ in the MST, and adds that node. It continues this
process until all nodes are in the MST.  The process of finding the shortest
edge can be (and frequently is) optimized by using a [Priority Queue][pqueue].

If we consider the console to be a fully connected graph, then we can slightly
modify this algorithm to create randomized mazes. Since the distance from a
node will always be `1`, we aren't able to pick the shortest edge (nor do we
want to). Instead, we will just randomly choose one of the edges that touches
the MST. This will result in a slowly spreading algorithm which will eventually
cut a complete maze from the grid. One of the properties of an MST is that
there are no cycles, therefore mazes generated with Prim's Algorithm with not
have loops.

<p align="center">
  <img src="media/primgen.gif" alt="Randomized Prim's Algorithm for generating mazes" />
</p>

### Randomized Depth-First Search
[Depth-First Search (DFS)][dfs] is a algorithm normally used to traverse the
nodes in a graph. Like Prim's Algorithm, it is initialized with a starting
point. DFS then pushes all of the connecting nodes on top of a [stack]. It then
pops off the top node from the stack, adds _its_ connecting nodes, and then
repeats the process until there are no more nodes on the stack. Normally, DFS
will use a uniform process when adding neighbors to the stack (For example, it
might add neighbors in a clockwise pattern: top, right, bottom, left). In the
case of maze generating, we need an element of randomness, so the neighbors
will be randomly selected to be added to the stack.

If we again consider the console to be a fully corrected graph, we can send DFS
through the grid, turning each visited node into a part of the maze. Due to the
nature of the stack data structure, DFS will seem to run along a path until it
runs out of space, at which point it will backtrack to an earlier point, then
run until it hits another dead-end. This will cause mazes to have very long
corridors, and a very low branching factor, so DFS mazes tend to have long
paths to the finish, but the solution is very easy to find.

<p align="center">
  <img src="media/dfsgen.gif" alt="Randomized Depth-First Search for generating mazes" />
</p>

### Randomized Kruskal's
[Kruskal's Algorithm][kruskal] is, much like Prim's Algorithm, a Minimum
Spanning Tree algorithm. The randomized version used here works by extracting
an edge from the set of all edges, then checking to see if the nodes at either
end of that edge are in the same [connected component], which are sometimes
referred to more simply as "forests". If the nodes are in the same forest, then
the edge is discarded, since adding it would create a cycle. However, if the
nodes are in separate forests, the edge is added, combining the two forests
into one. This process is repeated until there are no more edges to examine. In
this way, Kruskal's Algorithm is able to generate acyclic graphs.

<p align="center">
  <img src="media/kruskalgen.gif" alt="Randomized Kruskal's Algorithm for generating mazes" />
</p>

## Maze Solving
The following are explanations and demonstrations of algorithms that can be
used to solve mazes.

### Breadth-First Search
[Bread-First Search][bfs] is a relatively simple pathfinding algorithm - it's
frequently the first pathfinding algorithm the CS students learn. The function
is given a start node, which it immediately marks as visited and puts it into a
[queue]. This queue is referred to as the "frontier", and represents the nodes
that are currently being visited. It then pops the first node off the front of
the queue, and marks each of that node's neighbors as visited, followed by
adding them all to the queue. This process is repeated until either the goal is
found or all nodes have been explored. If BFS can't proceed, then there can not
be a path from the start to the node.

<p align="center">
  <img src="media/bfssolve.gif" alt="Breadth-First Search for solving mazes" />
</p>

### Depth-First Search
The operation of DFS is already explained in [the prior
section](#randomized-depth-first-search).

<p align="center">
  <img src="media/dfssolve.gif" alt="Depth-First Search for solving mazes" />
</p>

#### Recursive Backtracking
Recursive backtracking is a sort of clever way of implementing DFS. It uses the
exact same method for pathfinding, but taks advantage of the fact the when a
function is called, it is placed on the [call stack]. This call stack replaces
the stack used in DFS, causing Backtracking to be very easy to implement, since
the only required data structure is implicitly created during the operation of
the algorithm

Recursive backtracking can take a very long time. For this reason, the gif has
been omitted. The only visual difference between this implementation of
Backtracking vs DFS is that Backtracking actually "walks" back to the point at
which it made a wrong turn.

### A\*
[A\*][astar] is an "informed" pathfinding algorithm. This means that in order
for it to function, it not only needs to know where its start point is, it also
needs to know where the end point is. As A\* visits nodes, it assigns a
distance `d(start, v)` from that node to the start point. It also assigns a
value from a [heuristic] function `h(v)`. In the case of finding paths in
square-like mazes, the heuristic used is the [Manhattan Distance]. Once it has
those two values, they are summed and assigned to the node `f(v) = d(start, v) + h(v)`.
The node is then thrown into a priority queue. The algorithm progresses by
dequeing nodes from the priority queue until either the end point is
discovered, or there are no more nodes to explore.

<p align="center">
  <img src="media/astarsolve.gif" alt="A\* for solving mazes" />
</p>

<!-- References -->
[prims]: https://en.wikipedia.org/wiki/Prim%27s_algorithm
[mst]: https://en.wikipedia.org/wiki/Minimum_spanning_tree
[pqueue]: https://en.wikipedia.org/wiki/Priority_queue
[dfs]: https://en.wikipedia.org/wiki/Depth-first_search
[stack]: https://en.wikipedia.org/wiki/Stack_(abstract_data_type)
[kruskal]: https://en.wikipedia.org/wiki/Kruskal%27s_algorithm
[connected component]: https://en.wikipedia.org/wiki/Connected_component_(graph_theory)
[bfs]: https://en.wikipedia.org/wiki/Breadth-first_searcha
[queue]: https://en.wikipedia.org/wiki/Queue_(abstract_data_type)
[call stack]: https://en.wikipedia.org/wiki/Call_stack
[astar]: https://en.wikipedia.org/wiki/A*_search_algorithm
[heuristic]: https://en.wikipedia.org/wiki/Heuristic_(computer_science)
[Manhattan Distance]: https://en.wikipedia.org/wiki/Taxicab_geometry
