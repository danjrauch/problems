#include <bits/stdc++.h>
using namespace std;
#define pi 3.141592653589793238462643383
#define convtoradian 0.0174533

int j, n, res, t, k, co, b, temp;
string s; string ss; string si;
vector<int> v;
char cc;
map<int,int> m;

int main(){
  scanf("%d %d", &t, &k);
  priority_queue<int> q;
  for(int i = 0; i<t; ++i){
    scanf("%d", &j);
    v.push_back(j);
    q.push(j);
    m[j] = i;
  }
  while(co<k && b<t){
    if(q.top()>v[b]){
      temp = v[b];
      v[b] = q.top();
      v[m[q.top()]] = temp;
      n = m[q.top()];
      m[q.top()] = m[temp];
      m[temp] = n;
      //q.push(temp);
      co++;
    }
    q.pop();
    b++;
  }
  for(int i = 0; i<t; ++i) printf("%d ", v[i]);
  printf("\n");
  return 0;
}
