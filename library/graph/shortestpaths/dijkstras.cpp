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

int n, v, e, s, t;
vector<vector<pii > > graph; 
vector<pair<int, pii > > edges; 

vi dists; // used for all graphs simultaneously for dijkstras
vi preds; // used for all graphs simultaneously for dijkstras
 
void graphIntake(){
    scanf("%d %d %d %d", &v, &e, &s, &t);  
    graph.clear(); 
    edges.clear();
    graph.resize(v); 
    int a, b, we; 
    for(int i = 0; i<e; ++i){
        scanf("%d %d %d", &a, &b, &we); 
        graph[a].push_back(make_pair(b, we));
        graph[b].push_back(make_pair(a, we));               //undirected, just take this out to make it directed
        edges.push_back(make_pair(we, make_pair(a, b)));  
    }
}

void initss(int numofvertices, int s){
    dists.resize(numofvertices); 
    preds.resize(numofvertices); 
    for(int i = 0; i<numofvertices; ++i){
        dists[i] = INF; 
        preds[i] = -1; 
    }
    dists[s] = 0; 
}

int dijkstras(vector<vector<pii> > g, int s){
    initss(g.size(), s); 
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    pq.push(make_pair(0, s)); 
    while(!pq.empty()){
        pii p = pq.top(); 
        pq.pop(); 
        if(p.second == t) return dists[t]; 
        for(int i = 0; i<g[p.second].size(); ++i){
            pii u = g[p.second][i]; 
            if(dists[p.second] + u.second < dists[u.first]){
                dists[u.first] = dists[p.second] + u.second; 
                preds[u.first] = p.second; 
                pq.push(make_pair(dists[u.first], u.first)); 
            }
        }
    }
    return -1; 
}

int main(){
    int tests; 
    scanf("%d", &tests); 
    for(int te = 0; te<tests; ++te){
        graphIntake(); 
        int res = dijkstras(graph, s); 
        if(res == -1){
            printf("Case #%d: unreachable\n", te+1); 
        }
        else{
            printf("Case #%d: %d\n", te+1, res); 
        }
    }
}