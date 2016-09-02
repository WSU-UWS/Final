#include<iostream>
typedef int* IntArrayPtr;

class TwoDimension {
private:
	IntArrayPtr *Board;
	int row;
	int col;
	int UDLR[4];
public:
	TwoDimension();
	void play();
	void fillArray();
	void printArray();
	bool getMove(int playerSymbol);
	bool isValidMove(int playerRow, int playerCol) const;
	bool isFull();
	void checkWinner();
	void getUDLR(int playerRow, int playerCol, int UDLR[4]);
	int maxComb(int UDLR[4]);
	int countNeigh(int UDLR[4]);
	int maxComb(int UDLR[4], int neigh, int playerRow, int playerCol);
	~TwoDimension();
};

