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

vector<int> v;
set<int> s;

int main(){
  int a; 
  scanf("%d", &a);
  while(a != -1){
    v.push_back(a);
    s.insert(a);
    scanf("%d", &a);
  }
  for(int i = 0; i<v.size(); ++i){
    int r=0;
    for(int k = 0; k<=17; ++k){
      int t = v[i] ^ (1<<k);
      if(t > v[i] && s.count(t)) r++;
      for(int j = k+1; j<=17; ++j){
        int tt = t;
        tt = tt ^ (1<<j);
        if(tt > v[i] && s.count(tt)) r++;
      }
    }
    printf("%d:%d\n", v[i], r);
  }
  return 0;
}

