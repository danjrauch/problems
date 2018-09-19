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

int dr[] = {1, 0, -1, 0};
int dc[] = {0, 1, 0, -1}; 

int R, C; 

vector<vector<char> > grid; 

int numConnectedComponents; 

bool floodfill(int r, int c, char c1, char c2){
  if(r < 0 || r >=R || c < 0 || c >= C) return false; 
  if(grid[r][c] < 97 || grid[r][c] > 122) return false; 
  if(grid[r][c] != c1) return false; 
  grid[r][c] = c2; 
  for(int d = 0; d<4; d++){
    floodfill(r+dr[d], c+dc[d], c1, c2); 
  }
  return true; 
}

int main(){
  int tests; 
  scanf("%d", &tests); 
  tests = 1; 
  for(int i = 0; i<tests; ++i){
    numConnectedComponents = 0; 
    scanf("%d %d", &R, &C); 
    grid.resize(R); 
    for(int j = 0; j<R; ++j){
      grid[j].resize(C); 
      for(int k = 0; k<C; ++k){
        scanf(" %c ", &grid[j][k]); 
      }
    }
    for(int j = 0; j<R; ++j){
      for(int k = 0; k<C; ++k){
        if(floodfill(j, k, grid[j][k], (char)(65+numConnectedComponents))) numConnectedComponents++; 
      }
    }
    printf("%d\n", numConnectedComponents); 
  }
  return 0; 
}