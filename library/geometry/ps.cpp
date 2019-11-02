#include<bits/stdc++.h>
using namespace std;
#define INF 2147483647

int n;

#define EPS 1e-12
#define pi acos(-1.0)
#define CLOCKWISE 0
#define COUNTERCLOCKWISE 1

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

/* points should wrap counter clockwise, with last point being
 * the same as the first point */
vector<point> input_polygon(int n){
  vector<point> P(n+1);
  for(int i = 0; i<n; ++i){
    scanf("%lf %lf", &P[i].x, &P[i].y);
  }
  P[n] = P[0];
  return P;
}

double perimeter(const vector<point> &P){
  double result = 0.0;
  for(int i = 0; i<(int) P.size()-1; ++i){
    result += dist(P[i], P[i+1]);
  }
  return result;
}

/* returns the area, which is half the determinant */
double area(const vector<point> &P){
  double result = 0.0, x1, y1, x2, y2;
  for(int i = 0; i< (int)P.size()-1; ++i){
    x1 = P[i].x; x2 = P[i+1].x;
    y1 = P[i].y; y2 = P[i+1].y;
    result += (x1 * y2 - x2 * y1);
  }
  return fabs(result) / 2.0;
}

/*
 *               Vectors
 */

struct vec{
  double x, y;
  vec(double _x, double _y) : x(_x), y(_y) {}
};

vec to_vec(point a, point b){
  return vec(b.x - a.x, b.y - a.y);
}

/* s is nonnegative in [<1, 1, >1] */
vec scale(vec v, double s){
  return vec(v.x * s, v.y * s);
}

/* translate p by v's values */
point translate(point p, vec v){
  return point(p.x + v.x, p.y + v.y);
}

double dot(vec a, vec b){
  return (a.x * b.x + a.y * b.y);
}

double norm_sq(vec v){
  return v.x * v.x + v.y * v.y;
}

/* return the distance form p to the line defined by
 * two points a and b (a and b must be different)
 * the closest point is stored in the 4th parameter (byref) */
double dist_to_line(point p, point a, point b, point &c){
  // formula: c = a + u & ab
  vec ap = to_vec(a, p), ab = to_vec(a, b);
  double u = dot(ap, ab) / norm_sq(ab);
  c = translate(a, scale(ab, u));
  return dist(p, c);
}

/* returns the distance from p to the line segment ab defined by
 * two points a and b (still ok if a == b)
 * the closest point is stored in the 4th parameter (byref) */
double dist_to_line_segment(point p, point a, point b, point &c){
  vec ap = to_vec(a, p), ab = to_vec(a, b);
  double u = dot(ap, ab) / norm_sq(ab);
  if (u < 0.0){
    c = point(a.x, a.y);
    return dist(p, a);
  }
  if (u > 1.0){
    c = point(b.x, b.y);
    return dist(p, b);
  }
  return dist_to_line(p, a, b, c);
}

/* since oa dot ob = abs(oa) * abs(ob) * cos(theta),
 * we have theta = arccos(oa dot ob/(abs(oa) * abs(ob))) */
double angle(point a, point o, point b){
  vec oa = to_vec(o, a), ob = to_vec(o, b);
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}

double cross(vec a, vec b){
  return a.x * b.y - a.y * b.x;
}

/* note: to accept collinear points, we have to change the '>0'
 * returns true if point r is on the left side of line pq */
bool ccw(point p, point q, point r){
  return cross(to_vec(p, q), to_vec(p, r)) > 0;
}

bool collinear(point p, point q, point r){
  return fabs(cross(to_vec(p, q), to_vec(p, r))) < EPS;
}

/* returns true if the polygon is convex
 * a polygon is convex if all angles are left turns
 * this implementation accepts collinear points as convex */
bool is_convex(const vector<point> &P){
  int sz = (int)P.size();
  if (sz <= 3) return false;
  bool isLeft = ccw(P[0], P[1], P[2]);
  bool collin = collinear(P[0], P[1], P[2]);
  if(collin) isLeft = true;
  for(int i = 1; i<sz-1; ++i)
    if(collinear(P[i], P[i+1], P[(i+2) == sz ? 1 : i+2])) continue;
    else if(ccw(P[i], P[i+1], P[(i+2) == sz ? 1 : i+2]) != isLeft) return false;
  return true;
}

/* returns true if the point is inside of any polygon
 * sums the angles between the point and all other points
 * if sum == 360, the point is in the polygon
 * does not accept points on the edge of the polygon */
bool in_polygon(point pt, const vector<point> &P){
  if((int)P.size() == 0) return false;
  double sum = 0;
  for(int i = 0; i < (int) P.size()-1; ++i){
    if(ccw(pt, P[i], P[i+1]))
      sum += angle(P[i], pt, P[i+1]);
    else sum -= angle(P[i], pt, P[i+1]);
  }
  return fabs(fabs(sum) - 2*pi) < EPS;
}

/* line segment p-q intersect with line A-B */
point line_intersect_seg(point p, point q, point A, point B){
  double a = B.y - A.y;
  double b = A.x - B.x;
  double c = B.x * A.y - A.x * B.y;
  double u = fabs(a * p.x + b * p.y + c);
  double v = fabs(a * q.x + b * q.y + c);
  return point((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v));
}

/* cuts polygon Q along the line formed by point a -> point b
 * (note: the last point must be the same as the first point) */
vector<point> cut_polygon(point a, point b, const vector<point> &Q){
  vector<point> P;
  for(int i = 0; i<(int) Q.size(); ++i){
    double left1 = cross(to_vec(a, b), to_vec(a, Q[i])), left2 = 0;
    if(i != (int) Q.size()-1) left2 = cross(to_vec(a, b), to_vec(a, Q[i+1]));
    if(left1 > -EPS) P.push_back(Q[i]);
    if(left1 * left2 < -EPS)
      P.push_back(line_intersect_seg(Q[i], Q[i+1], a, b));
  }
  if(!P.empty() && !(P.back() == P.front()))
    P.push_back(P.front());
  return P;
}

/* angle sorting function for Graham's Scan */
point pivot(0, 0);
bool angle_cmp(point a, point b){
  if(collinear(pivot, a, b))
    return dist(pivot, a) < dist(pivot, b);
  double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
  double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
  return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
}

/* Graham's Scan
 * returns a polygon of the convex hull in counter-clockwise order. */
vector<point> CH_slower(vector<point> P){
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
  sort(++P.begin(), P.end(), angle_cmp);

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

/* 2D cross product of OA and OB vectors, i.e. z-component of their 3D cross product.
 * returns a positive value, if OAB makes a counter-clockwise turn,
 * negative for clockwise turn, and zero if the points are collinear. */
double cross(const point &O, const point &A, const point &B){
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

/* Andrew's Monotone Chain Algorithm
 * returns a polygon of the convex hull in counter-clockwise order.
 * note: the last point in the returned list is the same as the first one. */
vector<point> CH_faster(vector<point> P){
	int n = P.size(), k = 0;
	if (n == 1) return P;
	vector<point> H(2*n);

	// Sort points lexicographically
	sort(P.begin(), P.end());

	// Build lower hull
	for (int i = 0; i < n; ++i) {
		while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	// Build upper hull
	for (int i = n-2, t = k+1; i >= 0; i--) {
		while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

  H.resize(k-1);
	return H;
}

/* routine for getting the center of mass of the polygon */
point center;
void get_center_point(const vector<point> &P){
  double X = 0, Y = 0;
  for(int i = 0; i<(int)P.size(); ++i){
    X += P[i].x;
    Y += P[i].y;
  }
  center.x = X/P.size();
  center.y = Y/P.size();
}

/* comparison routine for the later sorting of the polygon */
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
  if (det < 0)
    return true;
  if (det > 0)
    return false;

  // points a and b are on the same line from the center
  // check which point is closer to the center
  double d1 = (a.x - center.x) * (a.x - center.x) + (a.y - center.y) * (a.y - center.y);
  double d2 = (b.x - center.x) * (b.x - center.x) + (b.y - center.y) * (b.y - center.y);
  return d1 > d2;
}

/* type = 0 for clockwise sorting
 * type = 1 for counter-clockwise sorting */
vector<point> sort_polygon(vector<point> poly, int type){
  vector<point> ret(poly);
  ret.erase(ret.begin()+ret.size()-1);
  get_center_point(ret);
  if(type == COUNTERCLOCKWISE) sort(ret.rbegin(), ret.rend(), L);
  else                         sort(ret.begin(), ret.end(), L);
  ret.push_back(ret[0]);
  return ret;
}

int main(){
  scanf("%d", &n);
  vector<point> P = input_polygon(n);
  vector<point> graham = CH_slower(P);
  vector<point> monotone = CH_faster(P);
  for(int i = 0; i<graham.size(); ++i){
    printf("%lf %lf\n", graham[i].x, graham[i].y);
  }
  printf("\n");
  for(int i = 0; i<monotone.size(); ++i){
    printf("%lf %lf\n", monotone[i].x, monotone[i].y);
  }

  P = input_polygon(n);
  vector<point> Q = input_polygon(n);
  vector<point> PQ;
  for(int i = 0; i<P.size()-1; ++i) PQ.push_back(P[i]);
  for(int i = 0; i<Q.size()-1; ++i) PQ.push_back(Q[i]);
  PQ.push_back(PQ[0]);
  P = sort_polygon(P, COUNTERCLOCKWISE);
  Q = sort_polygon(Q, COUNTERCLOCKWISE);
  printf("unsorted PQ\n");
  for(int i = 0; i<PQ.size(); ++i){
    printf("(%lf %lf)\n", PQ[i].x, PQ[i].y);
  }
  PQ = sort_polygon(PQ, COUNTERCLOCKWISE);
  printf("sorted PQ\n");
  for(int i = 0; i<PQ.size(); ++i){
    printf("(%lf %lf)\n", PQ[i].x, PQ[i].y);
  }
  PQ = CH_faster(PQ);
  printf("hulled PQ\n");
  for(int i = 0; i<PQ.size(); ++i){
    printf("(%lf %lf)\n", PQ[i].x, PQ[i].y);
  }
  printf("P: %lf\n", area(P));
  printf("Q: %lf\n", area(Q));
  printf("PQ: %lf\n", area(PQ));
  return 0;
}