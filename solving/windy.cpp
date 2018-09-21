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

#define EPS 1e-9;
#define pi acos(-1.0);

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
  return crosss(toVec(p, q), toVec(p, r)) > 0;
}

bool ccw(point p, point q, point r){
  return cross(toVec(p, q), toVec(p, r)) > 0;
}

int n;



int main(){
  
  return 0; 
}

