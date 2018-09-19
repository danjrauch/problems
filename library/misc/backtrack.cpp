#include <bits/stdc++.h>
using namespace std;
int n, j, t; string s;
long c;
int nSqu;

void searchGrid(int x, int y, vector<vector<int> > v){
  v[x][y] = 1;
  nSqu++;
  if(x == v.size()-1 && y == v[0].size()-1 && nSqu==v.size()*v[0].size()){
    c++;
    return;
  }
  if(x == v[0].size() || v[x][y] == 1) {
    nSqu--;
    return;
  }
  if(y == v.size() || v[x][y] == 1) {
    nSqu--;
    return;
  }
  if(y == -1 || v[x][y] == 1) {
    nSqu--;
    return;
  }
  if(x == -1 || v[x][y] == 1) {
    nSqu--;
    return;
  }
  searchGrid(x+1, y, v);
  searchGrid(x, y+1, v);
  searchGrid(x-1, y, v);
  searchGrid(x, y-1, v);
}

int main(){
  vector<vector<int> > v(5);
  for(int i = 0; i<5; ++i){
    for(int k = 1; k<6; ++k){
      v[i].push_back(k);
    }
  }
  searchGrid(0, 0, v);
  printf("%ld\n", c);
  return 0;
}
