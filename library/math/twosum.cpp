#include <bits/stdc++.h>
using namespace std;
int n, c, j, t, x; vector<int> v; string s;
int main(){
  scanf("%d %d", &n, &x);
  for(int i = 0; i<n; ++i){
    scanf("%d", &j);
    v.push_back(j);
  }
  sort(v.begin(), v.end());
  int a = 0;
  int b = v.size()-1;
  while(a!=b){
    c = v[a]+v[b];
    if(c == x) printf("%d %d\n", v[a], v[b]);
    if(c > x) b--;
    else a++;
  }
  return 0;
}
