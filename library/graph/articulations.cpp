#include<bits/stdc++.h>
using namespace std;

#define M 300005

#define ii pair<int,int> 
#define UNVISITED -1

vector<vector<int> > graph; 

int V, E; 

bool graphIntake(){
  scanf("%d %d", &V, &E); 
  graph.clear(); 
  graph.resize(V); 
  int a, b; 
  for(int i = 0; i<E; ++i){
    scanf("%d %d", &a, &b); 
    graph[a].push_back(b); 
    graph[b].push_back(a); 
  } 
  return true; 
}

int visited[M]; 
int ids[M];  
int low[M];
int parent[M]; 
int id, root, rootChildren; 

vector<ii> bridges; 
int isBreakpoint[M]; 

/*
Bridge and Breakpoint Finding 
----------------------------------------------------------------
*/

void articulationDFS(int u){
  low[u] = ids[u] = id++; 
  for(int v : graph[u]){
    if(ids[v] == UNVISITED){
      parent[v] = u; 
      if(u == root) rootChildren++; 
      articulationDFS(v); 
      if(low[v] >= ids[u]) isBreakpoint[u] = true; 
      if(low[v] > ids[u]) bridges.push_back(make_pair(u, v)); 
      low[u] = min(low[u], low[v]); 
    }else if(v != parent[u]) low[u] = min(low[u], ids[v]); 
  }
}

void findArticulations(){
  id = 0;
  fill(begin(ids), end(ids), UNVISITED); 
  for(int i = 0; i<V; ++i){
    if(ids[i] == UNVISITED){
      root = i; rootChildren = 0; 
      articulationDFS(i);
      isBreakpoint[root] = (rootChildren > 1); 
    }
  }
}

/*
----------------------------------------------------------------
*/

/*

int main(){
  graphIntake(); 
  findArticulations(); 
  printf("%d bridges\n", (int)bridges.size()); 
  for(int i = 0; i < (int)bridges.size(); ++i){
    printf("%d - %d\n", bridges[i].first, bridges[i].second); 
  }
  printf("\n"); 
  printf("breakpoints\n"); 
  for(int i = 0; i < V; ++i){
    if (isBreakpoint[i] == 1) printf("%d\n", i); 
  }
  printf("\n"); 
  return 0;
}

*/
