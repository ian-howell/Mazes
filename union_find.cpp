#include "union_find.h"

UnionFindSet::UnionFindSet(int x)
{
  parent = x;
  rank = 0;
}

int find(std::vector<UnionFindSet>& s, int x)
{
  if (s[x].parent != x)
    s[x].parent = find(s, s[x].parent);
  return s[x].parent;
}

void join(std::vector<UnionFindSet>& s, int x, int y)
{
  int xroot = find(s, x);
  int yroot = find(s, y);

  if (xroot == yroot)
    return;

  if (s[xroot].rank < s[yroot].rank)
  {
    s[xroot].parent = yroot;
  }
  else if (s[xroot].rank > s[yroot].rank)
  {
    s[yroot].parent = xroot;
  }
  else
  {
    s[yroot].parent = xroot;
    s[xroot].rank++;
  }
}
