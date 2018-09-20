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

#define INF 999999999

int n, res=INF;
vector<vector<pair<int, int> > > graph;
vector<string> v;

int numSame(string s, string ss){
  int res = 0; 
  for(int i = 0; i<s.size(); ++i){
    for(int k = 0; k<ss.size(); ++k){
      if(s.at(i) == ss.at(k)) res++;
    }
  }
  return res;
}

void search(int p, int mask, int c){
  if(mask == pow(2, n)-1) if(c < res){ res = c; return; }
  for(int i = 0; i<n; ++i){
    if(!(mask & (1 << i))){
      search(i, mask | (1<<i), c + graph[p][i].second);
    }
  }
}

int main(){
  scanf("%d", &n);
  v.resize(n); 
  graph.resize(n);
  for(int i = 0; i<n; ++i){
    cin >> v[i];
  }
  for(int i = 0; i<n; ++i){
    for(int k = i+1; k<n; ++k){
      int same = numSame(v[i], v[k]); 
      graph[i].push_back(make_pair(k, same)); 
      graph[k].push_back(make_pair(i, same)); 
    }
  }
  for(int i = 0; i<n; ++i)
    search(i, 0 ^ (1<<i), 0);
  printf("%d\n", res); 
  return 0; 
}

