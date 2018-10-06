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

vector<vector<int> > graph;
pair<int, int> p, res;

bool isValid(int i, int k) { return i >= 0 && k >= 0 && k < graph[i].size() && i < 5; }

void inputGraph(){
  graph.resize(5);
  for(int i = 0; i<5; ++i){
    graph[i].resize(i+1);
    for(int k = 0; k<=i; ++k){
      scanf("%d", &graph[i][k]);
      if(graph[i][k] == 0){ p.first = i; p.second = k; }
    }
  }
}

pair<int, int> search(int i, int k, pair<int, int> score){
  int additive = 0;
  int route;
  if(isValid(i-2, k) && graph[i-2][k] != 0 && graph[i-1][k]*graph[i-2][k] > additive){
    additive = graph[i-1][k]*graph[i-2][k];
    route = 1;
  }
  if(isValid(i, k+2) && graph[i][k+2] != 0 && graph[i][k+1]*graph[i][k+2] > additive){
    additive = graph[i][k+1]*graph[i][k+2];
    route = 2;
  }
  if(isValid(i+2, k+2) && graph[i+2][k+2] != 0 && graph[i+1][k+1]*graph[i+2][k+2] > additive){
    additive = graph[i+1][k+1]*graph[i+2][k+2];
    route = 3;
  }
  if(isValid(i+2, k) && graph[i+2][k] != 0 && graph[i+1][k]*graph[i+2][k] > additive){
    additive = graph[i+1][k]*graph[i+2][k];
    route = 4;
  }
  if(isValid(i, k-2) && graph[i][k-2] != 0 && graph[i][k-1]*graph[i][k-2] > additive){
    additive = graph[i][k-1]*graph[i][k-2];
    route = 5;
  }
  if(isValid(i-2, k-2) && graph[i-2][k-2] != 0 && graph[i-1][k-1]*graph[i-2][k-2] > additive){
    additive = graph[i-1][k-1]*graph[i-2][k-2];
    route = 6;
  }
}

int main(){
  inputGraph();
  res = search(p.first, p.second, make_pair(0, 0));
  printf("%d\n", res.first - res.second);
  return 0;
}