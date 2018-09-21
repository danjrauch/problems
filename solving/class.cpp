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

string s, t;

int f(int b, int e){
  int bb=b, ee=e;
  while(e-b>=0){
    if(s.at(b) != t.at(e)) return 0;
    b++; 
    e--;
  }
  int res = 1; 
  bb--; ee++;
  while(bb >= 0 && ee < s.size()){
    if(s.at(bb) == t.at(ee)) res++;
    b--; ee++;
  }
  return res;
}

int main(){
  cin >> s; 
  cin >> t;
  int b=-1, e, res=0; 
  for(int i = 0; i<s.size(); ++i){
    if(s.at(i) != t.at(i)){
      if(b == -1) b = i; 
      e = i;
    }
  }
  printf("%d\n", f(b, e));
  return 0; 
}

