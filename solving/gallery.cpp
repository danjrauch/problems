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

int N, n, k, res=-1;
vector<vector<int> > graph;
vector<pair<int, pair<int, bool> > >v;
vector<int> sortedv;
map<string, bool> dp;

bool check(int c, vector<pair<int, pair<int, bool> > > vec){
  for(int i = 0; i<graph[c].size(); ++i){
    if(vec[graph[c][i]].second.second) return 0;
  }
  return 1;
}

void search(int t, int score, vector<pair<int, pair<int, bool> > > vec){
  string s;
  for(int i = 0; i<N*2; ++i) s+= (vec[i].second.second + '0');
  //printf("%s\n", s.c_str());
  if(dp[s] || score < res) return;
  if(t == k){
    if(score > res) res = score;
    if(dp.count(s) == 0) dp[s] = 1;
    return;
  }
  for(int i = 0; i<N*2; ++i){
    if(vec[sortedv[i]].second.second == 0 && check(sortedv[i], vec)){
      vec[sortedv[i]].second.second = 1;
      search(t+1, score-=vec[sortedv[i]].first, vec);
      vec[sortedv[i]].second.second = 0;
    }
  }
}

int main(){
  scanf("%d %d", &N, &k);
  while(N != 0 || k != 0){
    res = -1;
    graph.resize(N*2);
    v.resize(N*2);
    sortedv.resize(N*2);
    dp.clear();
    int score = 0;
    for(int i = 0; i<2*N; ++i){
      scanf("%d", &v[i].first);
      v[i].second.first = i;;
      v[i].second.second = 0;
      score += v[i].first;
    }
    vector<pair<int, pair<int, bool> > > orderv(v);
    sort(orderv.begin(), orderv.end());
    for(int i = 0; i<N*2; ++i) sortedv[i] = orderv[i].second.first;
    for(int i = 0; i<N*2; ++i){
      if(i % 2 == 0){
        if(i-1>=0) graph[i].push_back(i-1);
        if(i+1<N*2) graph[i].push_back(i+1);
        if(i+3<N*2) graph[i].push_back(i+3);
      }else{
        if(i-3>=0) graph[i].push_back(i-3);
        if(i-1>=0) graph[i].push_back(i-1);
        if(i+1<N*2) graph[i].push_back(i+1);
      }
    }
    search(0, score, v);
    printf("%d\n", res);
    scanf("%d %d", &N, &k);
  }
  return 0; 
}
