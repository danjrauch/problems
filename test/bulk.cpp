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

long long numdatapoints; 

FILE *fp;

set<int> datapoints;

void writeDataPoint(){
  bool go = false;
  int p;
  while(!go){
    go = true;
    p = 0;
    for(int i = 0; i<17; ++i){
      if(rand() % 2 == 1){
        p = p | (1<<i); 
      }
    }
    if(datapoints.count(p) > 0) go = false;
  }
  //printf("%d\n", p); 
  fprintf(fp, "%d\n", p); 
  datapoints.insert(p);
}

int main(){
  fp = fopen("bulk", "w+");
  srand(time(0)); 
  printf("How many data points? : "); 
  scanf("%lld", &numdatapoints); 
  for(long long d = 0; d<numdatapoints; ++d){
    writeDataPoint(); 
  }
  fprintf(fp, "%d\n", -1); 
  fclose(fp); 
  return 0; 
}

