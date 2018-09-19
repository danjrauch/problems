#include <bits/stdc++.h>
using namespace std; 

int v, e, a, b; 

//also has a chromatic number 2
bool isBipartite(vector<vector<int> > graph){
    vector<int> colors(v, -1); 
    colors[0] = 1; 
    queue<int> q; 
    q.push(0);
    while(!q.empty()){
        int u = q.front(); 
        q.pop(); 
        for(int i = 0; i<graph[u].size(); ++i){
            if(colors[graph[u][i]] == -1){
                colors[graph[u][i]] = 1 - colors[u]; 
                q.push(graph[u][i]); 
            }
            else if(colors[graph[u][i]] == colors[u]){
                return false; 
            }
        }
    }
    return true; 
}

int main(){
    scanf("%d", &v); 
    while(v != 0){ 
        scanf("%d", &e); 
        vector<vector<int> >graph;
        graph.resize(v); 
        for(int i = 0; i<e; ++i){
            scanf("%d %d", &a, &b); 
            graph[a].push_back(b); 
            graph[b].push_back(a); 
        }
        if(isBipartite(graph)) printf("BICOLORABLE.\n"); 
        else printf("NOT BICOLORABLE.\n"); 
        scanf("%d", &v); 
    }
    return 0; 
}