#include <bits/stdc++.h>

using namespace std;

#define MAXSIDE 25
#define MAXMINES 99
#define MAXMOVEs 526


//global variable to store the sides and number of mines for the game board
int SIDE;
int MINES;

//to check if we are within bounds of board
bool isValid(int row , int col){

	return (row >= 0 && row < SIDE && col >= 0 && col < SIDE);

}

//function to check if the given co ordinate contains mine or not
bool isMine(int row , int col , char board[][MAXSIDE]){

	return board[row][col] == '*';

}

//function to get the move of the player
void move(int &row , int &col){

	cout<<"***Enter the row and col number of your move's cell***"<<endl;
	cin>>row>>col;

}

//function to print the board
void printBoard(char board[][MAXSIDE]){

	cout<<" \t";

	for(int i = 0 ; i < SIDE ; i++)
		cout<<i<<" ";

	cout<<endl<<endl;

	for(int i = 0 ; i < SIDE ; i++){

		cout<<i<<"\t";

		for(int j = 0 ; j < SIDE ; j++)
			cout<<board[i][j]<<" ";

		cout<<endl;

	}

}

//Function to count mines adjoining the given cell
int countMines(int row , int col , int mines[][2] , char realBoard[][MAXSIDE]){

	int count = 0;

	//utility array to store the neighbours
	int xCord[] = {-1 , -1 , 1 , 1 , -1 , 1 , 0 , 0};
	int yCord[] = {-1 , 1 , -1 , 1 , 0 , 0 , -1 , 1};

	//loop to check all the neighbours for mine
	for(int i = 0 ; i < 8 ; i++){

		//proceed if the neighbour index is valid
		if( isValid(row + xCord[i] , col + yCord[i]) )
			if(isMine(row + xCord[i] , col + yCord[i] , realBoard) == true)
				count += 1;

	}

	return count;

}

bool playMineSweeperUtil(char board[][MAXSIDE] , char realBoard[][MAXSIDE] ,
						 int mines[][2] , int row , int col , int& movesLeft){

	//If the move is valid or not
	if(board[row][col] != '-')
		return false;

	//check whether the move leads to mine
	if(realBoard[row][col] == '*'){

		board[row][col] = '*';

		for(int i = 0 ; i < MINES ; i++)
			board[ mines[i][0] ][ mines[i][1] ] = '*';

		printBoard(board);

		cout<<"You Lost"<<endl;

		return true;

	}

	//count the number of adjacent mines
	//and put it on the board
	else{

		int count = countMines(row , col , mines , realBoard);
		movesLeft -= 1;

		board[row][col] = count + '0';

		if(count == 0){


			board[row][col] = ' ';

			//utility array to store the neighbours
			int xCord[] = {-1 , -1 , 1 , 1 , -1 , 1 , 0 , 0};
			int yCord[] = {-1 , 1 , -1 , 1 , 0 , 0 , -1 , 1};

			//loop to check all the neighbours for mine
			for(int i = 0 ; i < 8 ; i++){

				//proceed if the neighbour index is valid
				if( isValid(row + xCord[i] , col + yCord[i]) )
					if( isMine(row + xCord[i] , col + yCord[i] , realBoard) == false)
						playMineSweeperUtil(board , realBoard , mines , 
							row + xCord[i] , col + yCord[i] , movesLeft);

			}			

		}

		return false;

	}

}

//A function to place mines randomly on board
void placeMines(int mines[][2] , char realBoard[][MAXSIDE]){

	bool visited[MAXSIDE * MAXSIDE];

	memset(visited , false , sizeof(visited));

	//loop till all the mines have been created
	for(int i = 0 ; i < MINES ; ){

		int randomVar = rand() % (SIDE * SIDE);
		int xCord = randomVar / SIDE;
		int yCord = randomVar % SIDE;

		//visit only if unvisited
		if(visited[randomVar] == false){

			mines[i][0] = xCord;
			mines[i][1] = yCord;

			visited[randomVar] = true;

			realBoard[xCord][yCord] = '*';

			i += 1;

		}

	}

	return;

}

void initialize(char realBoard[][MAXSIDE] , char board[][MAXSIDE]){

	//Initiate the time as null
	srand(time (NULL) );

	for(int row = 0 ; row < SIDE ; row++)
		for(int col = 0 ; col < SIDE ; col++)
			board[row][col] = realBoard[row][col] = '-';

}

void replaceMine(int row , int col , char realBoard[][MAXSIDE]){

	for(int i = 0 ; i < SIDE ; i++){

		for(int j = 0 ; j < SIDE ; j++){

			if(realBoard[i][j] == '-'){

				realBoard[i][j] = '*';
				realBoard[row][col] = '-';

				return;

			}

		}

	}

}

void playMineSweeper(){

	//to keep track of the game
	bool gameOver = false;

	char realBoard[MAXSIDE][MAXSIDE] , board[MAXSIDE][MAXSIDE];

	int mines[MAXMINES][2];

	int movesLeft = SIDE * SIDE - MINES;

	//initialize both boards
	initialize(realBoard , board);

	//place mines on board
	placeMines(mines , realBoard);

	//to keep track of moves played
	int currentMoveIndex = 0;

	while(gameOver == false){

		cout<<"Current board"<<endl;
		printBoard(board);

		int row , col;
		move(row , col);

		//make sure the very first move is always safe
		if(currentMoveIndex == 0){

			if( isMine(row , col , realBoard) == true )
				replaceMine(row , col , realBoard);

		}

		currentMoveIndex += 1;

		gameOver = playMineSweeperUtil(board , realBoard , mines , row , col , movesLeft);

		if(gameOver == false && movesLeft == 0){

			cout<<"You Won\n"<<endl;
			gameOver = true;

		}

	}

	return;

}

void chooseDifficulty(){

	int choice;

	cout<<"\t\tEnter your difficulty level"<<endl;
	cout<<"\t\t0. Easy"<<endl;
	cout<<"\t\t1. Medium"<<endl;
	cout<<"\t\t2. Hard\n\t\t";

	cin>>choice;

	if(choice == 0){

		SIDE = 9 , MINES = 10;

	}

	if(choice == 1){

		SIDE = 16 , MINES = 40;

	}

	if(choice == 2){

		SIDE = 24 , MINES = 99;

	}

}

int main(){

	chooseDifficulty();

	playMineSweeper();

	return 0;

}