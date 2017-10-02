#include <iostream>
#include <cstdlib> //rand
#include "ConnectFour.h"

using namespace std;

int main()
{
	int *** gameBoard = (int ***)malloc(sizeof(int**)); //initialize 
	int boardSize=0; //initialize
	char soloOrMulti='a'; //initialize

	cout << "\t\t\t";
	cout << "*****WELCOME TO CONNECT FOUR GAME*****"<< endl;
	cout << endl;

	boardSize = getBoardSize();
	
	initializeBoard(gameBoard, boardSize);
	
	cout << endl;
	cout << "\t\t\t";
	cout << "Here is your board: " << endl;
	printBoard(gameBoard, boardSize);
	cout << endl;
	
	soloOrMulti = multiplayerChoice();

	playGame(gameBoard, boardSize, soloOrMulti);

	return 0;
}
