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
typedef long ll; 

int n, r, c;
vector<vector<long> > grid; 

vector<vector<long> > dists; // used for all graphs simultaneously for dijkstras
vector<vector<pii> > preds; // used for all graphs simultaneously for dijkstras

void initss(int sr, int sc){
    dists.resize(r); 
    preds.resize(r); 
    for(int i = 0; i<r; ++i){
        dists[i].resize(c); 
        preds[i].resize(c); 
        for(int k = 0; k<c; ++k){
            dists[i][k] = INF; 
            preds[i][k] = make_pair(-1, -1); 
        }
    }
    dists[sr][sc] = grid[sr][sc]; 
}

//pretty fast for grids
long dijkstras(pii src, pii dest){
    initss(src.first, src.second); 
    int dr[] = {1, -1, 0, 0}; 
    int dc[] = {0, 0, 1, -1}; 
    priority_queue<pair<long, pii>, vector<pair<long, pii> >, greater<pair<long, pii> > > pq;
    pq.push(make_pair(grid[src.first][src.second], make_pair(src.first, src.second))); 
    while(!pq.empty()){
        pair<long, pii> p = pq.top(); 
        pq.pop(); 
        if(p.second.first == dest.first && p.second.second == dest.second) break; 
        for(int i = 0; i<4; ++i){
            if(p.second.first+dr[i] >= 0 && p.second.first+dr[i] < r && p.second.second+dc[i] >= 0 && p.second.second+dc[i] < c){
                if(dists[p.second.first][p.second.second] + grid[p.second.first+dr[i]][p.second.second+dc[i]] < dists[p.second.first+dr[i]][p.second.second+dc[i]]){
                    dists[p.second.first+dr[i]][p.second.second+dc[i]] = dists[p.second.first][p.second.second] + grid[p.second.first+dr[i]][p.second.second+dc[i]]; 
                    preds[p.second.first+dr[i]][p.second.second+dc[i]] = make_pair(p.second.first, p.second.second); 
                    pq.push(make_pair(dists[p.second.first+dr[i]][p.second.second+dc[i]], make_pair(p.second.first+dr[i], p.second.second+dc[i]))); 
                }
            }
        }
    }
    return dists[dest.first][dest.second]; 
}

int main(){
    int tests; 
    scanf("%d", &tests); 
    for(int te = 0; te<tests; ++te){
        scanf("%d", &r); 
        scanf("%d", &c); 
        grid.clear(); 
        grid.resize(r); 
        for(int i = 0; i<r; ++i){
            grid[i].resize(c); 
            for(int k = 0; k<c; ++k){
                scanf("%ld", &grid[i][k]); 
            }
        }
        long res = dijkstras(make_pair(0, 0), make_pair(r-1, c-1)); 
        printf("%ld\n", res); 
    }
    return 0; 
}