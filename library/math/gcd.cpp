#include <bits/stdc++.h>
using namespace std;
int n, c, j, t; vector<int> v; string s;

int GCD(int a, int b){
   if (b==0) return a;
   return GCD(b,a%b);
}

int main(){
  c = GCD(10,5);
  printf("%d\n", c);
  return 0;
}
