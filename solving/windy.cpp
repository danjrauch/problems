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

#define EPS 1e-9
#define pi acos(-1.0)

struct point{
  double x, y;
  point() { x=y=0.0; }
  point(double _x, double _y) : x(_x), y(_y) {}
  bool operator < (point other) const{
    if(fabs(x - other.x) > EPS) return x < other.x;
    return y < other.y;
  }
  bool operator == (point other) const{
    return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
  }
};

struct vec{
  double x, y;
  vec(double _x, double _y) : x(_x), y(_y) {}
};

vec toVec(point a, point b){
  return vec(b.x - a.x, b.y - a.y);
}

double cross(vec a, vec b){
  return a.x * b.y - a.y * b.x;
}

bool ccw(point p, point q, point r){
  return cross(toVec(p, q), toVec(p, r)) > 0;
}

int n;
vector<vector<pair<bool, pair<point, point> > > > graph;
vector<point> res;
vector<bool> visited;
map<point, int> pToG;
vector<point> v;
string dir;

void search(vector<bool> vis, vector<> segs, int pos, vector<point> r){
  if(pos == dir.size()) { copy(r.begin(), r.end(), back_inserter(res)); return; }
  point source = r[r.size()-2];
  point inter = r[r.size()-1];
  point dest;
  int d = dir.at(pos)=='L'?0:1;
  for(int i = 0; i<graph[sourcePos].size(); ++i){
    inter = graph[sourcePos][i].second.first;
    dest = graph[sourcePos][i].second.second;
    bool interVis = vis[pToG[inter]];
    bool destVis = vis[pToG[dest]];
    if(graph[sourcePos][i].first == d && !interVis  && !destVis){
      vis[pToG[inter]] = true; 
      vis[pToG[dest]] = true;
      pos++;
      r.push_back(inter);
      r.push_back(dest);
      search(vis, pos, r);
    }
  }
}

int main(){
  scanf("%d", &n);
  graph.resize(n);
  v.resize(n);
  visited.resize(n);
  for(int i = 0; i<n; ++i){
    scanf("%lf %lf", &v[i].x, &v[i].y);
    pToG[v[i]] = i;
  }
  for(int i = 0; i<n; ++i){
    for(int k = 0; k<n; ++k){
      if(k == i) continue;
      for(int j = 0; j<n; ++j){
        if(j == i || j == k) continue;
        if(ccw(v[i], v[k], v[j])){
          graph[pToG[v[i]]].push_back(make_pair(0, make_pair(v[k], v[j])));
        }else{
          graph[pToG[v[i]]].push_back(make_pair(1, make_pair(v[k], v[j])));
        }
      }
    }
  }
  //for(int i = 0; i<n; ++i){
  //  printf("%d (%lf, %lf)\n", i, v[i].x, v[i].y);
  //  for(int k = 0; k<graph[i].size(); ++k){
  //    int d = graph[i][k].first;
  //    point e = graph[i][k].second.first;
  //    point f = graph[i][k].second.second;
  //    printf("    %d -> (%lf, %lf) -> (%lf, %lf)\n", d, e.x, e.y, f.x, f.y);
  //  }
  //}
  for(int i = 0; i<n; ++i){
    vector<point> m; m.push_back(v[i]);
    search(visited, 0, m);
  }
  for(int i = 0; i<res.size(); ++i){
    printf("%d ", pToG[res[i]]+1);
  }
  printf("\n");
  return 0;
}

