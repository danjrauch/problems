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

int L, W, P, O, I, sp;
vector<vector<int> > vs;
vector<vector<int> > v;
vector<int> intervals;
string s;

void move(){
  for(int i = 0; i<L; ++i){
    if(i % 2 == 0){
      for(int k = W-1; k>=0; --k){
        if(v[i][k] != 0){
          if(v[i][k+v[i][k]] < W) v[i][k+v[i][k]] = v[i][k];
          for(int j = k+1; j<k+v[i][k]; ++j) v[i][j] = -2;
          v[i][k] = 0;
        }
      }
      for(int k = 0; k<W; ++k){
        if(v[i][k] != 0){
          if(k-intervals[i] >= 0 && v[i][k-intervals[i]] == 0) v[i][k-intervals[i]] = v[i][k];
        }
      }
    }
    else{
      for(int k = 0; k<W; ++k){
        if(v[i][k] != 0){
          if(v[i][k-v[i][k]] >= 0) v[i][k-v[i][k]] = v[i][k];
          for(int j = k-1; j>k-v[i][k]; ++j) v[i][j] = -2;
          v[i][k] = 0;
        }
      }
      for(int k = 0; k<W; ++k){
        if(v[i][k] != 0){
          if(k+intervals[i] >= 0 && v[i][k+intervals[i]] == 0) v[i][k+intervals[i]] = v[i][k];
        }
      }
    }
  }
}

void destroyCollisions(){
  for(int i = 0; i<L; ++i){
    for(int k = 0; k<W; ++k){
      if(v[i][k] == -2) v[i][k] = 0;
    }
  }
}

int main(){
  scanf("%d %d", &L, &W);
  vs.resize(L);
  intervals.resize(L);
  for(int i = 0; i<L; ++i) vs[i].resize(W);
  for(int i = 0; i<L; ++i){
    scanf("%d %d %d", &O, &I, &sp);
    for(int k = O; k<W; k+=I){
      vs[i][k] = sp;
    }
    intervals[i] = I;
  }
  scanf("%d", &P);
  cin >> s;
  v.resize(L);
  // for(int i = 0; i<L; ++i) v[i].resize(W);
  for(int i = 0; i<L; ++i){
    v[i] = vs[vs.size()-1-i];
  }
  pair<int, int> pos = make_pair(-1, P);
  for(int i = 0; i<s.size(); ++i){
    move();
    if(s.at(i) == 'L') pos.second--;
    if(s.at(i) == 'R') pos.second++;
    if(s.at(i) == 'U') pos.first++;
    if(s.at(i) == 'D') pos.first--;
    if(pos.first >= 0 && pos.first != L && v[pos.first][pos.second] != 0){
      printf("squish\n");
      return 0;
    }
    destroyCollisions();
  }
  // printf("%d %d\n", pos.first, pos.second);
  if(pos.first < L) printf("squish\n");
  else printf("safe\n");
  return 0;
}