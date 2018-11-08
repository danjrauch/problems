#include <bits/stdc++.h>
using namespace std; 

vector<vector<int> > graph; 
vector<pair<int, int> > edges; 

int v, e; 

void addEdge(int s, int d){
  graph[s].push_back(d); 
  graph[d].push_back(s);
  edges.push_back(make_pair(s, d)); 
}

struct subset{
  int parent; 
  int rank; 
};

/*Finds the representative of a set with path compression*/
int find(struct subset * subsets, int i){
  if (subsets[i].parent != i) subsets[i].parent = find(subsets, subsets[i].parent); 
  return subsets[i].parent; 
}

/*Combines two sets into one (higher rank higher up tree)*/
void Union(struct subset * subsets, int x, int y){
  int xroot = find(subsets, x); 
  int yroot = find(subsets, y); 
  if(subsets[xroot].rank < subsets[yroot].rank) subsets[xroot].parent = yroot; 
  else if(subsets[xroot].rank > subsets[yroot].rank) subsets[yroot].parent = xroot; 
  else {
    subsets[yroot].parent = xroot; 
    subsets[xroot].rank++; 
  }
}

struct subset* createSubsets(){
  struct subset* subsets = (struct subset*) malloc(v * sizeof(struct subset)); 
  for(int i = 0; i<v; ++i){
    subsets[i].parent = i; 
    subsets[i].rank = 0; 
  }
  return subsets; 
}

/*creates the subset array for the graph without checking for cycle*/
void createSets(struct subset * subsets){
  for(int i = 0; i<e; ++i){
    int x = find(subsets, edges[i].first); 
    int y = find(subsets, edges[i].second); 
    Union(subsets, x, y); 
  }
}

/*calculates the number of connected components*/
int numOfConnectedComponents(struct subset* subsets){
  for(int i = 0; i<v; ++i) find(subsets, i); 
  int n = 0; 
  map<int, bool> m; 
  for(int i = 0; i<v; ++i){
    if(m[subsets[i].parent]) continue; 
    m[subsets[i].parent] = 1; 
    n++; 
  }
  return n; 
}

int main(){
  scanf("%d %d", &v, &e); 
  graph.resize(v); 
  struct subset* subsets = createSubsets(); 
  int a, b; 
  for(int i = 0; i<e; ++i){
    scanf("%d %d", &a, &b); 
    addEdge(a-1, b-1); 
  }
  
}