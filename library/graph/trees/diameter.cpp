#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <iomanip>
using namespace std;

vector<vector<int> > graph; //..a tree for this algorithm

int V, E; 

bool graphIntake(){
  if(scanf("%d %d", &V, &E) == EOF) return false; 
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

/*
 * Use DFS to determine the diameter of a tree, rooted or otherwise
 * */

pair<int, int> diameterUtil(int root){
  vector<int> dist(V+1, 0); 
  dist[root] = 1; 
  stack<int> s; 
  s.push(root); 
  while(!s.empty()){
    int u = s.top(); 
    s.pop(); 
    for(int i = 0; i<graph[u].size(); ++i){
      if(dist[graph[u][i]] != 0) continue; 
      s.push(graph[u][i]); 
      dist[graph[u][i]] = dist[u] + 1; 
    }
  }
  int mx = INT_MIN, node = -1; 
  for(int i = 1; i<=V; ++i){
    if(mx < dist[i]){
      mx = dist[i]; 
      node = i; 
    }
  }
  return make_pair(mx, node); 
}

int findDiameter(int root){
  pair<int, int> p1 = diameterUtil(root), p2; 
  p2 = diameterUtil(p1.second); 
  return p2.first; 
}

int main(){
  while(graphIntake()){
    for(int i = 0; i<V; ++i){
      printf("%d\n", findDiameter(i)); 
    }
  }
  return 0; 
}

