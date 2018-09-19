#include <bits/stdc++.h>
using namespace std; 

int partition(vector<int> v, int p, int r){
  int x = v[r]; 
  int i = p-1; 
  for(int j = p; j<r; ++j){
    if(v[j] <= x){
      i++; 
      swap(v[i], v[j]); 
    }
  }
  swap(v[i+1], v[r]); 
  return i+1; 
}

int select(vector<int> v, int p, int r, int i){
  if(p == r) return v[p]; 
  int q = partition(v, p, r); 
  int k = q-p+1; 
  if(i == k) return v[q]; 
  else if(i<k) return select(v, p, q-1, i); 
  else return select(v, q+1, r, i-k); 
}

int main(){
  srand(time(0)); 
  vector<int> v(20); 
  for(int i = 0; i<20; ++i){
    v[i] = rand() % 40 + 1; 
    printf("%d ", v[i]); 
  }
  int k = select(v, 0, v.size()-1, 5); 
  printf("\n%d\n", k); 
  return 0; 
}