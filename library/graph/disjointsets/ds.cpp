#include <bits/stdc++.h>
using namespace std; 

vector<vector<int> > graph; 
// vector<int> colors; 
// vector<pair<int, int> > times; 
// vector<int> preds; 
vector<pair<int, int> > edges; 

int v, e, a, b, we, t, numComps; 
int tempRank; 

void addEdge(int s, int d){
  graph[s].push_back(d); 
  graph[d].push_back(s); 
  edges.push_back(make_pair(s, d));
}

void graphIntake(){
  scanf("%d", &v); 
  e = v; 
  graph.resize(v); 
  for(int i = 0; i<e; ++i){
    scanf("%d", &a); 
    addEdge(i, a-1);
  }
}

typedef struct subset{
  int parent; 
  int rank; 
}subset;

subset* subsets; 

/*Finds the representative of a set with path compression*/
int find(int i){
  if (subsets[i].parent != i) subsets[i].parent = find(subsets[i].parent); 
  return subsets[i].parent; 
}

/*Combines two sets into one (higher rank higher up tree)*/
void Union(int x, int y){
  int xroot = find(x); 
  int yroot = find(y); 
  if(subsets[xroot].rank < subsets[yroot].rank) subsets[xroot].parent = yroot; 
  else if(subsets[xroot].rank > subsets[yroot].rank) subsets[yroot].parent = xroot; 
  else {
    subsets[yroot].parent = xroot; 
    subsets[xroot].rank++; 
  } 
}

void createSubsets(){
  subsets = (subset*) malloc(v * sizeof(subset)); 
  for(int i = 0; i<v; ++i){
    subsets[i].parent = i; 
    subsets[i].rank = 0; 
  }
}

void zeroSubsets(){
  for(int i = 0; i<v; ++i){
    subsets[i].parent = i; 
    subsets[i].rank = 0; 
  }
}

/*creates the subset array for the graph without checking for cycle*/
void createSets(){
  for(int i = 0; i<edges.size(); ++i){
    int x = find(edges[i].first); 
    int y = find(edges[i].second); 
    Union(x, y); 
  }
}

/*calculates the number of connected components*/
int numOfConnectedComponents(){
  for(int i = 0; i<v; ++i) find(i); //compress all the paths
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
  graphIntake(); 
  createSubsets();
  createSets(); 
  int j = numOfConnectedComponents(); 
  printf("%d\n", j); 
  return 0; 
}