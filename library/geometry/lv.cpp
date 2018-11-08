#include<bits/stdc++.h>
using namespace std;
#define INF 2147483647
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int, int> pii;

int n;

#define EPS 1e-12
#define pi acos(-1.0)

//POINTS
struct point_i {
  int x, y;
  point_i() { x = y = 0; }
  point_i(int _x, int _y) : x(_x), y(_y) {}
  bool operator < (point_i other) const{
    if(x == other.x) return x < other.x;
      return y < other.y;
  }
  bool operator == (point_i other) const{
    return x == other.x && y == other.y;
  }
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

struct point3D {
  double x, y, z;
  point3D() { x = y = z = 0; }
  point3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
  bool operator < (point3D b) const{
    if (x == b.x){
      if (y == b.y){
        if (z == b.z) return true; else return (z < b.z);
      }
      else return (y < b.y);
    }
    else{
      return (x < b.x);
    } 
  }
  bool operator == (point3D other) const{
    return x == other.x && y == other.y && z == other.z;
  }
};

struct pointPolar {
  double r, ang; 
  pointPolar() { r = ang = 0; } 
  pointPolar(double _x, double _y) : r(sqrt(_x*_x+_y*_y)), ang(atan2(_y, _x)) {}
  bool operator < (pointPolar b) const{
    if(fabs(ang - b.ang) > EPS) return ang < b.ang;
    return r < b.r;
  }
  bool operator == (pointPolar other) const{
    return ang == other.ang && r == other.r;
  }
  double getY(){
    return r*sin(ang); 
  }
  double getX(){
    return r*cos(ang); 
  }
};

double dist3D(point3D p1, point3D p2){
  return sqrt(pow((p1.x-p2.x), 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

double dist(point p1, point p2){
  return hypot(p1.x - p2.x, p1.y - p2.y);
}

//rotate p by theta degrees ccw w.r.t. origin (0,0)
point rotate(point p, double theta){
  double rad = (pi/180.0) * theta;
  return point(p.x*cos(rad) - p.y*sin(rad), p.x*sin(rad) + p.y*cos(rad));
}

//LINES
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

line pointsToLine(point p1, point p2){
  line l(0, 0, 0); 
  if(fabs(p1.x - p2.x) < EPS){
    l.a = 1.0; l.b = 0.0; l.c = -p1.x;
  }
  else{
    l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
    l.b = 1.0;
    l.c = -(double)(l.a * p1.x) - p1.y;
  }
  return l; 
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

//VECTORS
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

// Segment intersection

//used for segment intersection and triangulation
double area2(point a, point b, point c){
  return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

bool left(point a, point b, point c){
  return area2(a, b, c) > EPS;
}

bool leftOn(point a, point b, point c){
  return area2(a, b, c) >= 0;
}

// bool collinear(point a, point b, point c){
//   return area2(a, b, c) < EPS;
// }

bool Xor(bool x, bool y){
  return !x ^ !y;
}

//tests if two segments ab and cd are properly intersecting (not between)
bool intersect_prop(point a, point b, point c, point d){
  if(collinear(a,b,c) || collinear(a,b,d) || collinear(c,d,a) || collinear(c,d,b)) return false;
  return Xor(left(a,b,c), left(a,b,d)) && Xor(left(c,d,a), left(c,d,b));
}

//test if point c is incident on segment ab
bool between(point a, point b, point c){
  point ba, ca;
  if(!collinear(a,b,c)) return false;
  if(fabs(a.x-b.x) > EPS)
    return ((((a.x < c.x) || fabs(a.x-c.x) < EPS) && ((c.x < b.x) || fabs(c.x-b.x) < EPS)) || 
            (((a.x > c.x) || fabs(a.x-c.x) < EPS) && ((c.x > b.x) || fabs(c.x-b.x) < EPS)));
  else 
    return ((((a.y < c.y) || fabs(a.y-c.y) < EPS) && ((c.y < b.y) || fabs(c.y-b.y) < EPS)) || 
            (((a.y > c.y) || fabs(a.y-c.y) < EPS) && ((c.y > b.y) || fabs(c.y-b.y) < EPS)));
}

//tests for segment intersection between ab and cd
//can do vertical, horizontal, and other segments
//segments that start/end on other segment count as intersecting
bool intersect(point a, point b, point c, point d, point &p){
  if(intersect_prop(a, b, c, d)){
    areIntersect(pointsToLine(a, b), pointsToLine(c, d), p);
    return true;
  } 
  else if(between(a,b,c)){
    p.x = c.x; p.y = c.y; return true;
  } 
  else if(between(a,b,d)){
    p.x = d.x; p.y = d.y; return true;
  } 
  else if(between (c,d,a)){
    p.x = a.x; p.y = a.y; return true;
  } 
  else if(between(c,d,b)){
    p.x = b.x; p.y = b.y; return true;
  }
  else return false;
}

//Triangles 
double area(double ab, double bc, double ca){
  double halfperim = (ab+bc+ca)/2; 
  return sqrt(halfperim*(halfperim-ab)*(halfperim-bc)*(halfperim-ca)); 
}

double perimeter(double ab, double bc, double ca){
  return ab+bc+ca; 
}

//A triangle with area A and semi-perimeter s has an inscribed circle (incircle) with radius r = A/s
double rInCircle(double ab, double bc, double ca) {
  return area(ab, bc, ca) / (0.5 * perimeter(ab, bc, ca));
}
double rInCircle(point a, point b, point c) {
  return rInCircle(dist(a, b), dist(b, c), dist(c, a));
}

//find the center of the incircle in the triangle
int inCircle(point p1, point p2, point p3, point &ctr, double &r){
  r = rInCircle(p1, p2, p3); 
  if (fabs(r) < EPS) return 0; 

  line l1, l2; //compute the angle bisectors
  double ratio = dist(p1, p2) / dist(p1, p3); 
  point p = translate(p2, scale(toVec(p2, p3), ratio / (1 + ratio))); 
  l1 = pointsToLine(p1, p); 

  ratio = dist(p2, p1) / dist(p2, p3); 
  p = translate(p1, scale(toVec(p1, p3), ratio / (1 + ratio))); 
  l2 = pointsToLine(p2, p); 

  areIntersect(l1, l2, ctr); 
  return 1; 
}

//find the radius of the circumcircle around a triangle
//sides version
double rCircumCircle(double ab, double bc, double ca){
  return ab * bc * ca / (4.0 * area(ab, bc, ca)); 
}

//points version
double rCircumCircle(point a, point b, point c){
  return rCircumCircle(dist(a, b), dist(b, c), dist(c, a)); 
}

//Circles --- might need triangles
int insideCircle(point p, point c, double r){
  double dx = p.x - c.x, dy = p.y - c.y;
  double Euc = dx * dx + dy * dy, rSq = r*r;
  return Euc < rSq ? 0 : fabs(Euc - rSq) < EPS ? 1 : 2;
}

bool circle2PtsRad(point p1, point p2, double r, point &c) {
  double d2 = (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y); double det = r * r / d2 - 0.25;
  if (det < 0.0) return false;
  double h = sqrt(det);
  c.x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
  c.y = (p1.y + p2.y) * 0.5 + (p2.x - p1.x) * h;
  return true;
} // to get the other center, reverse p1 and p2

int main(){
  point P1(0,0), P2(1,1), P3(1,1), P4(2, 2);
  point c;
  printf("%d\n", intersect(P1, P2, P3, P4, c) ? 1 : 0);
  printf("%lf %lf\n", c.x, c.y);
  return 0;
}