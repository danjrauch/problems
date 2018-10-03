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
#define INF 2147483647

#define EPS 1e-12
#define pi acos(-1.0)

int n, r;
vector<vector<pair<int, int> > > graph;
vector<bool> res;
// bool vis[50001];

void search(int orig, int prev, int cur, int pcolor){
  for(int i = 0; i<graph[cur].size(); ++i){
    if(graph[cur][i].first == prev) continue;
    if(graph[cur][i].second == pcolor){
      res[graph[cur][i].first] = res[orig] = 1;
      r-=2;
    }
    if(!res[orig]) search(orig, cur, graph[cur][i].first, graph[cur][i].second);
  }
}

int main(){
  scanf("%d", &n);
  r = n;
  graph.resize(n+1);
  res.resize(n+1);
  for(int i = 0; i<n-1; ++i){
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    graph[a].push_back(make_pair(b, c));
    graph[b].push_back(make_pair(a, c));
  }
  for(int i = 1; i<=n; ++i){
    if(!res[i]) search(i, i, i, -1);
  }
  printf("%d\n", r);
  for(int i = 1; i<=n; ++i){
    if(!res[i]) printf("%d\n", i);
  } 
  return 0;
}