/*

   *       *        This program identifies a single cycle in the graph,
    \  *  /         done by findCycle via dfs variant. Verticies in this
     \  \/          cycle are given value 0 in the mapping vector.   
      *-*    *      Then for each vertex v in that cycle, a bfs is begun
      | |   /       at v. The shortest paths to the verticies seen on 
    *-*-*--*---*    these searches are recorded in the mapping vector.
     /   \          So the program calculates the shortest distances 
    *     *         from a central cycle to all other verticies.

*/

#include <bits/stdc++.h>
using namespace std;

#define DFS_WHITE -1
#define DFS_BLACK 1
#define DFS_GRAY 2

int V;
vector<vector<int>> graph;

vector<int> dfs_num, dfs_parent, mapping;

void inputGraph(){
  int a, b;
  scanf("%d", &V);
  graph.resize(V);
  mapping.assign(V, -1);
  for(int i = 0; i<V; i++){
    scanf("%d %d", &a, &b);
    graph[a-1].push_back(b-1);
    graph[b-1].push_back(a-1);
  }
}

void bfs(int s){
  queue<int> q;
  q.push(s);
  while(!q.empty()){
    int u = q.front();
    for(int i = 0; i<graph[u].size(); ++i){
      if(mapping[graph[u][i]] == -1){
        q.push(graph[u][i]);
        mapping[graph[u][i]] = mapping[u] + 1;
      }
    }
    q.pop();
  }
}

int dfs(int u){
  dfs_num[u] = DFS_GRAY;
  for(int i = 0; i<graph[u].size(); i++){
    int v = graph[u][i];
    if(dfs_num[v] == DFS_WHITE){
      dfs_parent[v] = u;
      dfs(v);
    }
    else if(dfs_num[v] == DFS_GRAY)
      if(v != dfs_parent[u])
        return v;
  }
  dfs_num[u] = DFS_BLACK;
  return -1;
}

void findCycle(){
  for(int i = 0; i<V; ++i){
    dfs_num.assign(V, DFS_WHITE);
    dfs_parent.assign(V, -1);
    int idx = dfs(i);
    if(idx != -1){
      while(idx != -1){
        mapping[idx] = 0;
        idx = dfs_parent[idx];
      }
      return;
    }
  }
}

int main() {
  inputGraph();
  findCycle();
  for(int i = 0; i<mapping.size(); ++i)
    if(!mapping[i])
      bfs(i);
  for(int i = 0; i<mapping.size(); ++i)
    printf("%d ", mapping[i]);
  printf("\n");
  return 0;
}