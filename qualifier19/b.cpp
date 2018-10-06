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

int p, q, s;

int main(){
  scanf("%d %d %d", &p, &q, &s);
  for(int i = 1; i<=s; ++i){
    if(i % p == 0 && i % q == 0){
      printf("yes\n");
      return 0;
    }
  }
  printf("no\n");
  return 0;
}