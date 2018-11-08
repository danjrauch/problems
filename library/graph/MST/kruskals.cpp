#include<bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int> > > graph; 
vector<pair<int, pair<int, int> > > edges; 

int v, e, a, b, we, t, numComps; 
int tempRank; 

vector<int> split(string s){
  string buf; 
  stringstream ss(s); 
  vector<int> tokens; 
  for(int i = 0; i<s.size(); ++i){
    if(s.at(i) == ','){
      s.erase(i); 
    }
  }
  while(ss >> buf){
    tokens.push_back(stoi(buf)); 
  }
  return tokens; 
}

void addEdge(int s, int d, int w){
  graph[s].push_back(make_pair(d, w));
  graph[d].push_back(make_pair(s, w));
  edges.push_back(make_pair(w, make_pair(s, d)));
}

void graphIntake(){
  e = v; 
  graph.resize(v); 
  edges.clear(); 
  // for(int i = 0; i<e; ++i){
  //   scanf("%d", &a); 
  //   addEdge(i, a-1);
  // }
  string s;
  vector<int> f; 
  cin.ignore(); 
  for(int i = 0; i<v; ++i){
    getline(cin, s); 
    f = split(s); 
    for(int j = i; j<v; ++j){
      if(f[j] != 0){
        addEdge(i, j, f[j]); 
      } 
    }
  }
}

typedef struct subset{
  int parent; 
  int rank; 
}subset;

vector<subset> subsets; 

/*Finds the representative of a set with path compression*/
int find(int i){
  if (subsets[i].parent != i) subsets[i].parent = find(subsets[i].parent); 
  return subsets[i].parent; 
}

/*Combines two sets into one (higher rank higher up tree)*/
void Union(int x, int y){
  int xroot = find(x); 
  int yroot = find(y); 
  if(subsets[xroot].rank < subsets[yroot].rank) subsets[xroot].parent = yroot; 
  else if(subsets[xroot].rank > subsets[yroot].rank) subsets[yroot].parent = xroot; 
  else {
    subsets[yroot].parent = xroot; 
    subsets[xroot].rank++; 
  } 
}

void createSubsets(){
  subsets.resize(v); 
  for(int i = 0; i<v; ++i){
    subsets[i].parent = i; 
    subsets[i].rank = 0; 
  }
}

vector<pair<int, pair<int, int> > > res; 

void kruskals(){
  res.clear(); 
  sort(edges.begin(), edges.end()); 
  createSubsets(); 
  for(int i = 0; i<e; ++i){
    pair<int, pair<int, int> > front = edges[i]; 
    if(find(front.second.first) != find(front.second.second)){
      Union(front.second.first, front.second.second); 
      res.push_back(front); 
    }
  }
}

int tests; 

int main(){
  scanf("%d", &tests); 
  for(int i = 0; i<tests; ++i){
    scanf("%d", &v); 
    graphIntake(); 
    kruskals(); 
    printf("Case %d:\n", i+1); 
    for(int i = 0; i<res.size(); ++i){
      printf("%c-%c %d\n", res[i].second.first+65, res[i].second.second+65, res[i].first); 
    }
  }
  return 0;
}