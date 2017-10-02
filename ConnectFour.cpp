#include "ConnectFour.h"
#include <iostream>
#include <cstdlib> //rand

using namespace std;
int getBoardSize()
{
	int size;

	cout << "\t\t\t";
	cout << "Please enter board size between 4 and 20. Size should be even.: ";
	cin >> size;

	while(size<4 || size>20 || size%2!=0) //invalid size
	{
		cout<< "\t\t\t";
		cout<< "Check your input again. Board size should be between 4 and 20. Size should be even.: ";
		cin >> size;
	}
	
	return size;
}

char multiplayerChoice()
{
	char choice;
	
	cout << "\t\t\t";
	cout << "Do you want to play Multiplayer or Solo? Press M for Multiplayer, press S for Solo.: ";
	cin >> choice;

	while(choice != 'm' && choice != 'M' && choice != 's' && choice != 'S') //invalid option
	{
		cin.ignore(); 
		cout << "\t\t\t";
		cout << "Check your input again. Press M for Multiplayer, press S for Solo: ";
		cin >> choice;
	}

	return choice;
}

void printBoard(int *** board, int size)
{
	char tileName = 'A';
	int tile,i,j;
	
	cout << "\t\t\t";
	for(i=0; i<size; ++i)
	{
		cout << tileName << " ";
		tileName++;
	}
	cout << endl;
	
	for(i=0; i<size; ++i)
	{
		cout << "\t\t\t";
		for(j=0; j<size; ++j)
		{
			tile = (*board)[i][j];
			switch(tile)
			{
				case 0: 
					cout << ". ";
					break;

				case 1:
					cout << "X ";
					break;

				case 2:
					cout << "O ";
					break;
			}
		}
		cout<<"\n";
	}
}

void initializeBoard(int *** board, int size)
{
	int i,j; // no need to explain, simple malloc functions
	*board = (int **)malloc(size * sizeof(int *));
	
	for(i=0; i<size; ++i)
		(*board)[i] = (int *)malloc(size * sizeof(int));

	for(i=0; i<size; ++i) // initialize every tile to empty
	{
		for(j=0; j<size; ++j)
			(*board)[i][j] = 0;
	}
}

int movePiece(int *** board, int size, char tile, char player)
{
	int row,column;
	column = tileToColumnIndex(tile);

	for(row=0; row<size; ++row)
	{
		if((*board)[size-row-1][column] == 0 && player == 'X') // place 'player' to the first empty row in that column
		{
			(*board)[size-row-1][column] = 1;
			break;
		}
		
		else if((*board)[size-row-1][column] == 0 && player == 'O')
		{
			(*board)[size-row-1][column] = 2;
			break;
		}
	}

	printBoard(board, size);
	return(size-row-1); // i return the row to use it in check win functions - to know where exactly the last move is
}

int moveAi(int *** board, int size)
{
	int row,validMove=1;
	int randomMove;
	
	while(validMove==1)
	{
		randomMove = rand()%size+1; // rand column 
		validMove = isFull(board, size, randomMove); // if computer 'chooses' a full column, rand it again
	}

	for(row=0; row<size; ++row)
	{
		if((*board)[size-row-1][randomMove] == 0) // place computer move in empty tile and then break the loop
		{
			(*board)[size-row-1][randomMove] = 2;
			break;
		}
	}

	cout << endl;
	printBoard(board, size); // print updated board everytime
	return(size-row-1); 
}

void playGame(int *** board, int size, char soloOrMulti)
{
	int turn=0, row;
	char player, tile;
	
	while(1)
	{
		if(turn%2 == 0)
		{
			player = 'X';
			
			do
			{
				cout << endl;
				cout << "\t\t\t";
				cout << "Player X, make your move: ";
				cin >> tile;
			}while(isValid(size, tile) == 0 || isFull(board,size,tile) == 1); // check the user input
			
			row = movePiece(board, size, tile, player);
		}

		else
		{
			player = 'O';
			
			if(soloOrMulti == 'S' || soloOrMulti == 's')
			{
				cout << "\t\t\t";
				cout << "--------------------------";
				cout << endl;
				cout << "\t\t\t";
				cout << "Computer is making move: ";
				row  = moveAi(board, size);
			}
			
			else
			{
				do
				{
					cout << endl;
					cout << "\t\t\t";
					cout << "Player O, make your move: ";
					cin >> tile;
				}while(isValid(size, tile) == 0 || isFull(board,size,tile) == 1);
				
				row = movePiece(board, size, tile, player);
			}
		}
		turn++;
		
		if(isGameFinished(board, size, row, tile, player) == true)
		{
			free(*board); //free memory when game is over.
			break;
		}
	}
}

bool isGameFinished(int *** board, int size, int row, char tile, char player)
{
	int column;
	int playerInt;
	int horizontal=0,vertical=0,diagonal=0;
	
	playerInt = (player == 'X') ? 1 : 2; // to make things easier...
	column = tileToColumnIndex(tile);
	
	horizontal = checkHorizontal(board, size, row, column, playerInt);
	vertical = checkVertical(board, size, row, column, playerInt);
	diagonal = checkDiagonal(board, size, row, column, playerInt);
	
	if(horizontal == 1 || vertical == 1 || diagonal == 1)
	{
		cout << endl;
		cout << "\t\t\t";
		cout << "CONGRATZ! Player " << player << " won the game!" << endl;
		printBoard(board, size);
		return true;
	}

	return false;
}

/*

1		X . . .		DIAGONAL CHECK (for all the 4 directions.)
2		. X . .		1.X = board[0][0] && 2.X = board[1][1] && 3.X = board[2][2] && 4.X = board[3][3]
3		. . X .		so we can clearly see row index behaves row++ and column index behaves column++ every step.
4		. . . X		for other directions; row-- column--, row++ column--, row-- column++  
		
		this attitude is the nearly same with horizontal and vertical checks. 
		i am not going to comment what i did over and over again for these 3 functions below.
*/

int checkHorizontal(int *** board, int size, int row, int column, int player) //return 1 if found, 0 otherwise.
{
	int count=0, i;

	for(i=column; i>=0; --i) // left 
	{
		if((*board)[row][i]!=player) // if there is a tile that does not contain 'player' in the way, break the loop 
			break;
		if((*board)[row][i]==player)
			count++;
		if(count==4) // i don't have to loop through everything if there are 4 players in a row, break the loop
			break;
		
	}

	if(count==4) return 1; // win

	count=0; // re-initialize to use variable again
	for(i=column; i<size; ++i) // right 
	{
		if((*board)[row][i]!=player)
			break;
		if((*board)[row][i]==player)
			count++;
		if(count==4)
			break;
	}

	if(count==4) return 1;

	return 0; // no win
}

int checkVertical(int *** board, int size, int row, int column, int player) //return 1 if found, 0 otherwise.
{
	int count=0, i;

	for(i=row; i>=0; --i) // up
	{
		if((*board)[i][column]!=player)
			break;
		if((*board)[i][column]==player)
			count++;
		if(count==4)
			break;
		
	}

	if(count==4) return 1;

	count=0;
	for(i=row; i<size; ++i) // down
	{
		if((*board)[i][column]!=player)
			break;
		if((*board)[i][column]==player)
			count++;
		if(count==4)
			break;
	}

	if(count==4) return 1;

	return 0;
}

int checkDiagonal(int *** board, int size, int row, int column, int player) //return 1 if found, 0 otherwise.
{
	int count=0, i,j=column;
	
	for(i=row; i>=0; --i) // up-left diagonal
	{
		if((*board)[i][j]!=player)
			break;
		if((*board)[i][j]==player)
			count++;
		--j;
		if(count==4)
			break;
	}
	if(count==4) return 1;

	j=column;
	count=0;
	for(i=0; i<size; ++i) // down-right diagonal
	{
		if((*board)[i][j]!=player)
			break;
		if((*board)[i][j]==player)
			count++;
		++j;
		if(count==4)
			break;

	}
	if(count==4) return 1;

	j=column;
	count=0;
	for(i=row; i>=0; --i) // up-right diagonal
	{
		if((*board)[i][j]!=player)
			break;
		if((*board)[i][j]==player)
			count++;
		++j;
		if(count==4)
			break;
			
	}
	if(count==4) return 1;

	j=column;
	count=0;
	for(i=row; i<size; ++i) // down-left diagonal
	{
		if((*board)[i][j]!=player)
			break;
		if((*board)[i][j]==player)
			count++;
		--j;
		if(count==4)
			break;
			
	}
	if(count==4) return 1;

	return 0;
}

int isFull(int *** board, int size, char tile) //return 1 if full, return 0 otherwise. 
{
	int row,column,full=0;
	column = tileToColumnIndex(tile);
	
	for(row=0; row<size; row++)
	{
		if((*board)[size-row-1][column] == 0)
			break;
		
	}

	if(row>=size) // if the for loop is never broken, then there is no empty tile for this column
	{
		cout << "\t\t\t";
		cout << "The column you chose is full. Please select another column." << endl;
		full = 1;
	}

	return full;
}

int isValid(int size, char tile) //return 1 if valid, return 0 otherwise.
{
	int column,valid=1;
	column = tileToColumnIndex(tile);

	if(column>=size) // simply user input exceeds the board size
	{
		cout << "\t\t\t";
		cout << "Your move is not valid. Please select another column." << endl;
		valid = 0;
	}

	return valid;
}

int tileToColumnIndex(char tile)
{
	int column; // i don't have to explain this, do i? 

	tile = tolower(tile);
	column = (int)tile - 97;

	return column;
}

void tolower(char *str)
{
	while(*str != '\0')
	{
		if(*str >= 65 && *str <= 90)
			*str = *str+32;
		str++;
	}
}