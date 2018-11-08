#include <bits/stdc++.h>
using namespace std;

#define DFS_WHITE -1
#define DFS_BLACK 1

int V, E;
vector<vector<pair<int, int> > > graph;
vector<int> dfs_num;
vector<int> dfs_low;
int dfsNumberCounter, numSCC;
vector<int> S, visited;

void tarjanSCC(int u) {
  dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
  S.push_back(u);
  visited[u] = 1;
  for(int j = 0; j < (int)graph[u].size(); j++) {
    pair<int, int> v = graph[u][j];
    if(dfs_num[v.first] == DFS_WHITE)
      tarjanSCC(v.first);
    if(visited[v.first])
      dfs_low[u] = min(dfs_low[u], dfs_low[v.first]);
  }
  if(dfs_low[u] == dfs_num[u]) {
    printf("SCC %d:", ++numSCC);
    while(1) {
      int v = S.back(); S.pop_back(); visited[v] = 0;
      printf(" %d", v);
      if(u == v) break;
    }
    printf("\n");
  }
}

void inputGraph(){
  int a, b, w;
  scanf("%d %d", &V, &E);
  graph.resize(V); // assign blank vectors of pair<int, int>s to graph
  for(int j = 0; j<E; j++) {
    scanf("%d %d %d", &a, &b, &w);
    graph[a].push_back(make_pair(b, w));
  }
}

int main() {
  inputGraph();

  printf("Strongly Connected Components (the input graph must be DIRECTED)\n");
  dfs_num.assign(V, DFS_WHITE); dfs_low.assign(V, 0); visited.assign(V, 0);
  dfsNumberCounter = numSCC = 0;
  for(int i = 0; i < V; i++)
    if(dfs_num[i] == DFS_WHITE)
      tarjanSCC(i);

  return 0;
}
