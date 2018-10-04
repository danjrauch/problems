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

int T, n;
vector<int> v;

void add1(){
  for(int i = n-1; i>=0; --i){
    if(v[i]) v[i] = 0;
    else{
      v[i] = 1;
      return;
    }
  }
}

void print(){
  for(int i = 0; i<n; ++i){
    printf("%d", v[i]);
  }
  printf("\n");
}

int main(){
  scanf("%d", &T);
  for(int i = 0; i<T; ++i){
    scanf("%d", &n);
    v.clear();
    v.resize(n);
    add1();
    print();
  }
  return 0;
}
