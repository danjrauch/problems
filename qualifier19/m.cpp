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
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int, int> pii;

int n;

#define EPS 1e-9
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

double dist(point p1, point p2){
  return hypot(p1.x - p2.x, p1.y - p2.y);
}

struct vec{
    double x, y; 
    vec(double _x, double _y) : x(_x), y(_y) {} 
}; 

vec toVec(point a, point b){
    return vec(b.x - a.x, b.y - a.y);
}

//s is nonnegative in [<1, 1, >1]
vec scale(vec v, double s){
    return vec(v.x * s, v.y * s); 
}

//translate p by v's values
point translate(point p, vec v){
    return point(p.x + v.x, p.y + v.y); 
}

//dot product 
double dot(vec a, vec b){
    return (a.x * b.x + a.y * b.y); 
}

double norm_sq(vec v){
    return v.x * v.x + v.y * v.y; 
}

//return the distance form p to the line defined by
//two points a and b (a and b must be different)
//the closest point is stored in the 4th parameter (byref)
double distToLine(point p, point a, point b, point &c){
    // formula: c = a + u & ab
    vec ap = toVec(a, p), ab = toVec(a, b); 
    double u = dot(ap, ab) / norm_sq(ab); 
    c = translate(a, scale(ab, u)); 
    return dist(p, c); 
}

//returns the distance from p to the line segment ab defined by
//two points a and b (still ok if a == b)
//the closest point is stored in the 4th parameter (byref)
double distToLineSegment(point p, point a, point b, point &c){
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab); 
    if (u < 0.0){
        c = point(a.x, a.y); 
        return dist(p, a); 
    } 
    if (u > 1.0){
        c = point(b.x, b.y); 
        return dist(p, b); 
    }
    return distToLine(p, a, b, c); 
}

//since oa dot ob = abs(oa) * abs(ob) * cos(theta), 
//we have theta = arccos(oa dot ob/(abs(oa) * abs(ob)))
double angle(point a, point o, point b){
    vec oa = toVec(o, a), ob = toVec(o, b); 
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); 
}

double cross(vec a, vec b){
    return a.x * b.y - a.y * b.x; 
}

//note: to accept collinear points, we have to change the '>0'
//returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r){
    return cross(toVec(p, q), toVec(p, r)) > 0; 
}

bool collinear(point p, point q, point r){
    return fabs(cross(toVec(p, q), toVec(p, r))) < EPS; 
}

//angle sorting function for Graham's Scan 
point pivot(0, 0); 
bool angleCmp(point a, point b){
    if(collinear(pivot, a, b))
        return dist(pivot, a) < dist(pivot, b); 
    double d1x = a.x - pivot.x, d1y = a.y - pivot.y; 
    double d2x = b.x - pivot.x, d2y = b.y - pivot.y; 
    return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0; 
}

//Graham's Scan 
//returns a polygon of the convex hull in counter-clockwise order.
vector<point> CHslower(vector<point> P){
    int i, j, n = (int)P.size(); 
    if(n <= 3){
        if(!(P[0] == P[n-1])) P.push_back(P[0]); //safeguard from corner case
        return P;                                //special case, CH is P itself
    }

    //first, find P0 = point with lowest Y and if tie: rightmost x
    int P0 = 0; 
    for(i = 1; i<n; ++i){
        if(P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x))
            P0 = i; 
    }

    point temp = P[0]; P[0] = P[P0]; P[P0] = temp; 

    //second, sort points by angle w.r.t. pivot P0
    pivot = P[0]; 
    sort(++P.begin(), P.end(), angleCmp); 

    //third, the ccw tests
    vector<point> S; 
    S.push_back(P[n-1]); 
    S.push_back(P[0]); 
    S.push_back(P[1]); 
    i = 2; 
    while(i<n){
        j = (int)S.size()-1; 
        if(ccw(S[j-1], S[j], P[i]))
            S.push_back(P[i++]); 
        else
            S.pop_back(); 
    }
    return S; 
}

//points should wrap counter clockwise, with last point being
//the same as the first point
vector<point> inputPolygon(int n){
  vector<point> P; 
  set<point> curr;
  for(int i = 0; i<n; ++i){
    point p;
    scanf("%lf %lf", &p.x, &p.y); 
    if(curr.count(p) == 0){
      P.push_back(p);
      curr.insert(p);
    }
  }
  // P.push_back(P[0]); 
  return P; 
}

//returns the area, which is half the determinant
double area(const vector<point> &P){
    double result = 0.0, x1, y1, x2, y2;
    for(int i = 0; i< (int)P.size()-1; ++i){
        x1 = P[i].x; x2 = P[i+1].x; 
        y1 = P[i].y; y2 = P[i+1].y; 
        result += (x1 * y2 - x2 * y1); 
    }
    return fabs(result) / 2.0; 
}

//routine for getting the center of mass of the polygon
point center; 
void getCenterPoint(const vector<point> &P){
    double X = 0, Y = 0; 
    for(int i = 0; i<(int)P.size(); ++i){
        X += P[i].x; 
        Y += P[i].y; 
    }
    center.x = X/P.size(); 
    center.y = Y/P.size(); 
}

//comparison routine for the later sorting of the polygon
//take this with a grain of shit
bool L(const point &a, const point &b){
    if (a.x - center.x >= 0 && b.x - center.x < 0)
        return true;
    if (a.x - center.x < 0 && b.x - center.x >= 0)
        return false;
    if (a.x - center.x == 0 && b.x - center.x == 0) {
        if (a.y - center.y >= 0 || b.y - center.y >= 0)
            return a.y > b.y;
        return b.y > a.y;
    }

    // compute the cross product of vectors (center -> a) x (center -> b)
    double det = (a.x - center.x) * (b.y - center.y) - (b.x - center.x) * (a.y - center.y);
    if (det > 0)
        return true;
    if (det < 0)
        return false;

    // points a and b are on the same line from the center
    // check which point is closer to the center
    double d1 = (a.x - center.x) * (a.x - center.x) + (a.y - center.y) * (a.y - center.y);
    double d2 = (b.x - center.x) * (b.x - center.x) + (b.y - center.y) * (b.y - center.y);
    return d1 > d2;
}

vector<bool> ext;

int main(){
  scanf("%d", &n);
  vector<point> G = inputPolygon(n*3);
  getCenterPoint(G); 
  sort(G.begin(), G.end(), L); 
  G.push_back(G[0]);
  G = CHslower(G);
  scanf("%d", &n);
  vector<point> J = inputPolygon(n*3);
  getCenterPoint(J);
  sort(J.begin(), J.end(), L);
  J.push_back(J[0]);
  J = CHslower(J);
  if(J.size() != G.size() || fabs(area(J) - area(G)) > EPS){
    printf("no\n");
    return 0;
  }
  for(int i = 0; i<G.size(); ++i){
    if(G[i].x != J[i].x || G[i].y != J[i].y){
      printf("no\n");
      return 0;
    }
  }
  printf("yes\n");
  // if(J.size()>G.size()){
  //   ext.resize(J.size()-1);
  //   for(int i = 0; i<J.size()-2; ++i){
  //     if(collinear(J[i], J[i+1], J[i+2])){
  //       ext[i+1] = 1;
  //     }
  //   }
  //   vector<point> newJ; 
  //   for(int i = 0; i<ext.size(); ++i){
  //     if(!ext[i]) newJ.push_back(J[i]);
  //   }
  //   J = newJ;
  // }
  // else{
  //   ext.resize(G.size()-1);
  //   for(int i = 0; i<G.size()-2; ++i){
  //     if(collinear(G[i], G[i+1], G[i+2])){
  //       ext[i+1] = 1;
  //     }
  //   }
  //   vector<point> newG; 
  //   for(int i = 0; i<ext.size(); ++i){
  //     if(!ext[i]) newG.push_back(G[i]);
  //   }
  //   G = newG;
  // }
  // for(int i = 0; i<G.size(); ++i){
  //   printf("(%lf, %lf) ", G[i].x, G[i].y);
  // }
  // printf("\n\n");
  // for(int i = 0; i<J.size(); ++i){
  //   printf("(%lf, %lf) ", J[i].x, J[i].y);
  // }
  // printf("\n");
  return 0;
}