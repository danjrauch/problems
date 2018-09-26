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

#define INF 999999999

int T, res;
vector<vector<char> > grid;
vector<vector<char> > w;
map<int, bool> m;

int dr[] = {0,1,-1,0};
int dc[] = {1,0,0,-1};

bool isValid(int i, int k){ return i>=0 && i<3 && k>=0 && k<3; }

vector<vector<char> > flip(vector<vector<char> > work, int i, int k){
  if(work[i][k] == '*') work[i][k] = '.';
  else work[i][k] = '*';
  for(int j = 0; j<4; ++j){
    if(isValid(i+dr[j], k+dc[j])){
      if(work[i+dr[j]][k+dc[j]] == '*') work[i+dr[j]][k+dc[j]] = '.';
      else work[i+dr[j]][k+dc[j]] = '*';
    }
  }
  return work;
}

void solve(vector<vector<char> > work, int score){
  bool done = true;
  int mask = 0;
  for(int i = 0; i<3; ++i){
    for(int k = 0; k<3; ++k){
      if(work[i][k] != grid[i][k]) done = false;
      if(work[i][k] == '*') mask = mask | (1<<(i+k));
      printf("%c", work[i][k]);
    }
    printf("\n");
  }
  printf("\n");
  if(done){
    if(score < res){
      res = score;
      return;
    }
  }
  if(score > res || m[mask]) return;
  m[mask] = 1;
  for(int i = 0; i<3; ++i){
    for(int k = 0; k<3; ++k){
      solve(flip(work, i, k), score+1);
    }
  }
}

int main(){
  scanf("%d", &T);
  grid.resize(3);
  w.resize(3);
  for(int i = 0; i<3; ++i){
    grid[i].resize(3);
    w[i].resize(3);
  }
  for(int t = 0; t<T; ++t){
    res = INF; 
    string s;
    for(int i = 0; i<3; ++i){
      cin >> s;
      for(int k = 0; k<3; ++k){
        grid[i][k] = s.at(k);
        w[i][k] = '.';
      }
    }
    solve(w, 0);
    printf("%d\n", res);
  }
  return 0; 
}
