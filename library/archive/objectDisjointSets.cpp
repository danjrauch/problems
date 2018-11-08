#include <bits/stdc++.h>
using namespace std; 

/*Uses disjoint sets with path compression to find a cycle in a graph if it exists*/

struct Edge{
  int src, dest; 
};

struct Graph{
  int V, E; 
  struct Edge * edge; 
};

struct subset{
  int parent; 
  int rank; 
};

struct Graph * createGraph(int V, int E){
  struct Graph * graph = (struct Graph*) malloc(sizeof(struct Graph)); 
  graph -> V = V; 
  graph -> E = E; 
  graph -> edge = (struct Edge*) malloc(graph->E * sizeof(struct Edge)); 
  return graph; 
}

/*Finds the representative of a set with path compression*/
int find(struct subset subsets[], int i){
  if (subsets[i].parent != i) subsets[i].parent = find(subsets, subsets[i].parent); 
  return subsets[i].parent; 
}

/*Combines two sets into one (higher rank higher up tree)*/
void Union(struct subset subsets[], int x, int y){
  int xroot = find(subsets, x); 
  int yroot = find(subsets, y); 
  if(subsets[xroot].rank < subsets[yroot].rank) subsets[xroot].parent = yroot; 
  else if(subsets[xroot].rank > subsets[yroot].rank) subsets[yroot].parent = xroot; 
  else {
    subsets[yroot].parent = xroot; 
    subsets[xroot].rank++; 
  }
}

/*creates the subset array for the graph without checking for cycle*/
void createSets(struct Graph* graph, struct subset * subsets){
  for(int e = 0; e<graph->E; ++e){
    int x = find(subsets, graph->edge[e].src); 
    int y = find(subsets, graph->edge[e].dest); 
    Union(subsets, x, y); 
  }
}

/*calculates the number of connected components*/
int numOfConnectedComponents(struct Graph* graph, struct subset* subsets){
  int n = 0; 
  map<int, bool> m; 
  for(int i = 0; i<graph->V; ++i){
    if(m[subsets[i].parent]) continue; 
    m[subsets[i].parent] = 1; 
    n++; 
  }
  return n; 
}

/*sets up subset array and checks for the existance of a cycle during*/
int isCycle(struct Graph* graph, struct subset* subsets){
  int cycle = 0; 
  for(int e = 0; e<graph->E; ++e){
    int x = find(subsets, graph->edge[e].src); 
    int y = find(subsets, graph->edge[e].dest); 
    if(x == y) cycle = 1; 
    Union(subsets, x, y); 
  }
  return cycle;  
}

int main(){
  int V = 3, E = 3; 
  struct Graph* graph = createGraph(V, E); 
  struct subset* subsets =  (struct subset*) malloc(graph->V * sizeof(struct subset)); 
  for(int i = 0; i<V; ++i){
    subsets[i].parent = i; 
    subsets[i].rank = 0; 
    printf("%d %d\n", i, 0);
  }
  printf("----------------------\n"); 
  graph->edge[0].src = 0; 
  graph->edge[0].dest = 1; 
  graph->edge[1].src = 1; 
  graph->edge[1].dest = 2;
  graph->edge[2].src = 2; 
  graph->edge[2].dest = 0; 
  // graph->edge[2].src = 0;
  // graph->edge[2].src = 2;

  if(isCycle(graph, subsets)) printf("cycle\n"); 
  else printf("no cycle\n");
  int n = numOfConnectedComponents(graph, subsets); 
  printf("%d\n", n); 
  for(int i =0 ; i<V; ++i){
    printf("%d %d\n", subsets[i].parent, subsets[i].rank); 
  }
}