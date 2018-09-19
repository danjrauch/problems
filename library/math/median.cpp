#include <bits/stdc++.h>
using namespace std;
int n, c, j, t, d;
vector<int> v; vector<int> vv;
double s;

double findMedian(int k, vector<int> v, vector<int> vv){
  double res = 0;
  sort(vv.begin(), vv.end());
  if(k%2==0){
    res = (double)(vv[k/2-1] + vv[k/2]) / 2;
  }
  else{
    res = vv[k/2];
  }
  return res;
}

int main(){
  scanf("%d %d", &t, &d);
  for(int i = 0; i<d; ++i){
    scanf("%d", &n);
    v.push_back(n);
    vv.push_back(n);
  }
  v.push_back(n);
  for(int i = d; i<t; ++i){
    scanf("%d", &n);
    v.push_back(n);
    s = findMedian(i, v, vv);
    if(s*2 <= v[i+1]) c++;
    vv.push_back(v[i+1]);
  }
  printf("%d\n", c);
  return 0;
}
