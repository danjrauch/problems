/*Cluster Number*/

#include <bits/stdc++.h>
using namespace std;

int n, m, a, b, j; vector<vector<int> > vec;

void DFS(int u, int r, int tcol){
  bool visited[u][r];
  for(int i = 0; i<u; ++i){
    for(int k = 0; k<r; ++k) {
      visited[i][k] = false;
    }
  }
  int clusters = 0;
  for(int i = 0; i<u; ++i){
    for(int k = 0; k<r; ++k){
      if(vec[i][k] != tcol) continue;
      if(visited[i][k]) continue;
      stack<pair<int, int> > st; 
      st.push(make_pair(i, k));
      clusters++;
      while(!st.empty()){
        pair<int, int> p = st.top();
        visited[p.first][p.second] = true;
        vec[p.first][p.second] = clusters;
        st.pop();
        if(p.first+1 < vec.size() && !visited[p.first+1][p.second] && vec[p.first+1][p.second] == tcol) st.push(make_pair(p.first+1, p.second));
        if(p.first-1 >= 0 && !visited[p.first-1][p.second] && vec[p.first-1][p.second] == tcol) st.push(make_pair(p.first-1, p.second));
        if(p.second+1 < vec[p.first].size() && !visited[p.first][p.second+1]  && vec[p.first][p.second+1] == tcol) st.push(make_pair(p.first, p.second+1));
        if(p.second-1 >=0 && !visited[p.first][p.second-1] && vec[p.first][p.second-1] == tcol) st.push(make_pair(p.first, p.second-1));
        if(p.first+1 < vec.size() && p.second+1 < vec[p.first+1].size() && !visited[p.first+1][p.second+1] && vec[p.first+1][p.second+1] == tcol) st.push(make_pair(p.first+1, p.second+1)); // diags start
        if(p.first-1 >= 0 && p.second+1 < vec[p.first-1].size() && !visited[p.first-1][p.second+1] && vec[p.first-1][p.second+1] == tcol) st.push(make_pair(p.first-1, p.second+1));
        if(p.first+1 < vec.size() && p.second-1 >= 0 && !visited[p.first+1][p.second-1]  && vec[p.first+1][p.second-1] == tcol) st.push(make_pair(p.first+1, p.second-1));
        if(p.first-1 >= 0 && p.second-1 >= 0 && !visited[p.first-1][p.second-1] && vec[p.first-1][p.second-1] == tcol) st.push(make_pair(p.first-1, p.second-1));
      }
    }
  }
}

int main(){
  double d = 0;
  srand(time(0));
  int rows, cols;
  scanf("%d %d", &rows, &cols);
  vec.resize(rows);
  for(int i = 0; i<rows; ++i){
    vec[i].resize(cols);
    for(int k = 0; k<cols; ++k){
      d = (double) rand() / RAND_MAX;
      if(d<.4) vec[i][k] = 1;
      else vec[i][k] = 0;
    }
  } 
  for(int i = 0; i<rows; ++i){
    vec[i].resize(cols);
    for(int k = 0; k<cols; ++k) printf("%d ", vec[i][k]);
    printf("\n");
  } printf("\n");

  DFS(rows, cols, 1);

  for(int i = 0; i<rows; ++i){
    vec[i].resize(cols);
    for(int k = 0; k<cols; ++k) printf("%d ", vec[i][k]);
    printf("\n");
  } 
  return 0;
}