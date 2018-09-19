#include </Users/Dan/Documents/cp/library/graph/articulations.cpp>

//https://codeforces.com/problemset/problem/1000/E

struct BridgeTree{
  vector<vector<int> > roundNodes; //..new bridge tree nodes
  vector<vector<int> > squareNodes; //..for each roundNode, their associated original graph nodes
};

/*
  Compresses a graph into its bridge-tree
*/


BridgeTree buildBridgeTree(){
  BridgeTree bt;

  findArticulations();
  int componentNumber = -1;
  vector<int> bridgeEndpoints;
  vector<int> nodeComponentNumbers(V, 0);
  set<pair<int, int> > bridgeSet;

  for(int i = 0; i<V; ++i) {
    nodeComponentNumbers[i] = -1;
    visited[i] = -1;
  }

  for(int i = 0; i<(int)bridges.size(); ++i){
    bridgeEndpoints.push_back(bridges[i].first);
    bridgeEndpoints.push_back(bridges[i].second);
    bridgeSet.insert(make_pair(bridges[i].first, bridges[i].second));
    bridgeSet.insert(make_pair(bridges[i].second, bridges[i].first));
  }

  for(int i = 0; i<(int)bridgeEndpoints.size(); ++i){
    int u = bridgeEndpoints[i];
    if(nodeComponentNumbers[u] != -1) continue;
    componentNumber++;
    bt.roundNodes.push_back(vector<int>());
    bt.squareNodes.push_back(vector<int>());
    stack<int> s;
    s.push(u);
    while(!s.empty()){
      u = s.top(); s.pop();
      if(visited[u] == i) continue;
      visited[u] = i;
      nodeComponentNumbers[u] = componentNumber;
      bt.squareNodes[componentNumber].push_back(u);
      for(int k : graph[u]){
        if(bridgeSet.count(make_pair(u, k)) == 0 && visited[k] != i){
          s.push(k);
        }
      }
    }
  }

  for(int i = 0; i<(int)bridges.size(); ++i){
    bt.roundNodes[nodeComponentNumbers[bridges[i].first]].push_back(nodeComponentNumbers[bridges[i].second]);
    bt.roundNodes[nodeComponentNumbers[bridges[i].second]].push_back(nodeComponentNumbers[bridges[i].first]);
  }

  return bt;
}

pair<int, int> diameterUtil(int root, vector<vector<int> > tree){
  vector<int> dist(V, 0);
  dist[root] = 1;
  stack<int> s;
  s.push(root);
  while(!s.empty()){
    int u = s.top();
    s.pop();
    for(int i = 0; i<(int)tree[u].size(); ++i){
      if(dist[tree[u][i]] != 0) continue;
      s.push(tree[u][i]);
      dist[tree[u][i]] = dist[u] + 1;
    }
  }
  int mx = INT_MIN, node = -1;
  for(int i = 0; i<V; ++i){
    if(mx < dist[i]){
      mx = dist[i];
      node = i;
    }
  }
  return make_pair(mx, node);
}

int main(){
  graphIntake(); 
  BridgeTree bt = buildBridgeTree(); 
  printf("Round Nodes\n"); 
  for(int i = 0; i < bt.roundNodes.size(); ++i){
    for(int k = 0; k < bt.roundNodes[i].size(); ++k){
      printf("%d ", bt.roundNodes[i][k]); 
    }
    printf("\n"); 
  }
  printf("Square Nodes\n"); 
  for(int i = 0; i < bt.squareNodes.size(); ++i){
    for(int k = 0; k < bt.squareNodes[i].size(); ++k){
      printf("%d ", bt.squareNodes[i][k]); 
    }
    printf("\n"); 
  }
  return 0;
}
