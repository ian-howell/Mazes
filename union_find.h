#ifndef UNION_FIND_H
#define UNION_FIND_H

#include <vector>

// Helper struct for Kruskal's algorithm
struct UnionFindSet
{
  int rank;
  int parent;
  UnionFindSet() {}
  UnionFindSet(int i);
};

int find(std::vector<UnionFindSet>& s, int i);
void join(std::vector<UnionFindSet>& s, int x, int y);

#endif
