#!/bin/bash

for i in "bt" "bfs" "dfs" "astar"
do
  ./solver_driver \--algorithm=$i \--animate \--speed=5 \--infile=unsolved.txt \-o solved.txt
done
