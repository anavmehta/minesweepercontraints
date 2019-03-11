# minesweepercontraints
Minesweeper Constraints
In a minesweeper solver, you are given an array nxm of cells, which each cell indicating a number (upto 9), which indicates the number of mines in itself and the eight numbers covering it. The goal is to solve the constraints and uncover all the mines in the grid.
Input description:
The mine status where each number upto 9 the mines in itself and around it. These are the constraints of the 7×7 minesweeper.
1100111
2321122
3532122
3653022
2432011
2332121
1111110
Output description:
The solution of the mine field, which satisfies the input status constraint. “x” represents the mine at the location, “_” represents an empty field.
_______
x____x_
_xx___x
x_x____
_xx___x
_______
_x__x__

Input Generation
The input grid is generated in the generateMineField() routine. The inputs to the generation are the size of the minefield N and M and also probability P (or density) of the minefield. A probability P=0 means there are no mines in the minefield and P=100 implies that all the cells are mines in the minefield. A random number is chosen for each grid element and if the random number is less than P, a mine is assigned to the grid and a boolean array mines is generated. The input to the constraint solver is that status of each grid which is an integer of the count the mines of itself and the eight numbers.

inputs N, M //size of the minefield
input  P //probability of cell being a mine
foreach cell x,y in minefield 
   a) choose a random number between 0 and 100
   b) if the number is less than P assign a mine to the cell (mines[x][y] = true)
forach cell x,y in the minefield
   a) assign status[x][y] to sum of the mines in itself and the numbers
 $status[x][y] = \sum_{dx=-1}^{dx=1}{\sum_{dy=-1}^{dy=1}{mines[x+dx][y+dy])}$ 
Brute Force Algorithm
The Brute Force Algorithm is to generate all possible minesweeper combinations and try every configuration one by one until the correct configuration is found which satisfies the constraint. This is very hard.

Backtracking Algorithm
Like all other Backtracking problems, we can solve Minesweeper by one by one mine to open cells. Before assigning a cell to a mine, we check whether it is safe to assign. We basically check that the number of mines in the cell and surrounding it have atleast 1 supporting the cell to be a mine. After checking for safety, we assign the cell to a mine, and recursively check whether this assignment leads to a solution or not. If the assignment doesn’t lead to a solution, then we search recursively for a solution with the cell without a mine.

If all cells are assigned and all the all constraints are covered then return true
Find x,y of an unassigned cell
  If there is none, return false
  For the current x,y cell
    a) If there is no conflict for mine at cell x,y (ie the number of mines at cell x,y and 
       surrounding cells, have atleast one mine)
        assign mine to x,y and decrease the mine count of itself and neighbors and recursively 
        try fill in rest of grid
    b) If recursion successful, return true
    c) Else, remove mine, and increase the mine count of itself and neighbors and recursively 
       try fill in rest of grid
  If the cell has been tried with and without a mine and no solution found, return false
Examples:

Input : 
011
122
122
Output :
___
__x
_x_
Analysis :
Since there are nine locations, there are 9 equations, with each cell either has a mine or not. Lets say status[x][y] as input can be defined as sum of boolean variables mines[x][y] in neighboring cells plus itself
 $status[x][y] = \sum_{dx=-1}^{dx=1}{\sum_{dy=-1}^{dy=1}{mines[x+dx][y+dy])}$ 
1. status[0][0] = 0 = mines[0][0] + mines[0][1] + mines[1][0] + mines[1][1]
implies that mines[0][0] = mines[0][1] = mines[1][0] = mines[1][1] = 0
2. status[1][0] = 1 = mines[0][0] + mines[0][1] + mines[2][0] + mines[1][0] + mines[1][1] + mines[2][1]
implies that mines[2][0] + mines[2][1] = 1
3. status[2][0] = 1 = mines[2][0] + mines[1][0] + mines[2][1] + mines[1][1]
implies that mines[2][0] + mines[2][1] = 1
4. status[0][1] = 1 = mines[0][0] + mines[0][1] + mines[0][2] + mines[1][0] + mines[1][1] + mines[1][2]
implies that mines[0][2] + mines[1][2] = 1
5. status[1][1] = 2 = mines[0][0] + mines[0][1] + mines[0][2] + mines[1][0] + mines[1][1] + mines[1][2] + mines[2][0] + mines[2][1] + mines[2][2]
implies that mines[0][2] + mines[1][2] + mines[2][0] + mines[2][1] + mines[2][2] = 2
6. status[2][1] = 2 = mines[1][0] + mines[1][1] + mines[1][2] + mines[2][0] + mines[2][1] + mines[2][2]
implies that mines[1][2] + mines[2][0] + mines[2][1] + mines[2][2] = 2
7. status[0][2] = 1 = mines[0][1] + mines[0][2] + mines[1][1] + mines[1][2]
implies that mines[0][2] + mines[1][2] = 1
8. status[1][2] = 2 = mines[0][1] + mines[0][2] + mines[1][1] + mines[1][2] + mines[2][1] + mines[2][2]
implies that mines[0][2] + mines[1][2] + mines[2][1] + mines[2][2] = 2
9. status[2][2] = 2 = mines[1][1] + mines[1][2] + mines[2][1] + mines[2][2]
implies that mines[1][2] + mines[2][1] + mines[2][2] = 2

By trimming further we get mines[1][2] = 1 and mines[2][1] = 1

Few more examples minesweeper Input and Output.

Input : 
13431
25663
24564
24675
12443
Output :
_xxx_
__x__
x_xxx
_x_xx
__xx_
Input :
1100111
2321122
3532122
3653022
2432011
2332121
1111110
Output :
_______
x____x_
_xx___x
x_x____
_xx___x
_______
_x__x__
