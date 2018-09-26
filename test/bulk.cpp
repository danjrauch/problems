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
  int p = rand() % 400;
  int s = rand() % 400;
  fprintf(fp, "%d %d\n", p, s); 
}

int main(){
  fp = fopen("bulk", "w+");
  srand(time(0)); 
  printf("How many data points? : "); 
  scanf("%lld", &numdatapoints);
  fprintf(fp, "%d %d\n", 200, 4);
  for(long long d = 0; d<numdatapoints; ++d){
    writeDataPoint(); 
  }
  fprintf(fp, "%d %d\n", 0, 0); 
  fclose(fp); 
  return 0; 
}

