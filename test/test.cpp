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
    cout << " before max comb is called";
    int total2 = maxComb(UDLR, neigh, playerRow, playerCol);
    if (total2 == 0)
        total2 = 1;
    else
        total2 = total2;

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
        int direc1 = 5;
        int direc2 = 5;
        int tempTot = 0;
        int total = 0;
        for (int i = 0; i < 4; i++)
        {
            if (UDLR[i] == 0)
                {
                    // skips element in UDLR is 0, i.e. empty
                    continue;
                }
            for (int j = 0; j < 4; j++)
            {
                if (i == j)
                {
                    // Prevents algorithm from using itself as a pair
                    continue;
                }
                if (UDLR[j] == 0)
                {
                    // skips element in UDLR is 0, i.e. empty
                    continue;
                }
                /*
                if (std::abs(UDLR[i]) == 6 || std::abs(UDLR[j]) == 6)
                {
                    cout << "before continue";
                    continue;
                    cout << "after continue";
                }
                */

                 //   if (UDLR[i] != 0 || UDLR[j] != 0)
                 //   {
                        tempTot = std::abs(UDLR[i]) + std::abs(UDLR[j]);
                        if (tempTot <=6 && tempTot > total)
                        {
                            direc1 = i;
                            direc2 = j;
                            total = tempTot;
                   //     }
                    }

            }
        }

        cout << endl << "Value of i and j " << direc1 << ", " << direc2 << endl;
        if (total == 0)
        {
            cout << "recuse to one\n";
            return maxComb(UDLR, 1, playerRow, playerCol);
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
            Board[playerRow][playerCol+1] = 0;
            break;
        }

        return total;
    }


    if (neigh == 3)
    {
        int tempTot = 0;
        int total = 0;
        int direc1 = 5;
        int direc2 = 5;
        int direc3 = 5;

        cout << "beginning of call";
        // 4 combinations, change parameter so that boundaries are not passed, will crash
        if (std::abs(UDLR[0]) + std::abs(UDLR[1]) + std::abs(UDLR[2]) > total && std::abs(UDLR[0]) + std::abs(UDLR[1]) + std::abs(UDLR[2]) <= 6)
        {
            direc1 = 0;
            direc2 = 1;
            direc3 = 2;
            total = std::abs(UDLR[0]) + std::abs(UDLR[1]) + std::abs(UDLR[2]);
        }
        if (std::abs(UDLR[0]) + std::abs(UDLR[1]) + std::abs(UDLR[3]) > total && std::abs(UDLR[0]) + std::abs(UDLR[1]) + std::abs(UDLR[3]) <= 6)
        {
            direc1 = 0;
            direc2 = 1;
            direc3 = 3;
            total = std::abs(UDLR[0]) + std::abs(UDLR[1]) + std::abs(UDLR[3]);
        }
        if (std::abs(UDLR[1]) + std::abs(UDLR[2]) + std::abs(UDLR[3]) > total && std::abs(UDLR[1]) + std::abs(UDLR[2]) + std::abs(UDLR[3]) <= 6)
        {
            direc1 = 1;
            direc2 = 2;
            direc3 = 3;
            total = std::abs(UDLR[1]) + std::abs(UDLR[2]) + std::abs(UDLR[3]);
        }
        if (std::abs(UDLR[2]) + std::abs(UDLR[3]) + std::abs(UDLR[0]) > total && std::abs(UDLR[2]) + std::abs(UDLR[3]) + std::abs(UDLR[0]) <= 6)
        {
            direc1 = 2;
            direc2 = 3;
            direc3 = 0;
            total = std::abs(UDLR[2]) + std::abs(UDLR[3]) + std::abs(UDLR[0]);
        }
        cout << "will this fix it?";
        if (playerCol == 0)
        {
            if ((std::abs(UDLR[0]) + std::abs(UDLR[1]) + std::abs(UDLR[3]) > total) && std::abs(UDLR[0]) + std::abs(UDLR[1]) + std::abs(UDLR[3]) <= 6)
            {
                total = std::abs(UDLR[0]) + std::abs(UDLR[1]) + std::abs(UDLR[3]);
                direc1 = 0;
                direc2 = 1;
                direc3 = 3;
            }
            if (std::abs(UDLR[0]) + std::abs(UDLR[1]) + std::abs(UDLR[3]) > 6)
            {
                return maxComb(UDLR, 2, playerRow, playerCol);
            }
        }

        if (playerCol == col-1)
        {
            direc1 = 0;
            direc2 = 1;
            direc3 = 2;
            if ((std::abs(UDLR[0]) + std::abs(UDLR[1]) + std::abs(UDLR[2]) > total) && std::abs(UDLR[0]) + std::abs(UDLR[1]) + std::abs(UDLR[2]) <= 6)
            {
                total = std::abs(UDLR[0]) + std::abs(UDLR[1]) + std::abs(UDLR[2]);
                direc1 = 0;
                direc2 = 1;
                direc3 = 2;
            }
            if (std::abs(UDLR[0]) + std::abs(UDLR[1]) + std::abs(UDLR[2]) > 6)
            {
                return maxComb(UDLR, 2, playerRow, playerCol);
            }
        }

        if (playerRow == 0)
        {

            cout << "HEREEEE!\n\n\n";
            if ((std::abs(UDLR[1]) + std::abs(UDLR[2]) + std::abs(UDLR[3]) > total) && std::abs(UDLR[1]) + std::abs(UDLR[2]) + std::abs(UDLR[3]) <= 6)
            {
                total = std::abs(UDLR[1]) + std::abs(UDLR[2]) + std::abs(UDLR[3]);
                direc1 = 1;
                direc2 = 2;
                direc3 = 3;
                cout << "it is running!!!";
            }
            if (std::abs(UDLR[1]) + std::abs(UDLR[2]) + std::abs(UDLR[3]) > 6)
            {
                cout << "\n\n\n !!!recursion to two\n\n\n";
                return maxComb(UDLR, 2, playerRow, playerCol);
            }
        }

        if (playerRow == row-1)
        {
            if ((std::abs(UDLR[0]) + std::abs(UDLR[2]) + std::abs(UDLR[3]) > total) && std::abs(UDLR[0]) + std::abs(UDLR[2]) + std::abs(UDLR[3]) <= 6)
            {
                total = std::abs(UDLR[0]) + std::abs(UDLR[2]) + std::abs(UDLR[3]);
                direc1 = 0;
                direc2 = 2;
                direc3 = 3;
            }
            if (std::abs(UDLR[0]) + std::abs(UDLR[2]) + std::abs(UDLR[3]) > 6)
            {
                cout << "\n\n\n !!!recursion to two\n\n\n";
                return maxComb(UDLR, 2, playerRow, playerCol);
            }
        }

        if (total == 0)
        {
            cout << "recuse two neighbours if sum too high\n";
            return maxComb(UDLR, 2, playerRow, playerCol);
        }
        else
        {

            cout << "this values " << direc1 << " " << direc2 << " " << direc3;
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
                Board[playerRow][playerCol+1] = 0;
                break;
            }
            switch(direc3)
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
                Board[playerRow][playerCol+1] = 0;
                break;
            }
            cout << "before return";
            return total;
        }
    }
    if (neigh == 4)
    {
        int total = std::abs(UDLR[0]) + std::abs(UDLR[1]) + std::abs(UDLR[2]) + std::abs(UDLR[3]);
        if (total <= 6)
        {
            cout << "doing 4 neighbours";
            Board[playerRow-1][playerCol] = 0;
            Board[playerRow+1][playerCol] = 0;
            Board[playerRow][playerCol-1] = 0;
            Board[playerRow][playerCol+1] = 0;
            return total;
        }
        else
        {
            cout << "recurse to 3 neighbours";
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
