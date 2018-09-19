/* https://codeforces.com/problemset/problem/1042/B
 * B. Vitamins
 * bitmasking dp
 * */

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

#define INF 99999999

int n, res=INF;
vector<pair<int, string> > js;

bool inside(char c, string s){
  for(int i = 0; i<s.size(); ++i) if(s.at(i) == c) return true;
  return false;
}

void findJ(pair<int, int> p, int pos[], string vs){
  for(int i = p.second; i<js[p.first].second.size(); ++i){
    if(!inside(js[p.first].second.at(i), vs)){
      vs += js[p.first].second.at(i);
      pos[vs.size()-1] = p.first;
    }
  }
  if(vs.size() == 3){
    int n = js[pos[0]].first; 
    // might have duplicate values
    if(pos[1] != pos[0])  
      n += js[pos[1]].first;
    if(pos[2] != pos[0] && pos[2] != pos[1])
      n += js[pos[2]].first; 
    //for(int i = 0; i<3; ++i) printf("%d ", pos[i]);
    //printf("\n"); 
    if(n < res)
      res = n; 
    return;
  }
  for(int i = p.first+1; i<js.size(); ++i){
    for(int k = 0; k<js[i].second.size(); ++k){
      if(!inside(js[i].second.at(k), vs)){
        findJ(make_pair(i, k), pos, vs); 
      }
    }
  }
}

int main(){
  scanf("%d", &n);
  js.resize(n);
  for(int i = 0; i<n; ++i){
    scanf("%d", &js[i].first); 
    cin >> js[i].second; 
  }
  int v[3] = {-1, -1, -1}; 
  for(int i = 0; i<js.size(); ++i){
    for(int k = 0; k<js[i].second.size(); ++k){
      findJ(make_pair(i, k), v, "");
    }
  }
  printf("%d\n", res==INF?-1:res);
  return 0; 
}
