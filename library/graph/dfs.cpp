#include <bits/stdc++.h>
using namespace std; 

int t, v, e; 

//vector<pair<int, pair<int, int> > > edges;        .....for weighted graphs
vector<pair<int, int> > edges; 
vector<vector<int> > graph; 

vector<int> dists; 
vector<int> preds; 
vector<int> colors; 
vector<pair<int, int> > times; 

void graphIntake(){
  scanf("%d %d", &v, &e); 
  graph.resize(v); 
  dists.resize(v); preds.resize(v); colors.resize(v); times.resize(v); //       ......for dfs
  edges.resize(e);  
  int a, b; 
  for(int i = 0; i<e; ++i){
    scanf("%d %d", &a, &b); 
    graph[a].push_back(b); 
    edges.push_back(make_pair(a, b)); 
  }
}

void dfs_vis(int u){
  t++; 
  times[u].first = t; 
  colors[u] = 1; 
  for(int i = 0; i<graph[u].size(); ++i){
    if(colors[graph[u][i]] == 0){
      preds[graph[u][i]] = u; 
      dfs_vis(graph[u][i]); 
    }
  }
  colors[u] = 2; 
  t++; 
  times[u].second = t; 
}

void dfs(){
  for(int i = 0; i<v; ++i){
    colors[i] = 0; 
    preds[i] = -1; 
  }
  t = 0; 
  for(int i = 0; i<v; ++i){
    if(colors[i] == 0){
      dfs_vis(i); 
    }
  }
}

int main(){
  graphIntake(); 
  dfs(); 
}