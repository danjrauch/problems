/* Matches a pattern string to a text string in O(n+m)
 * where n = length of pattern string, m = length of text string */

#include<bits/stdc++.h>
using namespace std;
#define INF 2147483647
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int, int> pii;

#define MAX_N 100010

string T, P; 
int b[MAX_N], n, m; 
vector<int> idxs; 

void kmpPreprocess(){
  int i = 0, j = -1; b[0] = -1; 
  while(i<P.size()){
    while(j>=0 && P.at(i) != P.at(j)) j = b[j]; 
    i++; j++; 
    b[i] = j; 
  }
}

void kmpSearch(){
  int i = 0, j = 0; 
  while(i<T.size()){
    while(j>=0 && T.at(i) != P.at(j)) j = b[j]; 
    i++; j++; 
    if(j == P.size()){
      idxs.push_back(i-j); 
      j = b[j]; 
    }
  }
}

int main(){
  T = "dktsadk"; 
  P = "tsa"; 
  kmpPreprocess(); 
  kmpSearch(); 
  for(int i = 0; i<idxs.size(); ++i){
    printf("%d ", idxs[i]); 
  }
  printf("\n"); 
  return 0;
}