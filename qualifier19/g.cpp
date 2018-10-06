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

int n;
string s;
vector<int> v;
vector<bool> vis;

int findLefts(int j){
  int m = j+1, res = 0;
  while(s.at(m) == 'L'){
    res++;
    m++;
  }
  return res;
}

int findLeftTurnIndex(int j, int lefts){
  int m = j+1, c = 0;
  while(c < lefts){
    c += vis[m] == false ? 1 : 0;
    m++;
  }
  return m-1;
}

int main(){
  scanf("%d", &n);
  cin >> s;
  for(int i = 0; i<n; ++i){
    v.push_back(i+1);
    vis.push_back(false);
  }
  int t = 0, j = 0, k = 0; 
  while(t != n){
    if(s.at(j) == 'R'){
      printf("%d\n", v[k]);
      t++;
      int lefts = findLefts(j);
      int l = findLeftTurnIndex(k, lefts);
      for(int w = 0; w<lefts-1; ++w){
        printf("%d\n", v[l-w]);
        t++;
      }
      k=l-lefts;
      j+=lefts;
    }
    else{
      j++;
      k++;
    }
  }
  return 0;
}