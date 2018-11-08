/*Flood Fill*/

#include <bits/stdc++.h>
using namespace std;

int n, m, a, b, j; vector<vector<int> > vec;

void floodFill(int u, int r, int tcol, int rcol){
  pair<int, int> n = make_pair(u, r);
  if(tcol == rcol) return;
  if(vec[u][r] != tcol) return;
  queue<pair<int,int> > q;
  q.push(n);
  while(!q.empty()){
    pair<int, int> w = q.front(); 
    pair<int, int> e = q.front();
    q.pop();
    while(w.second >= 0 && vec[w.first][w.second] == tcol){
      vec[w.first][w.second] = rcol; 
      if(w.first-1 >= 0 && vec[w.first-1][w.second] == tcol) q.push(make_pair(w.first-1, w.second));
      if(w.first+1 < vec.size() && vec[w.first+1][w.second] == tcol) q.push(make_pair(w.first+1, w.second));
      w.second--;
    } 
    while(e.second < vec[e.first].size() && vec[e.first][e.second] == tcol){
      if(e.first-1 >= 0 && vec[e.first-1][e.second] == tcol) q.push(make_pair(e.first-1, e.second));
      if(e.first+1 < vec.size() && vec[e.first+1][w.second] == tcol) q.push(make_pair(e.first+1, e.second));
      e.second++;
    } 
  }
}

int main(){
  srand(time(0));
  int rows; int cols;
  scanf("%d %d", &rows, &cols);
  vec.resize(rows);
  for(int i = 0; i<rows; ++i){
    vec[i].resize(cols);
    for(int k = 0; k<cols; ++k){
      j = rand()%2; 
      vec[i][k] = j;
      printf("%d ", vec[i][k]);
    }
    printf("\n");
  }
  printf("\n");
  for(int i = 0; i<rows; ++i){
    for(int k = 0; k<cols; ++k){
      floodFill(i,k,1,2);
    }
  }
  for(int i = 0; i<rows; ++i){
    for(int k = 0; k<cols; ++k) printf("%d ", vec[i][k]);
    printf("\n");
  }
  return 0;
}