#include <bits/stdc++.h>
using namespace std;

int n, a, b; 
vector<int> v; 

void quicksort(int p, int r){
  if(p<r){
    int q = partit(p, r); 
    quicksort(p, q-1); 
    quicksort(q+1, r);
  }
}

int partit(int p, int r){
  int x = v[r];
  int i = p - 1;
  for(int j = p; j<r; ++j){
    if(v[j]<=x){
      i++;
      swap(v[i],v[j]);
    }
  } 
  swap(v[i+1],v[r]);
  return i+1; 
}

int main(){
  srand(time(0)); 
  for(int i = 0; i<30; ++i){
    v.push_back(rand() % 9 + 1); 
  }
  quicksort(0,v.size()); 
  for(int i = 0; i<v.size(); ++i) printf("%d ", v[i]);
  printf("\n"); 
}