#include <bits/stdc++.h>
using namespace std;
int t;
int main(){
  scanf("%d", &t);
  for(int i = 0; i<t; ++i){
    int n, c, j;
    bool doable = true;
    vector<int> a; vector<int> b;
    multiset<int> s;
    scanf("%d %d", &n, &c);
    for(int k = 0; k<n; ++k){
      scanf("%d", &j);
      a.push_back(j);
    }
    for(int k = 0; k<n; ++k){
      scanf("%d", &j);
      s.insert(j);
    }
    for(int k = 0; k<n; ++k){
      auto w = s.lower_bound(c-a[k]);
      if(w!=s.end()){
        s.erase(w);
      }
      else{
        printf("NO\n"); doable = false; break;
      }
    }
    if(doable) printf("YES\n");
  }
  return 0;
}
