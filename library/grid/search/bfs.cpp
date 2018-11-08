#include <bits/stdc++.h>
using namespace std;

pair<int, int> src;
pair<int, int> dest;
int rows, cols;

vector<pair<int, int> > path;

struct cell{
  int parent_i, parent_j;
};

bool isValid(int row, int col){
  return (row>=0) && (row<rows) && (col>=0) && (col<cols);
}

void tracePath(vector<vector<cell> > cellDetails, pair<int,int> dest){
  printf("The path is: ");
  int row = dest.first;
  int col = dest.second;
  stack<pair<int, int> > Path;
  while(!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)){
    Path.push(make_pair(row,col));
    int temp_row = cellDetails[row][col].parent_i;
    int temp_col = cellDetails[row][col].parent_j;
    row = temp_row;
    col = temp_col;
  }
  Path.push(make_pair(row, col));
  while(!Path.empty()){
    pair<int, int> p = Path.top();
    Path.pop();
    path.push_back(p);
    printf("-> (%d,%d) ", p.first, p.second);
  }
  printf("\n");
  return;
}

void BFS(vector<vector<int> > grid, pair<int, int> src, pair<int, int> dest){
  bool foundDest = false;
  bool visited[rows][cols];
  vector<vector<cell> > cellDetails(rows); 
  for(int i = 0; i<rows; ++i){
    cellDetails[i].resize(cols);
    for(int k = 0; k<cols; ++k){
      visited[i][k] = false;
      cellDetails[i][k].parent_i = -1;
      cellDetails[i][k].parent_j = -1;
    }
  }
  queue<pair<int, int> > q;
  q.push(src);
  visited[src.first][src.second] = true;
  cellDetails[src.first][src.second].parent_i = src.first;
  cellDetails[src.first][src.second].parent_j = src.second;
  int i, j;
  while(!q.empty()){
    pair<int,int> p = q.front(); q.pop();
    i = p.first;
    j = p.second;
    //grid[i][j] = 3;
    if(i == dest.first && j == dest.second){
      printf("The destination has been found.\n");
      tracePath(cellDetails, dest);
      foundDest = true;
      visited[i][j] = 1;
      return;
    }
    if(isValid(i-1, j) && grid[i-1][j]){
      if(!visited[i-1][j]){
        q.push(make_pair(i-1, j));
        cellDetails[i-1][j].parent_i = i;
        cellDetails[i-1][j].parent_j = j;
        visited[i-1][j] = 1;
        //grid[i-1][j] = 2;
      }
    }
    if(isValid(i+1, j) && grid[i+1][j]){
      if(!visited[i+1][j]){
        q.push(make_pair(i+1, j));
        cellDetails[i+1][j].parent_i = i;
        cellDetails[i+1][j].parent_j = j;
        visited[i+1][j] = 1;
        //grid[i+1][j] = 2;
      }
    }
    if(isValid(i, j-1) && grid[i][j-1]){
      if(!visited[i][j-1]){
        q.push(make_pair(i, j-1));
        cellDetails[i][j-1].parent_i = i;
        cellDetails[i][j-1].parent_j = j;
        visited[i][j-1] = 1;
        //grid[i][j-1] = 2;
      }
    }
    if(isValid(i, j+1) && grid[i][j+1]){
      if(!visited[i][j+1]){
        q.push(make_pair(i, j+1));
        cellDetails[i][j+1].parent_i = i;
        cellDetails[i][j+1].parent_j = j;
        visited[i][j+1] = 1;
        //grid[i][j+1] = 2;
      }
    }
    if(isValid(i-1, j+1) && grid[i-1][j+1]){
      if(!visited[i-1][j+1]){
        q.push(make_pair(i-1, j+1));
        cellDetails[i-1][j+1].parent_i = i;
        cellDetails[i-1][j+1].parent_j = j;
        visited[i-1][j+1] = 1;
        //grid[i][j+1] = 2;
      }
    }
    if(isValid(i+1, j+1) && grid[i+1][j+1]){
      if(!visited[i+1][j+1]){
        q.push(make_pair(i+1, j+1));
        cellDetails[i+1][j+1].parent_i = i;
        cellDetails[i+1][j+1].parent_j = j;
        visited[i+1][j+1] = 1;
        //grid[i][j+1] = 2;
      }
    }
    if(isValid(i-1, j-1) && grid[i-1][j-1]){
      if(!visited[i-1][j-1]){
        q.push(make_pair(i-1, j-1));
        cellDetails[i-1][j-1].parent_i = i;
        cellDetails[i-1][j-1].parent_j = j;
        visited[i-1][j-1] = 1;
        //grid[i][j+1] = 2;
      }
    }
    if(isValid(i+1, j-1) && grid[i+1][j-1]){
      if(!visited[i+1][j-1]){
        q.push(make_pair(i+1, j-1));
        cellDetails[i+1][j-1].parent_i = i;
        cellDetails[i+1][j-1].parent_j = j;
        visited[i+1][j-1] = 1;
        //grid[i][j+1] = 2;
      }
    }
  }
  if(!foundDest) printf("No path found.\n");
}

// vector<vector<int> > v;

int main(){
  scanf("%d %d", &rows, &cols);
  vector<vector<int> > v;
  double num;
  srand(time(0));
  v.resize(rows);
  for(int i = 0; i<rows; ++i){
    v[i].resize(cols);
    for(int k = 0; k<cols; ++k){
      num = (double) rand() / (RAND_MAX);
      if(num < .2) v[i][k] = 0;
      else v[i][k] = 1;
    }
  }
  // rows = 8; cols = 6;
  // v = {{1, 1, 1, 1, 1, 1},
  //         {1, 1, 1, 1, 1, 1},
  //         {1, 0, 0, 0, 1, 1},
  //         {1, 0, 1, 1, 0, 1},
  //         {0, 0, 1, 1, 0, 1},
  //         {1, 1, 1, 0, 0, 1},
  //         {1, 1, 0, 1, 1, 1},
  //         {1, 1, 1, 1, 1, 1}};
  v[0][0] = 1;
  src = make_pair(0,0);
  v[v.size()-1][v[0].size()-1] = 1;
  dest = make_pair(v.size()-1, v[0].size()-1);
  for(int i = 0; i<rows; ++i){
    for(int k = 0; k<cols; ++k){
      printf("%d", v[i][k]);
    }
    printf("\n");
  }
  BFS(v, src, dest);
  for(int i = 0; i<path.size(); ++i) v[path[i].first][path[i].second] = 4;
  for(int i = 0; i<rows; ++i){
    for(int k = 0; k<cols; ++k){
      printf("%d", v[i][k]);
    }
    printf("\n");
  }
  return 0;
}
