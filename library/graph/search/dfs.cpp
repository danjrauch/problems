#include <bits/stdc++.h>
using namespace std;

#define DFS_WHITE -1
#define DFS_BLACK 1
#define DFS_GRAY 2
vector<int> dfs_parent;      // to differentiate real back edge versus bidirectional edge

int V, E;
vector<vector<pair<int, int> > > graph;

vector<int> dfs_num;     // this variable has to be global, we cannot put it in recursion
int numCC;

//can find the number of connected components in an undirected graph
void dfs(int u) {
  printf(" %d", u);
  dfs_num[u] = DFS_BLACK;
  for(int j = 0; j < (int)graph[u].size(); j++) {
    pair<int,int> v = graph[u][j];
    if(dfs_num[v.first] == DFS_WHITE)
      dfs(v.first);
  }
}

void graphCheck(int u) {
  dfs_num[u] = DFS_GRAY;
  for(int j = 0; j < (int)graph[u].size(); j++) {
    pair<int,int> v = graph[u][j];
    if(dfs_num[v.first] == DFS_WHITE) {
      dfs_parent[v.first] = u;
      graphCheck(v.first);
    }
    else if(dfs_num[v.first] == DFS_GRAY) {
      if (v.first == dfs_parent[u])
        printf(" Bidirectional (%d, %d) - (%d, %d)\n", u, v.first, v.first, u);
      else
        printf(" Back Edge (%d, %d) (Cycle)\n", u, v.first);
    }
    else if(dfs_num[v.first] == DFS_BLACK)
      printf(" Forward/Cross Edge (%d, %d)\n", u, v.first);
  }
  dfs_num[u] = DFS_BLACK;
}

void inputGraph(){
  int a, b, w;
  scanf("%d %d", &V, &E);
  graph.resize(V);
  for(int j = 0; j<E; j++) {
    scanf("%d %d %d", &a, &b, &w);
    graph[a].push_back(make_pair(b, w));
  }
}

int main() {
  inputGraph();

  printf("Standard DFS Demo (the input graph must be UNDIRECTED)\n");
  numCC = 0;
  dfs_num.assign(V, DFS_WHITE);
  for(int i = 0; i < V; i++)
    if(dfs_num[i] == DFS_WHITE)
      printf("Component %d:", ++numCC), dfs(i), printf("\n");
  printf("There are %d connected components\n", numCC);

  printf("Graph Edges Property Check\n");
  numCC = 0;
  dfs_num.assign(V, DFS_WHITE); dfs_parent.assign(V, -1);
  for(int i = 0; i<V; i++)
    if(dfs_num[i] == DFS_WHITE)
      printf("Component %d:\n", ++numCC), graphCheck(i);

  return 0;
}