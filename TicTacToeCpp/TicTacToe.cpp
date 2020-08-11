#include <iostream>
#include <time.h>
#include <math.h>
#include <limits>

using namespace std;

#define ROW_LEN 3
#define COL_LEN 3
#define HUMAN_PLAYER_NAME "Human"
#define COMPUTER_PLAYER_NAME "Computer"

char board[ROW_LEN][COL_LEN], signs[] = {'X', 'O'}, humanSign, computerSign;
string players[] = {HUMAN_PLAYER_NAME, COMPUTER_PLAYER_NAME};

void ClearScreen()
{
    system("cls");
}

void InitializeBoard()
{
    for (int row = 0; row < ROW_LEN; ++row)
    {
        for (int col = 0; col < COL_LEN; ++col)
            board[row][col] = ' ';
    }
}

void PrintBoard()
{
    for (int row = 0; row < ROW_LEN; ++row)
    {
        if (row != 0)
            cout << "---+---+---" << endl;
        for (int col = 0; col < COL_LEN; ++col)
        {
            if (col != 0)
                cout << "|";
            if (col == COL_LEN - 1)
                cout << " " << board[row][col] << endl;
            else
                cout << " " << board[row][col] << " ";
        }
    }
}

void SetHumanInput()
{
    int row, col;
    do
    {
        printf("\n%s's turn.\nChoose an empty position by entering a pair of numbers x y where x and y denotes row and column respectively.\n"
               "x and y should lie in [%d,%d] and [%d,%d] respectively ",
               HUMAN_PLAYER_NAME, 1, ROW_LEN, 1, COL_LEN);
        cin >> row >> col;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    } while (row < 1 || row > ROW_LEN || col < 1 || col > COL_LEN || board[row - 1][col - 1] != ' ');
    board[row - 1][col - 1] = humanSign;
    PrintBoard();
}

string CheckForWinner()
{
    char winnerSign;
    for (int row = 0; row < ROW_LEN; ++row)
    {
        if (board[row][0] != ' ' && board[row][0] == board[row][1] && board[row][1] == board[row][2])
            winnerSign = board[row][0];
    }
    for (int col = 0; col < COL_LEN; ++col)
    {
        if (board[0][col] != ' ' && board[0][col] == board[1][col] && board[1][col] == board[2][col])
            winnerSign = board[0][col];
    }
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        winnerSign = board[0][0];
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        winnerSign = board[0][2];
    return winnerSign == humanSign ? HUMAN_PLAYER_NAME : winnerSign == computerSign ? COMPUTER_PLAYER_NAME : "";
}

bool IsMovesLeft()
{
    for (int row = 0; row < ROW_LEN; ++row)
    {
        for (int col = 0; col < COL_LEN; ++col)
        {
            if (board[row][col] == ' ')
                return true;
        }
    }
    return false;
}

float MiniMax(bool isComputersTurn)
{
    string winner = CheckForWinner();
    float score = winner == COMPUTER_PLAYER_NAME ? +1 : winner == HUMAN_PLAYER_NAME ? -1 : 0;

    if (score != 0 || !IsMovesLeft())
        return score;

    if (isComputersTurn)
    {
        float bestScore = -INFINITY;
        for (int currentRow = 0; currentRow < ROW_LEN; ++currentRow)
        {
            for (int col = 0; col < COL_LEN; ++col)
            {
                if (board[currentRow][col] == ' ')
                {
                    board[currentRow][col] = computerSign;
                    bestScore = max(bestScore, MiniMax(false));
                    board[currentRow][col] = ' ';
                }
            }
        }
        return bestScore;
    }
    else
    {
        float bestScore = INFINITY;
        for (int currentRow = 0; currentRow < ROW_LEN; ++currentRow)
        {
            for (int currentCol = 0; currentCol < COL_LEN; ++currentCol)
            {
                if (board[currentRow][currentCol] == ' ')
                {
                    board[currentRow][currentCol] = humanSign;
                    bestScore = min(bestScore, MiniMax(true));
                    board[currentRow][currentCol] = ' ';
                }
            }
        }
        return bestScore;
    }
}

void SetComputerBestChoice()
{
    ClearScreen();
    int rowPosition = -1, colPosition = -1;
    float bestScore = -INFINITY, currentPositionScore;
    for (int currentRow = 0; currentRow < ROW_LEN; ++currentRow)
    {
        for (int currentCol = 0; currentCol < COL_LEN; ++currentCol)
        {
            if (board[currentRow][currentCol] == ' ')
            {
                board[currentRow][currentCol] = computerSign;
                currentPositionScore = MiniMax(false);
                board[currentRow][currentCol] = ' ';
                if (currentPositionScore > bestScore)
                {
                    bestScore = currentPositionScore;
                    rowPosition = currentRow, colPosition = currentCol;
                }
            }
        }
    }
    printf("\n%s's choice : [%d,%d]\n", COMPUTER_PLAYER_NAME, rowPosition + 1, colPosition + 1);
    board[rowPosition][colPosition] = computerSign;
    PrintBoard();
}

void PlayGame()
{
    char playAgain;
    string startingPlayer, currentPlayer;
    do
    {
        string winner;
        InitializeBoard();
        startingPlayer = players[rand() % (sizeof(players) / sizeof(players[0]))];
        ClearScreen();
        cout << startingPlayer << " starts first" << endl;
        if (startingPlayer == HUMAN_PLAYER_NAME)
        {
            PrintBoard();
            humanSign = 'X', computerSign = 'O';
        }
        else
            computerSign = 'X', humanSign = 'O';
        currentPlayer = startingPlayer;

        while (winner.empty() && IsMovesLeft())
        {
            if (currentPlayer == HUMAN_PLAYER_NAME)
                SetHumanInput();
            else
                SetComputerBestChoice();
            currentPlayer = currentPlayer == HUMAN_PLAYER_NAME ? COMPUTER_PLAYER_NAME : HUMAN_PLAYER_NAME;
            winner = CheckForWinner();
        }

        if (winner.empty())
            cout << "It's a tie" << endl;
        else
            cout << "Winner is " << winner << endl;

        cout << "Enter y to play again ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
}

int main()
{
    try
    {
        srand(time(NULL));
        PlayGame();
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
    }

    return 0;
}