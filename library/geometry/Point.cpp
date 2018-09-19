#include <bits/stdc++.h>
using namespace std;

int n;

#define EPS 1e-9
#define pi acos(-1.0)

struct point_i {
  int x, y;
  point_i() { x = y = 0; }
  point_i(int _x, int _y) : x(_x), y(_y) {}
};

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

double dist(point p1, point p2){
  return hypot(p1.x - p2.x, p1.y - p2.y);
}

point rotate(point p, double theta){
  double rad = (pi/180.0) * theta;
  return point(p.x*cos(rad) - p.y*sin(rad), p.x*sin(rad) + p.y*cos(rad));
}

int main(){
  point P1(0,0), P2(0,0), P3(0,1), P4(10,3);
  printf("%d\n", P1==P2);
  printf("%d\n", P1==P3);
  n = dist(P1, P3);
  printf("%d\n", n);
  point p = rotate(P4, 180);
  printf("%lf %lf\n", p.x, p.y);
  return 0;
}
