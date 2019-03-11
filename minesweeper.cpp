// Copyright (c) Anav Mehta 2019
// minesweeper.cpp
#include<bits/stdc++.h>
using namespace std;
// NxM is used for the size of Minesweeper grid. Size will be NxM
int N, M;
#define MAXM 100
#define MAXN 100
bool mines[MAXN][MAXM];
bool grid[MAXN][MAXM];
bool visited[MAXN][MAXM];
int status[MAXN][MAXM];
int dx[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};
int dy[9] = {0, 0, 0, -1, -1, -1, 1, 1, 1};

// This checks if the cell location is valid
bool isValid(int x, int y){
    return (x >= 0 && y >= 0 && x < N && y < M);
}

// Print Grid when done
void printGrid(bool grid[MAXN][MAXM], int status[MAXN][MAXM])
{
    for (int row = 0; row < N; row++) {
       for (int col = 0; col < M; col++) {
            if(grid[row][col]) cout << "x";
            else cout <<  "_";
       }
       cout << endl;
    }
}

// Checks whether it will be legal to assign a mine to the given x, y
// if the status of the cells and the cells around it has enough values
// to support the mine
// then decrement the status of those cells else return false
bool isSafe(bool grid[MAXN][MAXM], int status[MAXN][MAXM], int x, int y) {
    if(!isValid(x,y)) return false;
    for(int i=0;i<9;i++){
        if(isValid(x+dx[i], y+dy[i]) && (status[x+dx[i]][y+dy[i]] - 1 < 0))
            return(false);
    }
    for(int i=0;i<9;i++){
        if(isValid(x+dx[i],y+dy[i])) status[x+dx[i]][y+dy[i]]--;
    }
    return true;
}

// This function finds an entry in grid that is not visited
bool findUnvisited(bool visited[MAXN][MAXM], int &x, int &y){
    for (x = 0; x < N; x++)
        for (y = 0; y < M; y++)
            if (!visited[x][y]) return(true);
    return(false);
}
// This function checks if all solver has finished
bool isDone(int status[MAXN][MAXM], bool visited[MAXN][MAXM]) {
    bool done = true;
    for(int i=0;i<N;i++)
        for(int j=0;j<M;j++) {
            done = done && (status[i][j] == 0) && visited[i][j];
        }

    return (done);
}

/* Takes a grid with status of cells and attempts to assign values to
  all unassigned locations in such a way to meet the requirements
  for minesweeper constraint solution- ie the whether the cell has a mine
  or not is consistent with the constraint solver */
bool SolveMinesweeper(bool grid[MAXN][MAXM], int status[MAXN][MAXM],
                      bool visited[MAXN][MAXM]) {
    int x, y;

    // If the solver is finished we are done
    bool done=isDone(status, visited);
    if(done) return true;
    // Find any unvisited, if all cells are visited and solver is done,
    //then no solution can be found
    if(!findUnvisited(visited, x, y)) return false;

    visited[x][y] = true;
    //find a valid mine
    if (isSafe(grid, status, x, y)) {
        // Make the tentative assignment
        grid[x][y] = true;
        // If true return success
        if(SolveMinesweeper(grid, status, visited)) return true;
        // failure, reset the status and update the status
        grid[x][y] = false;
        for(int i=0;i<9;i++){
            if(isValid(x+dx[i],y+dy[i]))
               status[x+dx[i]][y+dy[i]]++;
        }
    }
    // We can still solve the minesweeper with the grid[x][y] = false
    if(SolveMinesweeper(grid, status, visited)) return true;
    visited[x][y] = false;
    // Trigger backtracking
    return false;
}

// A routine to generate the input minefield and status to be used by
// the constraint solver
void generateMineField() {
    int P, rand_val;
    memset(grid, false, sizeof(grid));
    memset(visited, false, sizeof(visited));
    M=7;
    N=7;
    P=15; //Probability for the cell being a mine
   // Following fills the mines in the grid
    for(int x=0;x<N;x++){
        for(int y=0;y<M;y++){
            mines[x][y] = false;
            rand_val = rand() % 100;
            if (rand_val < P) mines[x][y] = true;
        }
    }
    //Build the constraint status for our minesweeper problem
    for(int x=0;x<N;x++){
        for(int y=0;y<M;y++){
            status[x][y] = 0;
            for(int k=0;k < 9;k++) {
                if(isValid(x+dx[k], y+dy[k]) && (mines[x+dx[k]][y+dy[k]]))
                    status[x][y]++;
            }
            cout << status[x][y] << "";
        }
        cout << endl;
    }
}

int main() {
    generateMineField();

    if (SolveMinesweeper(grid, status, visited)) {
        printGrid(grid, status);
    } else
        printf("No solution exists\n");

    return 0;
}
