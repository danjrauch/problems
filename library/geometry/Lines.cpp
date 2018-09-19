#include <bits/stdc++.h>
using namespace std;

int n;

#define EPS 1e-9
#define pi acos(-1.0)

struct line { double a, b, c; };

void pointsToLine(point p1, point p2, line &l){
  if(fabs(p1.x - p2.x) < EPS){
    l.a = 1.0; l.b = 0.0; l.c = -p1.x;
  }
  else{
    l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
    l.b = 1.0;
    l.c = -(double)(l.a * p1.x) - p1.y;
  }
}

bool areParallel(line l1, line l2){
  return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
}

bool areSame(line l1, line l2){
  return areParallel(l1, l2) && (fabs(l1.c - l2.c) < EPS);
}

bool areIntersect(line l1, line l2, point &p){
  if(areParallel(l1, l2)) return false;
  p.x = (l2.b*l1.c - l1.b*l2.c) / (l2.a*l1.b - l1.a*l2.b);
  if(fabs(l1.b) > EPS) p.y = -(l1.a*p.x + l1.c);
  else                 p.y = -(l2.a*p.x + l2.c);
  return true;
}
