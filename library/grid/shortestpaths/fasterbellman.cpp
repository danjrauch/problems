#include<bits/stdc++.h>
using namespace std;

#define INF 2147483647
typedef vector<int> vi; 
typedef vector<vector<int> > vvi; 
typedef pair<int, int> pii; 

int n, m; 
vector<vector<pair<int, int> > > graph; 

int betterSPforGraphs(int src, int dest){
  vi dist(graph.size(), INF); 
  dist[src] = 0; 
  queue<int> q; 
  q.push(src); 
  vi in_queue(graph.size(), 0); 
  in_queue[src] = 1; 
  while(!q.empty()){
    int u = q.front(); q.pop(); in_queue[u] = 0; 
    for(int i = 0; i<graph[u].size(); ++i){
      int v = graph[u][i].first, weightuv = graph[u][i].second; 
      if(dist[u] + weightuv < dist[v]){
        dist[v] = dist[u] + weightuv; 
        if(!in_queue[v]){
          q.push(v); 
          in_queue[v] = 1; 
        }
      }
    }
  }
  return dist[dest]; 
}

//proven to be slow for some reason
int betterSPforGrids(vvi grid, pii src, pii dest){
  int dr[] = {1, 0, -1, 0}; 
  int dc[] = {0, 1, 0, -1}; 
  vvi dist(grid.size()); 
  for(int i = 0; i<grid.size(); ++i){
    dist[i].resize(grid[i].size(), INF); 
  }
  dist[src.first][src.second] = grid[src.first][src.second]; 
  queue<pii> q; 
  q.push(src); 
  vvi in_queue(grid.size()); 
  for(int i = 0; i<grid.size(); ++i){
    in_queue[i].resize(grid[i].size(), 0); 
  }
  in_queue[src.first][src.second] = 1; 
  while(!q.empty()){
    pii u = q.front(); q.pop(); in_queue[u.first][u.second] = 0; 
    for(int i = 0; i<4; ++i){
      if(u.first+dr[i] >= 0 && u.first+dr[i] < grid.size() && u.second+dc[i] >= 0 && u.second+dc[i] < grid[u.first+dr[i]].size()){
        if(dist[u.first][u.second] + grid[u.first+dr[i]][u.second+dc[i]] < dist[u.first+dr[i]][u.second+dc[i]]){
          dist[u.first+dr[i]][u.second+dc[i]] = dist[u.first][u.second] + grid[u.first+dr[i]][u.second+dc[i]]; 
          if(!in_queue[u.first+dr[i]][u.second+dc[i]]){
            q.push(make_pair(u.first+dr[i], u.second+dc[i])); 
            in_queue[u.first+dr[i]][u.second+dc[i]]; 
          }
        }
      }
    }
  }
  return dist[dest.first][dest.second]; 
}

int main(){
  int tests; 
  scanf("%d", &tests); 
  for(int te = 0; te<tests; ++te){
    scanf("%d", &n); 
    scanf("%d", &m); 
    vvi grid(n); 
    for(int i = 0; i<n; ++i){
      grid[i].resize(m); 
      for(int j = 0; j<m; ++j){
        scanf("%d", &grid[i][j]); 
      }
    }
    int res = betterSPforGrids(grid, make_pair(0, 0), make_pair(n-1, m-1)); 
    printf("%d\n", res); 
  }
  return 0;
}