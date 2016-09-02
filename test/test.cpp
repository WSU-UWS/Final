#include<iostream>
#include "test.h"
#include <iomanip>
#include<cmath>
using namespace std;
typedef int* IntArrayPtr;

TwoDimension::TwoDimension()
{
    int d1, d2;
    cout << "Enter the row and column dimensions of the array:\n";
    cin >> d1 >> d2;
    row = d1;
    col = d2;
    Board = new IntArrayPtr[d1];
    for (int i = 0; i < d1; i++)
        Board[i] = new int[d2];
}

void TwoDimension::play()
{
    fillArray();
    bool gameOver = false;
    int player = 1;

    printArray();

    while (!gameOver)
    {
        gameOver = getMove(player);

        if (player == 1)
            player = -1;
        else
            player = 1;
    }
    checkWinner();
}

void TwoDimension::fillArray()
{
    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            Board[i][j] = 0;
}

void TwoDimension::printArray()
{
    int displayRow = 1;
    int displayCol = 1;
    cout << " ";
    for (int i = 0; i < col; i ++)
    {
        cout << setw(3) << displayCol;
        displayCol++;
    }
    cout << endl << endl;
    for (int i = 0; i < row; i++)
    {
        cout << displayRow << setw(3);
        displayRow++;
        for (int j = 0; j < col; j++)
            cout << setw(3) << Board[i][j];
        cout << endl;
    }
}

bool TwoDimension::getMove(int playerSymbol)
{
    int playerRow, playerCol;

    do
    {
        cout << "Player " << playerSymbol
             << " enter move: ";
        cin >> playerRow >> playerCol;
        cout << endl;
    }
    while (!isValidMove(playerRow - 1, playerCol - 1) );
    playerRow--;
    playerCol--;
    getUDLR(playerRow, playerCol, UDLR);
    int neigh = countNeigh(UDLR);
    cout << endl << "you have this amount of neigh: " << neigh << endl;
    int total = maxComb(UDLR);
    int total2 = maxComb(UDLR, neigh, playerRow, playerCol);
    if (total == 0)
        total = 1;
    else
        total = total;

    Board[playerRow][playerCol] = playerSymbol * total2;
    printArray();

    bool done = isFull();
    return done;

}

int TwoDimension::maxComb(int UDLR[4], int neigh, int playerRow, int playerCol)
{
    if (neigh == 0 || neigh == 1)
    {
        return 1;
    }
    if (neigh == 2)
    {
        int direc1 = 0;
        int direc2 = 0;
        int tempTot = 0;
        int total = 1;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (i == j)
                {
                    continue;
                }
                else
                {
                    tempTot = std::abs(UDLR[i]) + std::abs(UDLR[j]);
                    if (tempTot <=6 && tempTot > total)
                    {
                        direc1 = i;
                        direc2 = j;
                        total = tempTot;
                    }
                }
            }
            switch(direc1)
            {
            case 0:
                Board[playerRow-1][playerCol] = 0;
                break;
            case 1:
                Board[playerRow+1][playerCol] = 0;
                break;
            case 2:
                Board[playerRow][playerCol-1] = 0;
                break;
            case 3:
                Board[playerRow-1][playerCol+1] = 0;
                break;
            }
            switch(direc2)
            {
            case 0:
                Board[playerRow-1][playerCol] = 0;
                break;
            case 1:
                Board[playerRow+1][playerCol] = 0;
                break;
            case 2:
                Board[playerRow][playerCol-1] = 0;
                break;
            case 3:
                Board[playerRow-1][playerCol+1] = 0;
                break;
            }
            return total;
        }
        return maxComb(UDLR, 1, playerRow, playerCol);
    }

    if (neigh == 3)
    {
        return 300;
    }
    if (neigh == 4)
    {
        int total = UDLR[0] + UDLR[1] + UDLR[2] + UDLR[3];
        if (total <= 6)
        {
            return total;
        }
        else
        {
            maxComb(UDLR, 3, playerRow, playerCol);
        }
    }

}

int TwoDimension::countNeigh(int UDLR[4])
{
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        if (UDLR[i] != 0)
        {
            count++;
        }
    }
    return count;
}

void TwoDimension::getUDLR(int playerRow, int playerCol, int UDLR[4])
{

    int up = 0;
    int down = 0;
    int left = Board[playerRow][playerCol-1];
    int right = Board[playerRow][playerCol+1];

    if (playerCol == 0)
        left = 0;

    if (playerCol == col-1)
        right = 0;
    // Dynamic array for rows are locked by columns are more flexible hence why +/-1 possible on col
    // whilst will crash if you past row boundaries
    if (playerRow != 0)
        up = Board[playerRow-1][playerCol];

    if (playerRow != row-1)
        down = Board[playerRow+1][playerCol];


    cout << "UDLR: " << up << ", " << down << ", " << left << ", " << right << endl;
    UDLR[0] = up;
    UDLR[1] = down;
    UDLR[2] = left;
    UDLR[3] = right;
}

int TwoDimension::maxComb(int UDLR[4])
{
    int up = UDLR[0];
    int down = UDLR[1];
    int left = UDLR[2];
    int right = UDLR[3];
    int neighbours = std::abs(up) + std::abs(down) + std::abs(left) + std::abs(right);
    return neighbours;
}

bool TwoDimension::isFull()
{
    for (int i=0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (Board[i][j] == 0)
            {
                return false;
            }
        }
    }
    return true;
}

bool TwoDimension::isValidMove(int playerRow, int playerCol) const
{
    if (0 <= playerRow && playerRow <= row-1 && 0 <= playerCol && playerCol <= col-1
            && Board[playerRow][playerCol] == 0)
        return true;
    else
        return false;
}

void TwoDimension::checkWinner()
{
    int positive = 0;
    int negative = 0;
    for (int i=0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (Board[i][j] > 0)
            {
                positive++;
            }
            else
            {
                negative++;
            }
        }
    }
    if (positive > negative)
    {
        cout << endl << "Player 1 is the winner.";
    }
    else
    {
        cout << endl << "Player 2 is the winner.";
    }
}

TwoDimension::~TwoDimension()
{
    for (int i = 0; i < row; i++)
        delete[] Board[i];
    delete[] Board;
}
