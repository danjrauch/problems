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

//points should wrap counter clockwise, with last point being
//the same as the first point
vector<point> inputPolygon(int n){
    vector<point> P(n); 
    for(int i = 0; i<n; ++i){
        scanf("%lf %lf", &P[i].x, &P[i].y); 
    }
    return P; 
}

int main(){
    scanf("%d", &n); 
    vector<point> poly = inputPolygon(n); 
    getCenterPoint(poly); 
    sort(poly.begin(), poly.end(), L); 
    for(int i = 0; i<poly.size(); ++i){
        printf("(%lf %lf)\n", poly[i].x, poly[i].y); 
    }
    return 0; 
}