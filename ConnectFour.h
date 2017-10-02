#ifndef CONNECTFOUR_H__
#define CONNECTFOUR_H__

//i used *** because i created a 2d integer array but i need to change it within functions so there is a plus 1 pointer to that
void printBoard(int *** board, int size); //prints the board
int getBoardSize(); //gets the size of the board from user
char multiplayerChoice(); //gets the user choice to play solo or multiplayer
void initializeBoard(int *** board, int size); //initializes the board with malloc
void moveAi(int *** board, int size, char tile); //if the user chooses single player computer makes move
void playGame(int *** board, int size, char soloOrMulti); //the main-ish function it calls moveai,movepiece and isgamefinished functions
void tolower(char *str); 
bool isGameFinished(int *** board, int size, int row, char tile, char player); //checks if the game finished or not
int movePiece(int *** board, int size, char tile); // simply changes the board via (un-directly) user commands 
int checkHorizontal(int *** board, int size, int row, int column, int player); // checks win at horizontal axis explained at line 230
int checkVertical(int *** board, int size, int row, int column, int player); // checks win at vertical axis explained at line 230
int checkDiagonal(int *** board, int size, int row, int column, int player); // checks win at diagonal axises explained at line 230
int isFull(int *** board, int size, char tile); // checks if the user wants to make a move to a column that is already full 
int isValid(int size, char tile); // checks if the user input for the MOVE PIECE does not exceed the board size
int tileToColumnIndex(char tile); // simply changes the user input for the column (character) to integer, i wrote this little thing to make my life easier  

#endif