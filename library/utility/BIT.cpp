#include <bits/stdc++.h>
using namespace std;

int n, c, j, t; vector<int> v; string s; 

class BITree{
  vector<int> BIT;
  int size;
  public:
    BITree(int n){
      size = n;
      BIT.resize(n);
    }
    ~BITree(){BIT.clear();}
    
    int get(int i){
      return BIT[i+1];
    }

    void update(int i, int delta){
      i++;
      while (i <= size){
        BIT[i] += delta;
        i += i & -i;
      }
    }

    int sum(int i){
      int sum = 0;
      while(i > 0){
        sum += BIT[i];
        i -= i&-i;
      }
      return sum;
    }

    int rangeSum(int i, int j){ //uses BIT.index + 1
        return sum(j) - sum(i-1);
    }
    private:
};

int main(){
  BITree bit(16);
  for(int i = 0; i<16; ++i) bit.update(i, i+1);
  // for(int i = 0; i<16; ++i){
  //   j = bit.get(i);
  //   printf("%d ", j);
  // }
  // printf("\n");
  int sum = bit.rangeSum(9, 13); 
  printf("%d\n", sum);
  return 0;
}
