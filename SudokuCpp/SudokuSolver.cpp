#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

vector<vector<int>> board = {{0, 2, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 6, 0, 0, 0, 0, 3},
                             {0, 7, 4, 0, 8, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 3, 0, 0, 2},
                             {0, 8, 0, 0, 4, 0, 0, 1, 0},
                             {6, 0, 0, 5, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 1, 0, 7, 8, 0},
                             {5, 0, 0, 0, 0, 9, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 4, 0}};

int rowLen = board.size();
int colLen = board[0].size();
int gridHeight = 3;
int gridWidth = 3;
int numberChoices[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

struct SquarePosition
{
    int rowPosition = -1, colPosition = -1;
};

void PrintSolveTime(high_resolution_clock::time_point startTime, high_resolution_clock::time_point endTime)
{
    auto timeTakenInSeconds = duration_cast<seconds>(endTime - startTime).count();
    auto timeTakenInMilliSeconds = duration_cast<milliseconds>(endTime - startTime).count();
    cout << "\nTime taken to solve : " << timeTakenInSeconds << "." << timeTakenInMilliSeconds % long(1E+3) << " seconds";
}

void PrintBoard()
{
    for (int row = 0; row < rowLen; ++row)
    {
        if (row % gridHeight == 0 && row != 0)
            cout << "------+-------+------" << endl;
        for (int col = 0; col < colLen; ++col)
        {
            if (col % gridWidth == 0 && col != 0)
                cout << "| ";
            if (col == colLen - 1)
                cout << board[row][col] << endl;
            else
                cout << board[row][col] << " ";
        }
    }
}

SquarePosition GetUnfilledPosition()
{
    SquarePosition square;
    for (int row = 0; row < rowLen; ++row)
    {
        for (int col = 0; col < colLen; ++col)
        {
            if (board[row][col] == 0)
            {
                square.rowPosition = row;
                square.colPosition = col;
                return square;
            }
        }
    }
    return square;
}

bool CanNumberBeInserted(int number, int currentRow, int currentCol)
{
    // check if number already exists in any other column in the same row
    for (int col = 0; col < colLen; ++col)
    {
        if (board[currentRow][col] == number && col != currentCol)
            return false;
    }
    // check if number already exists in any other row in the same column
    for (int row = 0; row < rowLen; ++row)
    {
        if (board[row][currentCol] == number && row != currentRow)
            return false;
    }
    // check if number already exists in any other position in the 3x3 grid
    int gridRowStartIndex = (currentRow / gridHeight) * 3, gridColStartIndex = (currentCol / gridWidth) * 3;
    int gridRowEndIndex = gridRowStartIndex + gridHeight, gridColEndIndex = gridColStartIndex + gridWidth;
    for (int row = gridRowStartIndex; row < gridRowEndIndex; ++row)
    {
        for (int col = gridColStartIndex; col < gridColEndIndex; ++col)
        {
            if (board[row][col] == number && row != currentRow && col != currentCol)
                return false;
        }
    }
    return true;
}

bool Solve()
{
    SquarePosition unfilledPosition = GetUnfilledPosition();
    if (unfilledPosition.rowPosition == -1 || unfilledPosition.colPosition == -1) // if no square is empty it means board is solved
        return true;
    int currentRow = unfilledPosition.rowPosition, currentCol = unfilledPosition.colPosition;
    for (int number : numberChoices)
    {
        if (CanNumberBeInserted(number, currentRow, currentCol))
        {
            board[currentRow][currentCol] = number;
            if (Solve())
                return true;
            // the board was unable to be solved at some point so reset all values till last solved position
            board[currentRow][currentCol] = 0;
        }
    }
    return false;
}

int main()
{
    cout << "\nBefore solving" << endl;
    PrintBoard();

    auto startTime = high_resolution_clock::now();
    bool isSolved = Solve();
    auto endTime = high_resolution_clock::now();

    if (isSolved)
    {
        cout << "\nAfter solving" << endl;
        PrintBoard();
    }
    else //unsolvable board
        cout << "The board is unsolvable" << endl;

    PrintSolveTime(startTime, endTime);

    return 0;
}