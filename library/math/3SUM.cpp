#include <bits/stdc++.h>
using namespace std;

int t, n, j, num; vector<int> v; string s;
tuple<int,int,int> res;

void solve3SUM(vector<int> vs, int k){
	int a, start, end, b, c;
	sort(vs.begin(), vs.end());
	for(int i = 0; i < vs.size()-3; i++){
		a = vs[i];
		start = i+1; 
		end = vs.size()-1;
		while(start < end){
			b = vs[start];
			c = vs[end];
			if(a + b + c == k){
				get<0>(res) = a; get<1>(res) = b; get<2>(res) = c;
				fprintf(stderr, "%d %d %d\n", a, b, c);
				end--;
			}
			else if(a+b+c > k) end--;
			else start++;
		}
	}
}

int main(){
	scanf("%d %d", &t, &num);
	for(int i = 0; i < t; i++){
		scanf("%d", &j);
		v.push_back(j);
	}
	solve3SUM(v, num);
  return 0;
}
