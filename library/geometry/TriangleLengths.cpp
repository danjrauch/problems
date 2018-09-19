#include <bits/stdc++.h>
using namespace std;

int n, j, c, r; vector<int> v; string s;

int main(){
  scanf("%d", &n);
  for(int i = 0; i<n; ++i){
    scanf("%d", &j); v.push_back(j);
  }
  sort(v.begin(), v.end());
  for(int i = 0; i<n-2; ++i){
    if(v[i]+v[i+1] > v[i+2]){
      printf("YES\n");
      return 0;
    }
  }
  printf("NO\n");
  return 0;
}
