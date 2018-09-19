#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <list>
#include <sstream>
#include <algorithm>

int n, j, k;

typedef struct node {
    int val;
    std::vector<node*> neigh;
} node;

node * far;

struct tree{
	std::vector<node*> nodes;
	int size;
};

int dfs(tree * t, node * s){
	int l = -1;
	std::vector<bool> visited(t->nodes.size(), false);
	std::stack<node*> stack; 
	stack.push(s);
	while(!stack.empty()){
		s = stack.top();
		far = s;
		stack.pop();
		if(!visited[s->val-1]){
			visited[s->val-1] = true;
		}
		for(int i = 0; i<s->neigh.size(); ++i){
			if(!visited[s->neigh[i]->val-1]){
				stack.push(s->neigh[i]);
			}
		}
	}
	return l;
}

int main(){
	scanf("%d", &n);
	tree* t = new tree();
	std::vector<bool> vis(n, false); 
	t->nodes.resize(n);
	for(int i = 0; i<n-1; ++i){
		scanf("%d %d", &j, &k);
		if(!vis[j-1]){
			t->nodes[j-1] = new node();
			t->nodes[j-1]->val = j;
		  vis[j-1] = true;
		}
		if(!vis[k-1]){
			t->nodes[k-1] = new node();
			t->nodes[k-1]->val = k;
			vis[k-1] = true;
		}
		t->nodes[j-1]->neigh.push_back(t->nodes[k-1]);
		t->nodes[k-1]->neigh.push_back(t->nodes[j-1]);
	}
	int q = dfs(t, t->nodes[0]);
	printf("%d\n", far->val);
	int answer = dfs(t, far);
	printf("%d\n", answer);
  return 0;
}
