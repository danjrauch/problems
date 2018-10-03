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

struct point {
  double x, y;
  point() { x = y = 0.0; }
  point(double _x, double _y) : x(_x), y(_y) {}
  bool operator < (point other) const{
    if(fabs(x - other.x) > EPS) return x < other.x;
    return y < other.y;
  }
  bool operator == (point other) const{
    return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
  }
};

struct line {
  line(double _a, double _b, double _c) : a(_a), b(_b), c(_c) {}
  line() : a(0), b(0), c(0) {}
  double a, b, c;
};

double solveForY(line l, double x){
  return (-l.c-(l.a*x))*(1/l.b);
}

double solveForX(line l, double y){
  return ((-l.b*y)-l.c)*(1/l.a);
}

bool isVertical(line l){
  return l.b == 0;
}

double dist(point p1, point p2){
    return hypot(p1.x - p2.x, p1.y - p2.y);
}

bool areParallel(line l1, line l2){
    return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
}

bool areIntersect(line l1, line l2, point &p){
  if(areParallel(l1, l2)) return false;
  p.x = (l2.b*l1.c - l1.b*l2.c) / (l2.a*l1.b - l1.a*l2.b);
  if(fabs(l1.b) > EPS) p.y = -(l1.a*p.x + l1.c);
  else                 p.y = -(l2.a*p.x + l2.c);
  return true;
}

int n, m;

double r;

vector<point> points;
vector<line>  lines;
vector<int>   masks;

//Use Euler's characteristic: F=1+E-V
int numFaces(){
  int res = m+1; 
  for(int i = 0; i<m-1; ++i){
    point p(-1000, -1000);
    for(int k = i+1; k<m; ++k){
      if(areIntersect(lines[i], lines[k], p) && dist(point(0,0), p)<r){
        res++;
      }
    }
  }
  return res;
}

int main(){
  scanf("%d %d %lf", &n, &m, &r);
  points.resize(n);
  masks.resize(n);
  lines.resize(m);
  for(int i = 0; i<n; ++i){
    scanf("%lf %lf", &points[i].x, &points[i].y);
  }
  for(int i = 0; i<m; ++i){
    scanf("%lf %lf %lf", &lines[i].a, &lines[i].b, &lines[i].c);
  }
  for(int i = 0; i<m; ++i){
    if(isVertical(lines[i])){
      double xval = -lines[i].c / lines[i].a;
      for(int k = 0; k<n; ++k){
        if(points[k].x < xval) {
          masks[k] = masks[k] | (1<<i);
        }
      }
    }
    else{
      for(int k = 0; k<n; ++k){
        if(points[k].y > solveForY(lines[i], points[k].x)){
          masks[k] = masks[k] | (1<<i);
        }
      }
    }
  }
  map<int, bool> m;
  bool good = true;
  for(int i = 0; i<masks.size(); ++i){
    if(m.count(masks[i])){
      good = false;
      break;
    }
    m[masks[i]] = 1;
  }
  // printf("%d %d\n", numFaces(), n);
  if(numFaces() != n) good = false;
  printf("%s\n", good?"yes":"no");
  return 0;
}
