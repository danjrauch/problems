#include <bits/stdc++.h>
using namespace std; 

#define INF 999999999

int t, V, e, we, source; 

vector<pair<int, pair<int, int> > > edges; 
vector<vector<int> > graph; 

//input function for graph intake
void graphIntake(){
  scanf("%d", &source); 
  int a, b; 
  graph.resize(V); 
  scanf("%d %d", &a, &b); 
  while(!(a == 0 && b == 0)){
    graph[a-1].push_back(b-1); 
    scanf("%d %d", &a, &b); 
  }
}

//untility function for toposort
void topoSortUtil(int v, bool visited[], deque<int> &topoList){
  visited[v] = true; 
  for(int i = 0; i<graph[v].size(); ++i){
    if(!visited[graph[v][i]]){
      topoSortUtil(graph[v][i], visited, topoList); 
    }
  }
  topoList.push_front(v); 
}

//executes topological sort - returns deque with sorted list
deque<int> topoSort(){
  deque<int> topoList; 
  bool *visited = new bool[V]; 
  for(int i = 0; i<V; ++i){
    visited[i] = false; 
  }
  for(int i = 0; i<V; ++i){
    if(visited[i] == false){
      topoSortUtil(i, visited, topoList); 
    }
  }
  return topoList; 
}

vector<int> spdists; vector<int> sppreds;

void initss(int numofvertices, int s){
  spdists.resize(numofvertices); 
  sppreds.resize(numofvertices); 
  for(int i = 0; i<numofvertices; ++i){
    spdists[i] = INF; 
    sppreds[i] = -1; 
  }
  spdists[s] = 0; 
}

void relax(int s, int d, int w){
  if(spdists[d] > spdists[s] + w){
    spdists[d] = spdists[s] + w; 
    sppreds[d] = s; 
  }
}

void dagsp(int s){
  deque<int> toposorted = topoSort(); 
  initss(V, s);
  for(int i = 0; i<V; ++i){
    for(int k = 0; k<graph[toposorted[i]].size(); ++k){
      relax(toposorted[i], graph[toposorted[i]][k], 1); 
    }
  } 
}

int main(){
  scanf("%d", &V); 
  while(V!=0){
    graphIntake();
    deque<int> tlist = topoSort(); 
    for(int i = 0; i<tlist.size(); ++i){
      printf("%d ", tlist[i]); 
    }
    printf("\n"); 
    scanf("%d", &V); 
  }
}