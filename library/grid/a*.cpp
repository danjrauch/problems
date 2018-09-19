#include <bits/stdc++.h>
using namespace std;

//diagonals allowed

int rows, cols;
vector<pair<int, int> > path;

struct cell{
  int parent_i, parent_j;
  double f, g, h;
};

bool isValid(int row, int col){
  return (row>=0) && (row<rows) && (col>=0) && (col<cols);
}

bool isDestination(int row, int col, pair<int, int> dest){
  if(row == dest.first && col == dest.second) return true;
  else return false;
}

int calculateHValue(int row, int col, pair<int, int> dest){
  return max(abs(row - dest.first), abs(col - dest.second));
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
  return;
}

void aStarSearch(vector<vector<int> > grid, pair<int, int> src, pair<int, int> dest){
  if(!isValid(src.first, src.second)){
    printf("Source invalid.\n");
    return;
  }
  if(!isValid(dest.first, dest.second)){
    printf("Destination is invalid.\n");
    return;
  }
  if(!(grid[src.first][src.second]) || !(grid[dest.first][dest.second])){
    printf("Source or destinaton is blocked.\n");
    return;
  }
  if(isDestination(src.first, src.second, dest)){
    printf("We are already here.\n");
    return;
  }
  bool closedList[rows][cols];
  memset(closedList, false, sizeof(closedList));

  vector<vector<cell> > cellDetails(rows);
  for(int i = 0; i<rows; ++i) cellDetails[i].resize(cols);
  for(int i = 0; i<rows; ++i){
    for(int j = 0; j<cols; ++j){
      cellDetails[i][j].f = 1e9;
      cellDetails[i][j].g = 1e9;
      cellDetails[i][j].h = 1e9;
      cellDetails[i][j].parent_i = -1;
      cellDetails[i][j].parent_j = -1;
    }
  }
  int i = src.first, j = src.second;
  cellDetails[i][j].f = 0;
  cellDetails[i][j].g = 0;
  cellDetails[i][j].h = 0;
  cellDetails[i][j].parent_i = i;
  cellDetails[i][j].parent_j = j;

  set<pair<int, pair<int, int> > > openList;
  openList.insert(make_pair(0, make_pair(i, j)));
  bool foundDest = false;
  while(!openList.empty()){
    pair<int, pair<int, int> > p = *openList.begin();
    openList.erase(openList.begin());
    i = p.second.first;
    j = p.second.second;
    closedList[i][j] = true;
    int gnew = 0;
    int hnew = 0;
    int fnew = 0;
    if(isValid(i-1, j)){
      if(isDestination(i-1, j, dest)){
        cellDetails[i-1][j].parent_i = i;
        cellDetails[i-1][j].parent_j = j;
        printf("The destination has been found.\n");
        tracePath(cellDetails, dest);
        foundDest = true;
        return;
      }
      else if(!closedList[i-1][j] && grid[i-1][j]){
        gnew = cellDetails[i][j].g + 1;
        hnew = calculateHValue(i-1, j, dest);
        fnew = gnew + hnew;
        if(cellDetails[i-1][j].f == 1e9 || cellDetails[i-1][j].f > fnew){
          openList.insert(make_pair(fnew, make_pair(i-1, j)));
          cellDetails[i-1][j].f = fnew;
          cellDetails[i-1][j].g = gnew;
          cellDetails[i-1][j].h = hnew;
          cellDetails[i-1][j].parent_i = i;
          cellDetails[i-1][j].parent_j = j;
        }
      }
    }
    ///////////////
    if(isValid(i+1, j)){
      if(isDestination(i+1, j, dest)){
        cellDetails[i+1][j].parent_i = i;
        cellDetails[i+1][j].parent_j = j;
        printf("The destination has been found.\n");
        tracePath(cellDetails, dest);
        foundDest = true;
        return;
      }
      else if(!closedList[i+1][j] && grid[i+1][j]){
        gnew = cellDetails[i][j].g + 1;
        hnew = calculateHValue(i+1, j, dest);
        fnew = gnew + hnew;
        if(cellDetails[i+1][j].f == 1e9 || cellDetails[i+1][j].f > fnew){
          openList.insert(make_pair(fnew, make_pair(i+1, j)));
          cellDetails[i+1][j].f = fnew;
          cellDetails[i+1][j].g = gnew;
          cellDetails[i+1][j].h = hnew;
          cellDetails[i+1][j].parent_i = i;
          cellDetails[i+1][j].parent_j = j;
        }
      }
    }
    ///////////////
    if(isValid(i, j+1)){
      if(isDestination(i, j+1, dest)){
        cellDetails[i][j+1].parent_i = i;
        cellDetails[i][j+1].parent_j = j;
        printf("The destination has been found.\n");
        tracePath(cellDetails, dest);
        foundDest = true;
        return;
      }
      else if(!closedList[i][j+1] && grid[i][j+1]){
        gnew = cellDetails[i][j].g + 1;
        hnew = calculateHValue(i, j+1, dest);
        fnew = gnew + hnew;
        if(cellDetails[i][j+1].f == 1e9 || cellDetails[i][j+1].f > fnew){
          openList.insert(make_pair(fnew, make_pair(i, j+1)));
          cellDetails[i][j+1].f = fnew;
          cellDetails[i][j+1].g = gnew;
          cellDetails[i][j+1].h = hnew;
          cellDetails[i][j+1].parent_i = i;
          cellDetails[i][j+1].parent_j = j;
        }
      }
    }
    ///////////////
    if(isValid(i, j-1)){
      if(isDestination(i, j-1, dest)){
        cellDetails[i][j-1].parent_i = i;
        cellDetails[i][j-1].parent_j = j;
        printf("The destination has been found.\n");
        tracePath(cellDetails, dest);
        foundDest = true;
        return;
      }
      else if(!closedList[i][j-1] && grid[i][j-1]){
        gnew = cellDetails[i][j].g + 1;
        hnew = calculateHValue(i, j-1, dest);
        fnew = gnew + hnew;
        if(cellDetails[i][j-1].f == 1e9 || cellDetails[i][j-1].f > fnew){
          openList.insert(make_pair(fnew, make_pair(i, j-1)));
          cellDetails[i][j-1].f = fnew;
          cellDetails[i][j-1].g = gnew;
          cellDetails[i][j-1].h = hnew;
          cellDetails[i][j-1].parent_i = i;
          cellDetails[i][j-1].parent_j = j;
        }
      }
    }
    ///////////////
    if(isValid(i-1, j+1)){
      if(isDestination(i-1, j+1, dest)){
        cellDetails[i-1][j+1].parent_i = i;
        cellDetails[i-1][j+1].parent_j = j;
        printf("The destination has been found.\n");
        tracePath(cellDetails, dest);
        foundDest = true;
        return;
      }
      else if(!closedList[i-1][j+1] && grid[i-1][j+1]){
        gnew = cellDetails[i][j].g + 1;
        hnew = calculateHValue(i-1, j+1, dest);
        fnew = gnew + hnew;
        if(cellDetails[i-1][j+1].f == 1e9 || cellDetails[i-1][j+1].f > fnew){
          openList.insert(make_pair(fnew, make_pair(i-1, j+1)));
          cellDetails[i-1][j+1].f = fnew;
          cellDetails[i-1][j+1].g = gnew;
          cellDetails[i-1][j+1].h = hnew;
          cellDetails[i-1][j+1].parent_i = i;
          cellDetails[i-1][j+1].parent_j = j;
        }
      }
    }
    ///////////////
    if(isValid(i-1, j-1)){
      if(isDestination(i-1, j-1, dest)){
        cellDetails[i-1][j-1].parent_i = i;
        cellDetails[i-1][j-1].parent_j = j;
        printf("The destination has been found.\n");
        tracePath(cellDetails, dest);
        foundDest = true;
        return;
      }
      else if(!closedList[i-1][j-1] && grid[i-1][j-1]){
        gnew = cellDetails[i][j].g + 1;
        hnew = calculateHValue(i-1, j-1, dest);
        fnew = gnew + hnew;
        if(cellDetails[i-1][j-1].f == 1e9 || cellDetails[i-1][j-1].f > fnew){
          openList.insert(make_pair(fnew, make_pair(i-1, j-1)));
          cellDetails[i-1][j-1].f = fnew;
          cellDetails[i-1][j-1].g = gnew;
          cellDetails[i-1][j-1].h = hnew;
          cellDetails[i-1][j-1].parent_i = i;
          cellDetails[i-1][j-1].parent_j = j;
        }
      }
    }
    ///////////////
    if(isValid(i+1, j+1)){
      if(isDestination(i+1, j+1, dest)){
        cellDetails[i+1][j+1].parent_i = i;
        cellDetails[i+1][j+1].parent_j = j;
        printf("The destination has been found.\n");
        tracePath(cellDetails, dest);
        foundDest = true;
        return;
      }
      else if(!closedList[i+1][j+1] && grid[i+1][j+1]){
        gnew = cellDetails[i][j].g + 1;
        hnew = calculateHValue(i+1, j+1, dest);
        fnew = gnew + hnew;
        if(cellDetails[i+1][j+1].f == 1e9 || cellDetails[i+1][j+1].f > fnew){
          openList.insert(make_pair(fnew, make_pair(i+1, j+1)));
          cellDetails[i+1][j+1].f = fnew;
          cellDetails[i+1][j+1].g = gnew;
          cellDetails[i+1][j+1].h = hnew;
          cellDetails[i+1][j+1].parent_i = i;
          cellDetails[i+1][j+1].parent_j = j;
        }
      }
    }
    ///////////////
    if(isValid(i+1, j-1)){
      if(isDestination(i+1, j-1, dest)){
        cellDetails[i+1][j-1].parent_i = i;
        cellDetails[i+1][j-1].parent_j = j;
        printf("The destination has been found.\n");
        tracePath(cellDetails, dest);
        foundDest = true;
        return;
      }
      else if(!closedList[i+1][j-1] && grid[i+1][j-1]){
        gnew = cellDetails[i][j].g + 1;
        hnew = calculateHValue(i+1, j-1, dest);
        fnew = gnew + hnew;
        if(cellDetails[i+1][j-1].f == 1e9 || cellDetails[i+1][j-1].f > fnew){
          openList.insert(make_pair(fnew, make_pair(i+1, j-1)));
          cellDetails[i+1][j-1].f = fnew;
          cellDetails[i+1][j-1].g = gnew;
          cellDetails[i+1][j-1].h = hnew;
          cellDetails[i+1][j-1].parent_i = i;
          cellDetails[i+1][j-1].parent_j = j;
        }
      }
    }
    ///////////////
  }
  if(!foundDest) printf("There is no path.\n");
  return;
}

vector<vector<int> > grid;

int main(){
  scanf("%d %d", &rows, &cols);
  double num;
  srand(time(0));
  grid.resize(rows);
  for(int i = 0; i<rows; ++i){
    grid[i].resize(cols);
    for(int j = 0; j<cols; ++j){
      num = (double) rand() / (RAND_MAX);
      if(num < .2) grid[i][j] = 0;
      else grid[i][j] = 1;
    }
  }
  // rows = 8; cols = 6;
  // grid = {{1, 1, 1, 1, 1, 1},
  //         {1, 1, 1, 1, 1, 1},
  //         {1, 0, 0, 0, 1, 1},
  //         {1, 0, 1, 1, 0, 1},
  //         {1, 0, 1, 1, 0, 1},
  //         {1, 1, 1, 0, 0, 1},
  //         {1, 1, 0, 1, 1, 1},
  //         {1, 1, 1, 1, 1, 1}};
  grid[0][0] = 1;
  pair<int, int> src = make_pair(0,0);
  grid[grid.size()-1][grid[0].size()-1] = 1;
  pair<int, int> dest = make_pair(grid.size()-1, grid[0].size()-1);
  for(int i = 0; i<grid.size(); ++i){
    for(int k = 0; k<grid[0].size(); ++k){
      printf("%d ", grid[i][k]);
    }
    printf("\n");
  }
  aStarSearch(grid, src, dest);
  for(int i = 0; i<path.size(); ++i){
    grid[path[i].first][path[i].second] = 2;
  }
  printf("\n");
  for(int i = 0; i<grid.size(); ++i){
    for(int k = 0; k<grid[0].size(); ++k){
      printf("%d ", grid[i][k]);
    }
    printf("\n");
  }
  return 0;
}
