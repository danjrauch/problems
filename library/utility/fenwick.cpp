#include<bits/stdc++.h>
using namespace std;

vector<int> ft; 

vector<int> input; 

void adjust(int v, int i){
  while(i<ft.size()){
    ft[i] += v; 
    i = i + (i & -i); //getNext(i)
  }
}

void makeFt(vector<int> input){
  ft.resize(input.size()+1); 
  for(int i = 1; i<=input.size(); ++i){
    adjust(input[i-1], i);
  }
}

int rsq(int i){ //range query from a to i
  i++; 
  int sum = 0; 
  while(i > 0){
    sum += ft[i]; 
    i = i - (i & -i); //getParent(i)
  }
  return sum; 
}

int rsq(int a, int b){
  return rsq(b)-rsq(a-1); 
}

void printFT(){
  for(int i = 0; i<ft.size(); ++i){
    printf("%d ", ft[i]); 
  }
  printf("\n"); 
}

int main(){
  int n, m; 
  scanf("%d %d", &n, &m); 
  input.resize(n); 
  for(int i = 0; i<n; ++i){
    scanf("%d", &input[i]); 
  }
  makeFt(input);
  printFT(); 
  printf("%d\n", rsq(0, 3)); 
  return 0; 
}