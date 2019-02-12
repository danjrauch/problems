#include<bits/stdc++.h>
using namespace std;
#define INF 2147483647
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> pii;

int n, v, e;
vector<vector<pii>> graph; 
vector<pair<int, pii>> edges; 

vi dists; // used for all graphs simultaneously for bellmanford
vi preds; // used for all graphs simultaneously for bellmanford
 
void graphIntake(){
  scanf("%d %d", &v, &e); 
  graph.resize(v); 
  int a, b, we; 
  for(int i = 0; i<e; ++i){
    scanf("%d %d %d", &a, &b, &we); 
    graph[a].push_back(make_pair(b, we));
    edges.push_back(make_pair(we, make_pair(a, b)));  
  }
}

void initss(int numofvertices, int s){
  dists.resize(numofvertices); 
  preds.resize(numofvertices); 
  for(int i = 0; i<numofvertices; ++i){
    dists[i] = INF; 
    preds[i] = -1; 
  }
  dists[s] = 0; 
}

void relax(int u, int v, int w){
  if(dists[v] > dists[u]+w){
    dists[v] = dists[u]+w; 
    preds[v] = u; 
  }
}

bool bellmanford(vector<vector<pair<int, int> > > g, int s){
  initss(v, s); 
  for(int i = 0; i<v-1; ++i)
    for(int k = 0; k<e; ++k)
      relax(edges[k].second.first, edges[k].second.second, edges[k].first); 
  for(int i = 0; i<e; ++i)
    if(dists[edges[i].second.second] > dists[edges[i].second.first] + edges[i].first)
      return false; 
  return true; 
}

int main(){
  graphIntake(); 
  bellmanford(graph, 3); 
}