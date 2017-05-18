#!/bin/bash

for i in "prims" "dfs" "kruskal"
do
  echo "./generator_driver --algorithm=$i --animate --speed=5 --rows=50 --cols=50 --file=unsolved.txt"
  ./generator_driver \--algorithm=$i \--animate \--speed=5 \--rows=50 \--cols=50 \--file=unsolved.txt
done
