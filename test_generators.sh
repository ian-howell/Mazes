#!/bin/bash

for i in "prims" "dfs" "kruskal"
do
  ./generator_driver \--algorithm=$i \--animate \--speed=5 \--rows=35 \--cols=35 \--file=unsolved.txt
done
