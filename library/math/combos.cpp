#include <bits/stdc++.h>
using namespace std;
int n, c, j, t; vector<int> v; string s;
vector<int> subset;

void subsetVector(int k, vector<int> v){
  if(k==v.size()){
    for(int i = 0; i<subset.size(); ++i){
      printf("%d ", subset[i]);
    }
    printf("\n");
  }
  else{
    subsetVector(k+1, v);
    subset.push_back(v[k]);
    subsetVector(k+1, v);
    subset.pop_back();
  }
}

void subsetSeq(int k){
  if(k==n){
    for(int i = 0; i<subset.size(); ++i){
      printf("%d ", subset[i]);
    }
    printf("\n");
  }
  else{
    subsetSeq(k+1);
    subset.push_back(k);
    subsetSeq(k+1);
    subset.pop_back();
  }
}

int main(){
  n = 5;
  //subsetSeq(0);
  vector<int> vv = {1,2,3};
  subsetVector(0, vv);
  return 0;
}
