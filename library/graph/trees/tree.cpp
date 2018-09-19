#include <bits/stdc++.h>
using namespace std;
int c, j, t, a=1, x; vector<int> v; string s;

typedef struct node{
  int num;
  vector<node*> nei;
  bool vis = false;
}node;

typedef struct tree{
  node * root;
  vector<node*> nodes;
}tree;

void bfs(node start, int end) {
 queue<node*> s;
 s.push(start);
 start->vis = true;
 while (s.empty() == false) {
  top = s.front();
  s.pop();
  if(s->num == end) return n;
  for(int i = 0; i<top->nei.size(); ++i){
    if(!top->nei[i]->vis){
      s.push(top->nei[i]);
      top->nei[i]->vis = true;
    }
  }
 }
}

int main(){
  scanf("%d", &j);
  string::size_type sz;
  tree *b = new tree();
  node *n = new node();
  n->num = j;
  b->root = n;
  b->nodes.push_back(n);
  cin.ignore();
  while(s!=-1){
    getline(cin, s);
    stringstream ss(s);
    string buf;
    vector<string>tokens;
    while(ss >> buf) tokens.push_back(buf);
    a = stoi(tokens[0], &sz);
    bool in = false;
    for(int i = 0; i<b->nodes.size(); ++i){
      if(b->nodes[i]->num == a) {
        in = true;
        x = i;
      }
    }
    if(in){
      for(int i = 1; i<tokens.size(); ++i){
        node* n = new node();
        scanf("%d", &t);
        n->num = t;
        b->nodes[x]->nei.push_back(n);
      }
    }
    else{
      node*w = new node();
      w->num = a;
      for(int i = 1; i<tokens.size(); ++i){
        node* n = new node();
        scanf("%d", &t);
        n->num = t;
        w->nei.push_back(n);
      }
    }
    in = false;

  }
  return 0;
}
