#include<bits/stdc++.h>
using namespace std;

const int N = 1e5;
int n;
int tree[2 * N];

// build the segment tree after the initial elements are in array 'tree' 
void build(){
  for(int i = n-1; i > 0; --i) tree[i] = tree[i<<1] + tree[i<<1|1];
}

// modify value at p, 0 indexed, to equal 'value'
void modify(int p, int value){
  for(tree[p+=n] = value; p > 1; p >>= 1) tree[p>>1] = tree[p] + tree[p^1];
}

// sum query over interval [l, r), 0 index based
int query(int l, int r){
  int res = 0;
  for(l += n, r += n; l < r; l >>= 1, r >>= 1){
    if(l&1) res += tree[l++];
    if(r&1) res += tree[--r];
  }
  return res;
}

int main(){
  scanf("%d", &n);
  for(int i = 0; i < n; ++i) scanf("%d", tree+n+i);
  build();
  modify(0, 2);
  for(int i = 0; i<2*n; ++i) printf("%d ", tree[i]);
  printf("\n");
  printf("%d\n", query(0, 5));
  return 0; 
}
