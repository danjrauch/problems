#include <bits/stdc++.h>
using namespace std;
int n, c, j, t; vector<int> v; string s;
int main(){
  scanf("%d", &n);
  for(int i = 0; i<n; ++i){
    scanf("%d", &j);
    v.push_back(j);
  }
  int best = 0; int sum = 0;
  for(int i = 0; i<n; ++i){
    sum = max(v[i], sum+v[i]);
    best = max(best, sum);
  }
  printf("%d\n", best);
  return 0;
}
