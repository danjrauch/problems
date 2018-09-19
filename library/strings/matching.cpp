// Matches a pattern string to a text string in O(n+m)
// where n = length of pattern string, m = length of text string

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <queue>
#include <deque>
#include <bitset>
#include <iterator>
#include <list>
#include <stack>
#include <map>
#include <set>
#include <functional>
#include <numeric>
#include <utility>
#include <limits>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <iomanip>
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