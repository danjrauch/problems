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

int n;
vector<set<int> > v;

int main(){
  scanf("%d", &n);
  v.resize(n);
  int a;
  for(int i = 0; i<n; ++i){
    for(int k = 0; k<25; ++k){
      scanf("%d", &a);
      v[i].insert(a);
    }
  }
  for(int i = 0; i<n; ++i){
    set<int>::iterator it;
    for (it = v[i].begin(); it != v[i].end(); ++it) {
      for(int k = i+1; k<n; ++k){
        if(v[k].count(*it)){
          printf("%d %d\n", i+1, k+1);
          return 0;
        }
      }
    }
  }
  printf("no ties\n");
  return 0;
}