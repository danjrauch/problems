#include <bits/stdc++.h>
using namespace std; 

map<int, char> m; 

int v, e, a, b, we; 

#define INF 99999  //PROBS NEED TO INCREASE

vector<vector<int> > graph; 
vector<vector<int> > preds; 

void graphIntake(){
  scanf("%d %d", &v, &e); 
  graph.resize(v); 
  preds.resize(v); 
  for(int i = 0; i<v; ++i){
    graph[i].resize(v);
    preds[i].resize(v); 
    fill(graph[i].begin(), graph[i].begin()+v, INF);  
    fill(preds[i].begin(), preds[i].begin()+v, -1); 
  } 
  for(int i = 0; i<v; ++i) graph[i][i] = 0; 
  for(int i = 0; i<e; ++i){
    scanf("%d %d %d", &a, &b, &we); 
    graph[a][b] = we; 
    preds[a][b] = a; 
  }
}

void floydwarshall(){
  for(int k = 0; k<v; ++k){
    for(int i = 0; i<v; ++i){
      for(int j = 0; j<v; ++j){
        if(graph[i][k] + graph[k][j] < graph[i][j]){
          graph[i][j] = graph[i][k]+graph[k][j]; 
          preds[i][j] = preds[k][j]; 
        }
      }
    }
  }
}

void printpath(int s, int d){
  if(preds[s][d] == -1) printf("no path\n"); 
  int i = s; 
  int k = d; 
  vector<int> path; 
  path.push_back(d); 
  while(preds[i][k] != -1){
    path.push_back(preds[i][k]); 
    k = preds[i][k]; 
  }
  for(int i = path.size()-1; i>-1; --i){
    printf("%d ", path[i]); 
  }
  printf("\n"); 
}

int main(){
  graphIntake(); 
  floydwarshall(); 
  //printpath(0, 3); 
  return 0; 
}