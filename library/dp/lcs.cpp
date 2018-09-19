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
using namespace std;

vector<int> v(8); 
int n; 

void lcs(vector<int> v){
  vector<int> l(v.size(), 0); 
  l[0] = 1; 
  for(int i = 1; i<v.size(); ++i){
    int max = 0; 
    for(int k = 0; k<i; ++k){
      if(l[k] > max && v[i] > v[k]){
        max = l[k]; 
      }
    }
    l[i] = max + 1; 
    if(l[i] > n) n = l[i]; 
  }
  for(int i = 0; i<l.size(); ++i){
    printf("%d ", l[i]); 
  }
  printf("\n"); 
}


int main(){
  v[0] = 1; 
  v[1] = 6; 
  v[2] = 7; 
  v[3] = 8; 
  v[4] = 1;
  v[5] = 9; 
  v[6] = 3; 
  v[7] = 10; 
  lcs(v); 
  printf("%d\n", n); 
  for(int i = 0; i<v.size(); ++i){
    printf("%d ", v[i]); 
  }
  printf("\n"); 
  return 0;
}