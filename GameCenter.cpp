/*
	COP 3503 Project
	Program Name: Game Center
	Function:
		Allow the user to play Connect4, TicTacToe, or a Memory Game
	Date: 04/19/2015
*/

#include <limits>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <stack>
#include <stdio.h>
#include <string.h>

//Declare namespace and inclusions
using namespace std;

//COUNNECT FOUR DECLARATION
class ConnectFour{
	//ConnectFour member declarations
	private:
		stack<int> plays;
		int board[6][7];
		int level;
		int medDiff;
		bool continueGame;

		int getHeight(int x);
		void removeLast(int times);
		bool isPlayable(int x);
		bool getToken(int x, int y);
		void setToken(int x, int human);
		void removeToken(int x);
		int getTopToken(int x);
		void printBoard();

		bool checkWinner(int token);
		bool checkRow(int token);
		bool checkColumn(int token);
		bool checkPos(int token);
		bool checkNeg(int token);
		bool isFullBoard();
		bool askYesNo(string s);

		bool getInformation(bool);
		bool getGuide(bool);
		bool changeDifficulty(bool);

		void turns();
		bool humanMove();

		void computerMove1();
		int decidePlacement();
		bool checkThreeH();
		int humThree();
		bool checkThreeC();
		int compThree();

		void computerMove2();
		void checkSolutions(int, int*);
		int checkUpSolutions(int token, int x);
		int checkSideSolutions(int token, int xStart);
		int checkPosSolutions(int token, int xStart);
		int checkNegSolutions(int token, int xStart);
		int weighted(int);

	public:
		ConnectFour() {
			bool x = getInformation(false);
			cout << endl;
			bool z = getGuide(false);
			cout << endl;
			bool y = changeDifficulty(false);
			continueGame = true;

			while(continueGame) {
				medDiff = 0;
				while(!plays.empty()) { //reset Stack
					plays.pop();
				}
				memset(board, 0, sizeof(board));
				turns();
			}
		}
		~ConnectFour() {}

};

//Checks for three human tokens in a row
bool ConnectFour::checkThreeH(){
	bool win = false;
	for(int x = 0; x < 7; x++){
		if(isPlayable(x)){
			setToken(x , 1);
			if(checkWinner(1)){
				win = true;
			}
			removeToken(x);
		}
	}
	return win;
}

//checks the column in which a winning human token could be placed
int ConnectFour::humThree(){
	int place;
	for(int x = 0; x < 7; x++){
		if(isPlayable(x)){
			setToken(x, 1);
				if(checkWinner(1)){
					place = x;
				}
			removeToken(x);
		}
	}
	return place;
}

//checks for three computer tokens in a row
bool ConnectFour::checkThreeC(){
	bool win = false;
	for(int x = 0; x < 7; x++){
		if(isPlayable(x)){
			setToken(x , -1);
			if(checkWinner(-1)){
				win = true;
			}
			removeToken(x);
		}
	}
	return win;
}

//checks column in which a winning computer token could be placed
int ConnectFour::compThree(){
	int place;
	for(int x = 0; x < 7; x++){
		if(isPlayable(x)){
			setToken(x, -1);
			if(checkWinner(-1)){
				place = x;
			}
			removeToken(x);
		}
	}
	return place;
}

int ConnectFour::decidePlacement(){
	medDiff++;
	//allows checking for 3 in a row placement 70% of the time
	if((medDiff != 7) && (medDiff != 10) && (medDiff != 15) && (medDiff != 19)){
		if(checkThreeC() == true){
			int input2 = compThree();
			return input2;
		}
		else if(checkThreeH() == true){
			int input1 = humThree();
			return input1;
		}

	}

		int xD, xO, maxD1, maxO1, choiceO1, choiceD1;
		maxD1 = 0;
		maxO1 = 0;


		//determine immediate surrounding square potential
		for(int r = 0; r < 7; r++){
			if(isPlayable(r)){
					xD = 0;
					xO = 0;
					int x = r;
					int y = getHeight(r);

				    if( (x >= 1) && (x <= 5) && (y >= 1) && (y <= 4) ) {
						for(int s = (x-1); s <= (x+1); s++){
							int t = (y-1);
							if(board[t][s] == 1){
								xD++;
							}
							else if(board[t][s] == -1){
								xO++;
							}
						}
						for(int s = (x-1); s <= (x+1); s++){
							int t = (y+1);
							if(board[t][s] == 1){
								xD++;
							}
							else if(board[t][s] == -1){
								xO++;
							}
						}
						if(board[y][x+1] == 1){
							xD++;
						}
						else if(board[y][x+1] == -1){
							xO++;
						}
						if(board[y][x-1] == 1){
							xD++;
						}
						else if(board[y][x+1] == -1){
							xO++;
						}
						if((xD*3) > maxD1){
							maxD1 = xD;
						}

						if((xO*3) > maxO1){
							maxO1 = xO;
						}
					}

					else if((x == 0) && (y==0)){
						if(board[y][x+1] == 1){
							xD++;
						}
						else if(board[y][x+1] == -1){
							xO++;
						}
						if(board[y+1][x+1] == 1){
							xD++;
						}
						else if(board[y+1][x+1] == -1){
							xO++;
						}
						if(board[y+1][x] == 1){
							xD++;
						}
						else if(board[y+1][x] == -1){
							xO++;
						}
						if((xD*3) > maxD1){
							maxD1 = xD;
						}

						if((xO*3) > maxO1){
							maxO1 = xO;
						}
					}

					else if((x == 6) && (y == 0)){
						if(board[y][x-1] == 1){
							xD++;
						}
						else if(board[y][x-1] == -1){
							xO++;
						}
						if(board[y+1][x-1] == 1){
							xD++;
						}
						else if(board[y+1][x-1] == -1){
							xO++;
						}
						if(board[y+1][x] == 1){
							xD++;
						}
						else if(board[y+1][x] == -1){
							xO++;
						}
						if((xD*3) > maxD1){
							maxD1 = xD;
						}

						if((xO*3) > maxO1){
							maxO1 = xO;
						}
					}

					else if((x == 0) && (y == 5)){
						if(board[y][x-1] == 1){
							xD++;
						}
						else if(board[y][x-1] == -1){
							xO++;
						}
						if(board[y+1][x-1] == 1){
							xD++;
						}
						else if(board[y+1][x-1] == -1){
							xO++;
						}
						if(board[y+1][x] == 1){
							xD++;
						}
						else if(board[y+1][x] == -1){
							xO++;
						}
						if((xD*3) > maxD1){
							maxD1 = xD;
						}

						if((xO*3) > maxO1){
							maxO1 = xO;
						}
					}

					else if((x == 6) && (y == 5)){
						if(board[y][x-1] == 1){
							xD++;
						}
						else if(board[y][x-1] == -1){
							xO++;
						}
						if(board[y-1][x-1] == 1){
							xD++;
						}
						else if(board[y-1][x-1] == -1){
							xO++;
						}
						if(board[y-1][x] == 1){
							xD++;
						}
						else if(board[y-1][x] == -1){
							xO++;
						}
						if((xD*3) > maxD1){
							maxD1 = xD;
						}

						if((xO*3) > maxO1){
							maxO1 = xO;
						}
					}

					else if((x >= 1) && (x <= 5) && (y == 0)){
						if(board[y][x+1] == 1){
							xD++;
						}
						else if(board[y][x+1] == -1){
							xO++;
						}
						if(board[y][x-1] == 1){
							xD++;
						}
						else if(board[y][x+1] == -1){
							xO++;
						}
						for(int s = (x-1); s <= (x+1); s++){
							int t = (y+1);
							if(board[t][s] == 1){
								xD++;
							}
							else if(board[t][s] == -1){
								xO++;
							}
						}
						if((xD*3) > maxD1){
							maxD1 = xD;
						}

						if((xO*3) > maxO1){
							maxO1 = xO;
						}

					}

					else if((x >= 1) && (x <= 5) && (y == 5)){
						if(board[y][x+1] == 1){
							xD++;
						}
						else if(board[y][x+1] == -1){
							xO++;
						}
						if(board[y][x-1] == 1){
							xD++;
						}
						else if(board[y][x+1] == -1){
							xO++;
						}
						for(int s = (x-1); s <= (x+1); s++){
							int t = (y-1);
							if(board[t][s] == 1){
								xD++;
							}
							else if(board[t][s] == -1){
								xO++;
							}
						}
						if((xD*3) > maxD1){
							maxD1 = xD;
						}

						if((xO*3) > maxO1){
							maxO1 = xO;
						}
					}

					else if((x == 0) && (y >= 1) && (y <= 4)){
						if(board[y][x+1] == 1){
							xD++;
						}
						else if(board[y][x+1] == -1){
							xO++;
						}
						for(int s = (x); s <= (x+1); s++){
							int t = (y-1);
							if(board[t][s] == 1){
								xD++;
							}
							else if(board[t][s] == -1){
								xO++;
							}
						}
						for(int s = (x); s <= (x+1); s++){
							int t = (y+1);
							if(board[t][s] == 1){
								xD++;
							}
							else if(board[t][s] == -1){
								xO++;
							}
						}
						if((xD*3) > maxD1){
							maxD1 = xD;
						}

						if((xO*3) > maxO1){
							maxO1 = xO;
						}
					}

					else if((x == 6) && (y >= 1) && (y <= 4)){
						if(board[y][x-1] == 1){
							xD++;
						}
						else if(board[y][x-1] == -1){
							xO++;
						}
						for(int s = (x-1); s <= (x); s++){
							int t = (y-1);
							if(board[t][s] == 1){
								xD++;
							}
							else if(board[t][s] == -1){
								xO++;
							}
						}
						for(int s = (x-1); s <= (x); s++){
							int t = (y+1);
							if(board[t][s] == 1){
								xD++;
							}
							else if(board[t][s] == -1){
								xO++;
							}
						}
					}

					if((xD*2) > maxD1){
						maxD1 = xD;
						choiceD1 = r;

					}

					if((xO*2.5) > maxO1){
						maxO1 = xO;
						choiceO1 = r;
					}
				}
			}


		if((maxD1) > (maxO1)){
			return choiceD1;
		}
		else if((maxO1) > (maxD1)){
			return choiceO1;
		}
		else{
	    	srand(static_cast<unsigned int>(time(0)));
			int first = (rand() % 7);
			while(!isPlayable(first) && (first <= 6)){
				first++;
			}
			return first;
		}
}


//keeps track of turns, alternating turns, and which player goes first
void ConnectFour::turns() {
	int first = askYesNo("Do you want to make the first move (Y/N)? ") ? 1:2;
	bool playing = true;
	bool win = false;
	int token;

	do{
		//Whose turn is it?
		token = (plays.size()+first)%2 == 1 ? 1:-1;
		if(token == 1) {
			playing = humanMove();
		}
		else {
			//Choose AI to Use
			if(level == 1) { //Average
				computerMove1();
			}
			else if(level == 2) { //Hard
				computerMove2();
			}
			else {
				cout << "Invalid level";
			}
		}

		//check if someone has one
		win = checkWinner(token);
		if(win) {
			if(token == 1) {
				printBoard();
				cout << "Congratulations human. You have defeated the computer\n";
			}
			else {
				printBoard();
				cout << "Unfortunately, the computer has won\n";
			}

			if(askYesNo("Would you like to exit (Y/N)?: ")) {
				continueGame = false;
			}
			playing = false;
		}
	} while(!win && !isFullBoard() && playing);
	return;
}

//defining how a human move will work
bool ConnectFour::humanMove() {
	string question =  "Your token is designated by 'X' and the computer is 'O'\nWhere do you want to place your token (1-7)? ";
	string cFull = "You cannot move here. This column is already full. Please try again\n"+
						question;
	string input;
	bool valid = false;

	printBoard();
	cout << question;
	cin >> input;

	//pushes human token into declared spot making that spot in array unplayable
	while(!valid) {
		//Position inputs
		if(input == "1") {
			if(isPlayable(0)) {
				plays.push(0);
				setToken(0, 1);
				return true;
			}
			cout << cFull;
			valid = false;
		}
		else if(input == "2") {
			if(isPlayable(1)) {
				plays.push(1);
				setToken(1, 1);
				return true;
			}
			cout << cFull;
			valid = false;
		}
		else if(input == "3") {
			if(isPlayable(2)) {
				plays.push(2);
				setToken(2, 1);
				return true;
			}
			cout << cFull;
			valid = false;
		}
		else if(input == "4") {
			if(isPlayable(3)) {
				plays.push(3);
				setToken(3, 1);
				return true;
			}
			cout << cFull;
			valid = false;
		}
		else if(input == "5") {
			if(isPlayable(4)) {
				plays.push(4);
				setToken(4, 1);
				return true;
			}
			cout << cFull;
			valid = false;
		}
		else if(input == "6") {
			if(isPlayable(5)) {
				plays.push(5);
				setToken(5, 1);
				return true;
			}
			cout << cFull;
			valid = false;
		}
		else if(input == "7") {
			if(isPlayable(6)) {
				plays.push(6);
				setToken(6, 1);
				return true;
			}
			cout << cFull;
			valid = false;
		}

		//Command inputs
		else if(input == "-r") {
			removeLast(2);
			return true;
		}
		else if(input == "-i") {
			if(!getInformation(true)) {
				return false;
			}
			return true;
		}
		else if(input == "-g") {
			if(!getGuide(true)) {
				return false;
			}
			return true;
		}
		else if(input == "-c") {
			if(!changeDifficulty(true)) {
				return false;
			}
			return true;
		}
		else if(input == "-n") {
			return false;
		}
		else if(input == "-e") {
			continueGame = false;
			return false;
		}

		//errors
		else {
			cout << "This input is not valid. Try again!\n";
			cout << "Where do you want to place your token (1-7)?";
			valid = false;
		}
		cin >> input;
	}
	return false;
}

//method for asking yes or no questions and responses
bool ConnectFour::askYesNo(string s) {
	string input;
	cout << s;
	cin >> input;
	bool valid = false;

	while(!valid) {
		if(input == "Y" || input == "y") {
			return true;
		}
		else if(input == "N" || input == "n") {
			return false;
		}
		else {
			valid = false;
			cout << "This is not a valid input. Try again\n";
			cout << s;
			cin >> input;
		}
	}
	return false;
}

//provides the integer height of a column, meaning how many tokens are placed
int ConnectFour::getHeight(int x) {
	int height = 0;
	while(((board[height][x] == 1) || (board[height][x] == -1)) && height<6)  {
		height++;
	}
	return height;
}

//sets token for human or computer depending on who is
void ConnectFour::setToken(int x, int token) {
	int y = getHeight(x);
	if(y <= 7) {
		board[y][x] = token;
		return;
	}
	else {
		cout << "There is no more space to play" << endl;
		return;
	}
}

//checks if a column is playable (if a column is full or not)
bool ConnectFour::isPlayable(int x) {
	return getHeight(x) >= 6 ? false:true;
}

//removes a placed token (used for experimentation and algorithms)
void ConnectFour::removeToken(int x) {
	int y = getHeight(x)-1;
	if(y >= 0) {
		board[y][x] = 0;
	}
	else {
		cout << "There are no tokens in column "<< x << " to remove\n";
	}
}

//Remove the last X amount of plays.
void ConnectFour::removeLast(int times) {
	for(int x=0; x<times; x++) {
		if(!plays.empty()) {
			removeToken(plays.top());
			plays.pop();
		}
		else {
			cout << "There are no more previous moves\n";
			return;
		}
	}
	return;
}

//get the top token
int ConnectFour::getTopToken(int x) {
	int height = getHeight(x);
	if(height == 0) {
		cout << "There was an error in getTopToken()\n";
	}
	else {
		return board[height-1][x];
	}
	return 0;
}

//method for printing out entirety of the game board
void ConnectFour::printBoard() {
	string line = "";
	line += "\n  1    2    3    4    5    6    7  ";
	line += "\n-----------------------------------\n";
	for(int y=5; y>=0; y--) {
		for(int x=0; x<7; x++) {
			if(board[y][x] == 1) { //human
				line += "| X |";
			}
			else if(board[y][x] == -1) { //computer
				line += "| O |";
			}
			else if (board[y][x] == -0){ //empty
				line += "|   |";
			}
			else{ //errors
				line += "| e |";
			}
		}
	line += "\n-----------------------------------\n";
	}
	line += "  1    2    3    4    5    6    7  \n";
	cout << endl << line << endl;
	return;
}

//if the board is completely full and there are no more moves to be played
bool ConnectFour::isFullBoard() {
	int counter = 0;
	for(int x=0; x<7; x++) {
		if(isPlayable(x)) {
			counter++;
		}
	}
	return counter == 0 ? true:false;
}

//checks if most recently placed token induced a winner
bool ConnectFour::checkWinner(int token) {
	bool row = checkRow(token);
	bool column = checkColumn(token);
	bool pos = checkPos(token);
	bool neg = checkNeg(token);
	return row || column || pos || neg ? true:false;
}

//checks rows for winner
bool ConnectFour::checkRow(int token) {
	int counter = 0;
	for(int y=0; y<7; y++) {
		for(int x=0; x<7; x++) {
			if(board[y][x] == token) {
				counter++;
				if(counter == 4) {
					return true;
				}
				}
				else {
					counter = 0;
			}
		}
		counter = 0;
	}
		return false;
}

//checks columns for winner
bool ConnectFour::checkColumn(int token) {
	int counter = 0;
	for(int x=0; x<7; x++) {
		for(int y=0; y<7; y++) {
			if(board[y][x] == token) {
				counter++;
				if(counter == 4) {
					return true;
				}
				}
				else {
					counter = 0;
				}
			}
			counter = 0;
		}
	return false;
}

//checks positive diagonals for winner
bool ConnectFour::checkPos(int token) {
	int counter = 0;
	for(int yStrt=2; yStrt>=0; yStrt--) {
		int y = yStrt;
		int x = 0;
		while(x<7 && y<7) {
			if(board[y][x] == token) {
				counter++;
				if(counter == 4) {
					return true;
				}
				}
				else {
					counter = 0;
				}
				x++;
				y++;
			}
			counter = 0;
		}
		for(int xStrt=1; xStrt<4; xStrt++) {
			int x = xStrt;
			int y = 0;
			while(x<7 && y<7) {
				if(board[y][x] == token) {
					counter++;
					if(counter == 4) {
						return true;
					}
				}
				else {
					counter = 0;
				}
				x++;
				y++;
			}
			counter = 0;
		}
	return false;
}

//checks negative diagonals for winner
bool ConnectFour::checkNeg(int token) {
	int counter = 0;
	for(int ySet=2; ySet>=0; ySet--) {
		int y = ySet;
		int x = 6;
		while(x>=0 && y<7) {
			if(board[y][x] == token) {
				counter++;
				if(counter == 4) {
					return true;
				}
			}
			else {
				counter = 0;
			}
			x--;
			y++;
		}
		counter = 0;
	}
	counter = 0;
	for(int xSet=5; xSet>2; xSet--) {
		int x = xSet;
		int y = 0;
		while(x<7 && y<7) {
			if(board[y][x] == token) {
				counter++;
				if(counter == 4) {
					return true;
				}
			}
			else {
				counter = 0;
			}
			x--;
			y++;
		}
		counter = 0;
	}
	return false;
}

//provides information on how to play
bool ConnectFour::getInformation(bool ask) {
	cout << "\nLet ConnectFour begin!\n"
				 << "\n"
				 << "Here's how to play! \n"
				 << "-----------------------------------------------------------------------\n"
				 << "The OBJECTIVE of the game is to connect 4 in a row\n"
				 << "this can be achieved horizontally, vertically, or diagonally\n"
				 << "You will take turns with the computer, and the first player to \n"
				 << "get a 4 in a row WINS\n"
				 << "This means that you need to block your opponents moves while also trying\n"
				 << "to make moves that will give you a 4 in a row\n"
				 << "If the board is full, the game is a tie\n"
				 << "\n"
				 << "\nYou will be asked to enter 1 or 2 to select the difficulty of the computer\n"
				 << "\nYou will then be asked whether you want to make the first move\n"
				 << "\nAfter choosing, simply enter an integer from 1-7 representative\n"
				 << "of which column you will be placing a token..\n"
				 << "\n 			~GOOD LUCK~ \n"
				 << "-----------------------------------------------------------------------\n"
				 << "\n";
	if(ask) {
		return askYesNo("Would you like to resume the game (Y/N) : ");
	}
	return false;
}

//provides Command Guide for the game
bool ConnectFour::getGuide(bool ask) {
	cout << "Command Guide"
				<< "----------------------------------------------------------\n"
				<< "\nWhen asked what move you want to play, you have several options\n"
				<< "Enter an integer 1-7 to play a token\n"
				<< "Or type any of the following commands-\n"
				<< "-n: start new game\n"
				<< "-e: exit game\n"
				<< "-c: change difficulty\n"
				<< "-r: go back to your last turn\n"
				<< "\n-----------------------------------------------------------------------\n";
	if(ask) {
		return askYesNo("Would you like to resume the game (Y/N) : ");
	}
	return false;
}

//method for choosing difficulty
bool ConnectFour::changeDifficulty(bool ask) {
	string input;
	bool valid = false;

	cout << "Which level computer do you want to play?\n";
	cout << "Average: choose 1\n";
	cout << "Hard: choose 2\n";
	cout << "Choice (1 or 2): ";
	cin >> input;
	cout << "\n";

	while(!valid) {
		if(input == "1") {
			valid = true;
			this->level = 1;
		}
		else if(input ==  "2") {
			valid = true;
			this->level = 2;
		}
		else {
			std::cout << "Invalid input, please enter an integer from 1 to 3! .. : ";
			std::cin >> input;
			valid = false;
			}
	}

	if(ask) {
		return askYesNo("Would you like to resume the game (Y/N) : ");
	}
	return false;
}


//method for allowing the computer to move in the first difficulty
void ConnectFour::computerMove1() {

	int move;

	if(plays.size()==0){
		srand(static_cast<unsigned int>(time(0)));
		int first = (rand() % 7);
		cout<< "Computer move\n";
		plays.push(first);
		setToken(first, -1);
	}
	else{
		move = decidePlacement();
		cout<< "Computer move\n"
			<< "\n";
		plays.push(move);
		setToken(move, -1);
	}
	return;
}

//method for allowing the computer to move in the second difficulty
void ConnectFour::computerMove2() {
	int humSolutions[7] = {0};;
	int compSolutions[7] = {0};
	int combined[7];

	//Possible solutions created by a human token
	checkSolutions(1, humSolutions);
	//Possible solutions create by a computer token
	checkSolutions(-1, compSolutions);

	int maxIndex = 0;

	//find index that blocks most human solutions and generates most computer solutions
	for(int i=0; i<7; i++) {
		combined[i] = compSolutions[i] + humSolutions[i];
		if(isPlayable(i)) {
			if(combined[i] > combined[maxIndex]) {
				maxIndex = i;
			}
		}
	}

	//if the computer has a winning move, play it
	for(int i=0; i<7; i++) {
		if(isPlayable(i)) {
			if(compSolutions[i] > 1000) {
				plays.push(i);
				setToken(i, -1);
				return;
			}
		}
	}

	//if the human has a winning move, block it
	for(int i=0; i<7; i++) {
		if(isPlayable(i)) {
			if((humSolutions[i] > 6*plays.size()) && (plays.size() >= 2)) {
				plays.push(i);
				setToken(i, -1);
				return;
			}
		}
	}

	//play solution that blocks most human solutions and generates most computer solutions
	plays.push(maxIndex);
	setToken(maxIndex,-1);
	return;
}

//checks for all possible solutions
void  ConnectFour::checkSolutions(int token, int* solutions) {
	//iterate through all new possible moves and generate the solutions created
	for(int x=0; x<7; x++) {
		solutions[x] = 0;
		if(isPlayable(x)) {
			setToken(x, token);
			solutions[x] += checkUpSolutions(token, x);
			solutions[x] += checkSideSolutions(token, x);
			solutions[x] += checkPosSolutions(token, x);
			solutions[x] += checkNegSolutions(token, x);
			removeToken(x);
		}
	}
	return;
}

//checks for column-like solutions for token
int ConnectFour::checkUpSolutions(int token, int x) {
	int ySet = getHeight(x)-1;
	int y = ySet;
	int tokenCount = 0;
	while((token == board[y][x]) && (y>=0)) { //iterate through column
		tokenCount++;
		y--;
	}
	if((5-ySet) >= (4-tokenCount)) {
		return weighted(tokenCount);
	}
	return 0;
}

//checks for row-like solutions for token
int ConnectFour::checkSideSolutions(int token, int xStart) {
	int y = getHeight(xStart)-1;
	int counter = 0;
	int connectedSpaces = 0;
	int tokenCount = 0;
	int x = xStart;
	int sum = 0;

	//iterate through the board for row like solutions
	while((token != -1*board[y][x]) && (x>=0) && (counter < 4)) { // check
		counter++;
		while((token != -1*board[y][x]) && (x<7) && connectedSpaces<4) {
			connectedSpaces++;
			if(token == board[y][x]) {
				tokenCount++;
			}
			x++;
		}
		if(connectedSpaces == 4) {
			sum += weighted(tokenCount);
		}
		connectedSpaces = 0;
		tokenCount = 0;
		x = xStart - counter;
	}
	return sum;
}

//checks for positive diagonal solutions created by token
int ConnectFour::checkPosSolutions(int token, int xStart) {
	int yStart = getHeight(xStart)-1;
	int y = yStart;
	int counter = 0;
	int connectedSpaces = 0;
	int tokenCount = 0;
	int x = xStart;
	int sum = 0;

	//iterate through the board for positive diagonal solutions
	while((token != -1*board[y][x]) && (x>=0) && (y>=0) && (counter < 4)) {
		counter++;
		while((token != -1*board[y][x]) && (x<7) && (y<6) && connectedSpaces<4) {
			connectedSpaces++;
			if(token == board[y][x]) {
				tokenCount++;
			}
			x++;
			y++;
		}
		if(connectedSpaces == 4) {
			sum += weighted(tokenCount);
		}
		connectedSpaces = 0;
		tokenCount = 0;
		x = xStart - counter;
		y = yStart - counter;
	}
	return sum;
}

//Checks for Negative diagonal solutions create by token
int ConnectFour::checkNegSolutions(int token, int xStart) {
	int yStart = getHeight(xStart)-1;
	int y = yStart;
	int counter = 0;
	int connectedSpaces = 0;
	int tokenCount = 0;
	int x = xStart;
	int sum = 0;

	//Iterate through the board for negative diagonal solutions
	while((token != -1*board[y][x]) && (x>=0) && (y<6) && (counter < 4)) {
		counter++;
		while((token != -1*board[y][x]) && (x<7) && (y>=0) && connectedSpaces<4) {
			connectedSpaces++;
			if(token == board[y][x]) {
				tokenCount++;
			}
			x++;
			y--;
		}
		if(connectedSpaces == 4) {
			sum += weighted(tokenCount);
		}
		connectedSpaces = 0;
		tokenCount = 0;
		x = xStart - counter;
		y = yStart + counter;
	}
	return sum;
}

//returns a weighted solution/move for computer placement
int ConnectFour::weighted(int count) {
	switch(count) {
		//Solution has 1 token
		case 1:
			return 1;
		// Solution has 2 tokens
		case 2:
			return 2;
		//Solution has 3 tokens
		case 3:
			return 8;
		//Solution has 4 tokens
		case 4:
			return 100000;
		//error
		default:
			cout << "There was an error\n";
			return 0;
	}
}

//END OF CONNECT FOUR DECLARATION




//TIC TAC TOE DECLARATION

//declaring class and its members
class TicTacToe
{
private:
    void printBoard();
    int chooseLevel();
    bool CoinFlip();
    void compLogicEasy(int);
    void compLogicRandom(int);
    void compLogicHard(int);
    bool checkFin();
    char tic[3][3];
    void userMove(int);
    int ranNumber();
    void methodEasy();
    void methodRandom();
    void methodImpossible();


public:
    TicTacToe();
    bool line1;
    bool line2;
    bool line3;
    bool line4;
    bool line5;
    bool line6;
    bool line7;
    bool line8;

};

//loop to allow user to play again
TicTacToe::TicTacToe()
{
    line1 = true;
    line2 = true;
    line3 = true;
    line4 = true;
    line5 = true;
    line6 = true;
    line7 = true;
    line8 = true;
    int playAgain=0;
    while(playAgain==0)
    {
        //creating char matrix tic with ' ' as the original values
        for (int row=0; row<3; row++)
        {
            for (int column=0; column<3; column++)
            {
                tic[row][column]=' ';
            }
        }
        //Rules of the game being stated
        cout<< "Welcome to Tic Tac Toe!"<< endl;
        cout<< "Rules:"<<endl;
        cout<< "Who goes first (user or A.I.) is determined by a coin flip."<< endl;
        cout<< "The goal of this game is to get 3 X's or O's in a row ,colomn ,or diagonal."<< endl;
        cout<< "Turns will be taken in an alternating pattern starting with the winner of the coin flip."<< endl;
        cout<< "The winner of the coin flip will be X and the loser will be O.\n"<< endl;

        //calls the chooselevel function
        int x=chooseLevel();

        cout<< "Here is your board"<<endl;

        //prints board
        printBoard();

        if(x==1)
        {
            //executes easy code
            methodEasy();
        }

        else if (x==2)
        {
            //executes random(medium) code
            methodRandom();
        }

        else if (x==3)
        {
            //executes impossible code
            methodImpossible();
        }

        int endGame=0;
        //loop used to limit user inputs
        while(endGame==0)
        {
            cout<<"Would you like to play again(y/n)?"<<endl;
            char yORn;
            cin>>yORn;
            if(yORn=='y'||yORn=='Y')
            {
                playAgain=0;
                endGame=1;
            }

            else if(yORn=='n'||yORn=='N')
            {
                //exit message
                cout<<"Have a nice day!!!"<<endl;
                cout<<"/)/)"<<endl;
                cout<<"(o.o)   RABBIT!!"<<endl;
                cout<<"(VV)"<<endl;
                playAgain=1;                endGame=1;
            }

            else
            {
                //bad input message
                cout<<"Not a proper input. Please choose again."<<endl;
                endGame=0;
            }
        }
    }
}

//building board
void TicTacToe::printBoard()
{
    cout<< "  1   2  3"<<endl;
    cout<< "1 "<<tic[0][0]<<" | "<<tic[0][1]<<" | "<<tic[0][2]<<endl;
    cout<<"  ---------"<<endl;
    cout<< "2 "<<tic[1][0]<<" | "<<tic[1][1]<<" | "<<tic[1][2]<<endl;
    cout<<"  ---------"<<endl;
    cout<< "3 "<<tic[2][0]<<" | "<<tic[2][1]<<" | "<<tic[2][2]<<"\n"<<endl;
}

int TicTacToe::chooseLevel()
{
    int ret;
    int t=0;
    //loop to control user input
    while(t==0)
    {
        //list of difficulty settings
        cout<< "Select your difficulty(1/2/3)."<<endl;
        cout<< "1: Easy"<<endl;
        cout<< "2: Medium"<<endl;
        cout<< "3: Impossible"<< endl;

        char level;
        cin>>level;

        int t;

        //menu for easy difficulty
        if(level=='1')
        {
            cout<<"You have chosen easy. Are you sure (y/n)?"<<endl;
            char y;
            cin>>y;
            if(y=='y'||y=='Y')
            {
                cout<<"Ok"<<endl;
                t=1;
                ret=1;
                return ret;
            }

            else if(y=='n'||y=='N')
            {
                cout<<"Choose again"<<endl;
                t=0;
            }

            else
            {
                cout<<"Not a proper imput. Please choose again."<<endl;
                t=0;
            }
        }

        //menu for medium difficulty
        else if(level=='2')
        {
            cout<<"You have chosen medium. Are you sure (y/n)?"<<endl;
            char y;
            cin>>y;
            if(y=='y'||y=='Y')
            {
                cout<<"Ok"<<endl;
                t=1;
                ret=2;
                return ret;
            }

            else if(y=='n'||y=='N')
            {
                cout<<"Choose again"<<endl;
                t=0;
            }

            else
            {
                cout<<"Not a proper imput. Please choose again."<<endl;
                t=0;
            }
        }

        //menu for impossible difficulty
        else if(level=='3')
        {
            cout<<"You have chosen impossible. Are you sure (y/n)?"<<endl;
            char y;
            cin>>y;
            if(y=='y'||y=='Y')
            {
                cout<<"ARE YOU INSANE(y/n)?"<<endl;
                char y;
                cin>>y;

                //answers question in line 194
                if(y=='y'||y=='Y')
                {
                    cout<<"Good luck you're going to need it"<<endl;
                    t=1;
                    ret=3;
                    return ret;
                }

                else if(y=='n'||y=='N')
                {
                    cout<<"Choose again"<<endl;
                    t=0;
                }

                else
                {
                    cout<<"Not a proper imput. Please choose again."<<endl;
                    t=0;
                }

            }

            else if(y=='n'||y=='N')
            {
                cout<<"Choose again"<<endl;
                t=0;
            }

            else
            {
                cout<<"Not a proper imput. Please choose again."<<endl;
                t=0;
            }
        }

        else
        {
            cout<<"Not a proper imput. Please choose again."<<endl;
            t=0;
        }
    }
    return ret;
}

//method for coin flip
bool TicTacToe::CoinFlip()
{
    //makes random number v
    int v=ranNumber();
    int x=0;
    //loop to control user input
    while (x==0)
    {
        cout<<"Enter heads or tails (h/t)."<<endl;
        char HorT;
        cin>>HorT;

        //Algorithm for coin flip
        if(HorT=='H' || HorT=='T'||HorT=='t' ||HorT=='h')
        {
            if (HorT=='H' ||HorT=='h')
            {
                //if random number is even and h is selected
                if(v%2==0)
                {
                    cout<< "You won the coin flip! You go first and you are X."<< endl;
                    x=1;
                    return true;
                }

                else
                {
                    cout<< "You lost the coin flip :( The A.I. goes first and you are O"<< endl;
                    x=1;
                    return false;
                }
            }

            if (HorT=='t' ||HorT=='T')
            {
                //if random number is odd and t is selected
                if(v%2!=0)
                {
                    cout<< "You won the coin flip! You go first and you are X."<< endl;
                    x=1;
                    return true;
                }

                else
                {
                    cout<< "You lost the coin flip :( The A.I. goes first and you are O"<< endl;
                    x=1;
                    return false;
                }
            }
        }

        //returns to begining of loop
        else
        {
            cout<< "Not a proper input. Enter H for heads or T for tails"<< endl;
            x=0;
        }
    }
    return false;
}

bool TicTacToe::checkFin()
{
     //checks first row
    if((tic[0][0] == tic[0][1] && tic[0][1] == tic[0][2])&&(tic[0][0]=='O'||tic[0][0]=='X'))
    {
        return true;
    }
    //checks second row
    if((tic[1][0] == tic[1][1] && tic[1][1] == tic[1][2])&&(tic[1][1]=='O'||tic[1][1]=='X'))
    {
        return true;
    }
    //checks third row
    if((tic[2][0] == tic[2][1] && tic[2][1] == tic[2][2] )&&(tic[2][1]=='O'||tic[2][1]=='X'))
    {
        return true;
    }

    //checks first column
    if((tic[0][0] == tic[1][0] && tic[1][0] == tic[2][0]) &&(tic[0][0]=='O'||tic[0][0]=='X'))
    {
        return true;
    }
    //checks second column
    if((tic[0][1] == tic[1][1] && tic[1][1] == tic[2][1] )&&(tic[1][1]=='O'||tic[1][1]=='X'))
    {
        return true;
    }

    //checks third column
    if((tic[0][2] == tic[1][2] && tic[1][2] == tic[2][2] )&&(tic[1][2]=='O'||tic[1][2]=='X'))
    {
        return true;
    }
     //checks first diagonal
    if((tic[0][0] == tic[1][1] && tic[1][1] == tic[2][2] )&&(tic[0][0]=='O'||tic[0][0]=='X'))
    {
        return true;
    }

    //checks second diagonal
    if((tic[0][2] == tic[1][1] && tic[1][1] == tic[2][0]) &&(tic[1][1]=='O'||tic[1][1]=='X'))
    {
        return true;
    }

    else
    {
        return false;
    }
    return false;
}

//logic for easy algorithm
void TicTacToe::compLogicEasy(int move)
{
    if(move == 1)
    {
        //start at possition 1 1
        tic[0][0] = 'X';
    }

    else if(move == 2)
    {
         //moves to next available space throughout algorithm
        if(tic[0][0] == 'X')
        {
            tic[0][1] = 'O';
        }

        else
        {
            tic[0][0] = 'O';
        }
    }

    //odd numbered moves mean the AI is "X"
    else if(move == 3)
    {
        if(tic[0][1] == 'O')
        {
            tic[0][2] = 'X';
        }

        else
        {
            tic[0][1] = 'X';
        }
    }

    //even numbered moves mean that the AI is "O"
    else if(move == 4)
    {
        if(tic[0][1] == ' ')
        {
            tic[0][1] = 'O';
        }

        else if(tic[0][2] == ' ')
        {
            tic[0][2] = 'O';
        }

        else if(tic[1][0] == ' ')
        {
            tic[1][0] = 'O';
        }

        else if(tic[1][1] == ' ')
        {
            tic[1][1] = 'O';
        }
        else if(tic[1][2] == ' ')
        {
            tic[1][2] = 'O';
        }

        else if(tic[2][0] == ' ')
        {
            tic[2][0] = 'O';
        }

        else if(tic[2][1] == ' ')
        {
            tic[2][1] = 'O';
        }

        else
        {
            tic[2][2] = 'O';
        }
    }

    else if(move == 5)
    {
        if(tic[0][1] == ' ')
        {
            tic[0][1] = 'X';
        }

        else if(tic[0][2] == ' ')
        {
            tic[0][2] = 'X';
        }

        else if(tic[1][0] == ' ')
        {
            tic[1][0] = 'X';
        }

        else if(tic[1][1] == ' ')
        {
            tic[1][1] = 'X';
        }

        else if(tic[1][2] == ' ')
        {
            tic[1][2] = 'X';
        }

        else if(tic[2][0] == ' ')
        {
            tic[2][0] = 'X';
        }

        else if(tic[2][1] == ' ')
        {
            tic[2][1] = 'X';
        }

        else
        {
            tic[2][2] = 'X';
        }
    }

    else if(move == 6)
    {
        if(tic[0][1] == ' ')
        {
            tic[0][1] = 'O';
        }

        else if(tic[0][2] == ' ')
        {
            tic[0][2] = 'O';
        }

        else if(tic[1][0] == ' ')
        {
            tic[1][0] = 'O';
        }

        else if(tic[1][1] == ' ')
        {
            tic[1][1] = 'O';
        }

        else if(tic[1][2] == ' ')
        {
            tic[1][2] = 'O';
        }

        else if(tic[2][0] == ' ')
        {
            tic[2][0] = 'O';
        }

        else if(tic[2][1] == ' ')
        {
            tic[2][1] = 'O';
        }

        else
        {
            tic[2][2] = 'O';
        }
    }

    //options increase in number as move number increases
    else if(move == 7)
    {
        if(tic[0][1] == ' ')
        {
            tic[0][1] = 'X';
        }

        else if(tic[0][2] == ' ')
        {
            tic[0][2] = 'X';
        }

        else if(tic[1][0] == ' ')
        {
            tic[1][0] = 'X';
        }

        else if(tic[1][1] == ' ')
        {
            tic[1][1] = 'X';
        }

        else if(tic[1][2] == ' ')
        {
            tic[1][2] = 'X';
        }

        else if(tic[2][0] == ' ')
        {
            tic[2][0] = 'X';
        }

        else if(tic[2][1] == ' ')
        {
            tic[2][1] = 'X';
        }

        else
        {
            tic[2][2] = 'X';
        }
    }

    else if(move == 8)
    {
        if(tic[0][1] == ' ')
        {
            tic[0][1] = 'O';
        }

        else if(tic[0][2] == ' ')
        {
            tic[0][2] = 'O';
        }

        else if(tic[1][0] == ' ')
        {
            tic[1][0] = 'O';
        }

        else if(tic[1][1] == ' ')
        {
            tic[1][1] = 'O';
        }

        else if(tic[1][2] == ' ')
        {
            tic[1][2] = 'O';
        }

        else if(tic[2][0] == ' ')
        {
            tic[2][0] = 'O';
        }

        else if(tic[2][1] == ' ')
        {
            tic[2][1] = 'O';
        }

        else
        {
            tic[2][2] = 'O';
        }
    }

    else
    {
        if(tic[0][1] == ' ')
        {
            tic[0][1] = 'X';
        }

        else if(tic[0][2] == ' ')
        {
            tic[0][2] = 'X';
        }

        else if(tic[1][0] == ' ')
        {
            tic[1][0] = 'X';
        }

        else if(tic[1][1] == ' ')
        {
            tic[1][1] = 'X';
        }

        else if(tic[1][2] == ' ')
        {
            tic[1][2] = 'X';
        }

        else if(tic[2][0] == ' ')
        {
            tic[2][0] = 'X';
        }

        else if(tic[2][1] == ' ')
        {
            tic[2][1] = 'X';
        }

        else
        {
            tic[2][2] = 'X';
        }
    }
}

//logic for medium(random) algorithm
void TicTacToe::compLogicRandom(int move)
{
    //case for even numbered moves
    if ((move % 2) == 0)
    {
        for(int i = 0; i < 1; )
        {
            int x = 0;
            int y = 0;
            //calls for the random number function
            int m = ranNumber();
            if(m == 1)
            {
                x = 0;
                y = 0;
            }

            //each random number has a specific location
            else if(m == 2)
            {
                x = 0;
                y = 1;
            }

            else if(m == 3)
            {
                x = 0;
                y = 2;
            }

            else if(m == 4)
            {
                x = 1;
                y = 0;
            }
            else if(m == 5)
            {
                x = 1;
                y = 1;
            }

            else if(m == 6)
            {
                x = 1;
                y = 2;
            }

            else if(m == 7)
            {
                x = 2;
                y = 0;
            }
            else if(m == 8)
            {
                x = 2;
                y = 1;
            }

            else
            {
                x = 2;
                y = 2;
            }

            //checks if space is open
            if(tic[x][y] == ' ')
            {
                //because move is even, "X" is put in the open space
                tic[x][y] = 'O';
                i++;
            }
        }
    }

    else {
        //case for odd numbered moves
        for(int i = 0; i < 1; )
        {
            int x = 0;
            int y = 0;
            int m = ranNumber();
            if(m == 1)
            {
                x = 0;
                y = 0;
            }

            else if(m == 2)
            {
                x = 0;
                y = 1;
            }

            else if(m == 3)
            {
                x = 0;
                y = 2;
            }

            else if(m == 4)
            {
                x = 1;
                y = 0;
            }

            else if(m == 5)
            {
                x = 1;
                y = 1;
            }

            else if(m == 6)
            {
                x = 1;
                y = 2;
            }

            else if(m == 7)
            {
                x = 2;
                y = 0;
            }

            else if(m == 8)
            {
                x = 2;
                y = 1;
            }

            else
            {
                x = 2;
                y = 2;
            }

            //checks if space is open
            if(tic[x][y] == ' ')
            {
                //because move is even, "X" is put in the open space
                tic[x][y] = 'X';
                i++;
            }
        }
    }
}

//creates random number between 1 and 9
int TicTacToe::ranNumber()
{
    int move1 = 0;
    move1 = rand() % 9 + 1;
    return move1;
}

//logic for hard (impossible) method
void TicTacToe::compLogicHard(int move)
{
        //action for move 1
        if(move == 1)
        {
            //placing "X" here removes 4 out of 8 ways of winning for user
            tic[1][1] = 'X';
            line2 = false;
            line5 = false;
            line7 = false;
            line8 = false;
        }

        //action for move 3
        else if(move == 3)
        {
            //case 1
            if(tic[0][0] == 'O')
            {
                //move removes 2 ways of winning for user totalling 2 ways remaining
                tic[2][2] = 'X';
                line3 = false;
                line6 = false;
            }

            //case 2
            else if(tic[2][2] == 'O')
            {
                //move removes 2 ways of winning for user totalling 2 ways remaining
                tic[0][0] = 'X';
                line1 = false;
                line4 = false;
            }

            //case 3
            else if(tic[0][2] == 'O')
            {
                //move removes 2 ways of winning for user totalling 2 ways remaining
                tic[0][0] = 'X';
                line1 = false;
                line4 = false;
            }

            //case 4
            else if(tic[2][0] == 'O')
            {
                //move removes 2 ways of winning for user totalling 2 ways remaining
                tic[0][0] = 'X';
                line1 = false;
                line4 = false;
            }

            //case 5
            else if(tic[1][2] == 'O')
            {
                //move removes 2 ways of winning for user totalling 2 ways remaining
                tic[0][0] = 'X';
                line1 = false;
                line4 = false;
            }

            //case 6
            else if(tic[0][1] == 'O')
            {
                //move removes 2 ways of winning for user totalling 2 ways remaining
                tic[0][0] = 'X';
                line1 = false;
                line4 = false;
            }

            //case 7
            else if(tic[1][0] == 'O')
            {
                //move removes 2 ways of winning for user totalling 2 ways remaining
                tic[0][0] = 'X';
                line1 = false;
                line4 = false;
            }

            //case 8
            else
            {
                //move removes 2 ways of winning for user totalling 2 ways remaining
                tic[0][0] = 'X';
                line1 = false;
                line4 = false;
            }
        }

        //action for move 5
        else if(move == 5){
            if(tic[0][0] == 'O')
            {
                /*remaining code recognizes all possible cases and reacts to remove 1
                way of winning for the user*/

                if(tic[0][1] == 'O')
                {
                    tic[0][2] = 'X';
                    line1 = false;
                }

                else if(tic[0][2] == 'O')
                {
                    tic[0][1] = 'X';
                    line1 = false;
                }

                else if(tic[1][0] == 'O')
                {
                    tic[2][0] = 'X';
                    line4 = false;
                }

                else if(tic[2][0] == 'O')
                {
                    tic[1][0] = 'X';
                    line4 = false;
                }

                else if(tic[1][2] == 'O')
                {
                    tic[2][0] = 'X';
                    line4 = false;
                }

                else
                {
                    if(tic[2][1] == 'O')
                    tic[2][0] = 'X';
                    line4 = false;
                }
            }

            else
            {
                if(tic[0][2] == 'O' && tic[1][2] == 'O')
                {
                    tic[2][2] = 'X';
                    line3 = false;
                    line6 = false;
                }

                else if(tic[1][2] == 'O' && tic[2][1] == 'O')
                {
                    tic[2][2] = 'X';
                    line6 = false;
                    line3 = false;
                }
                else if(tic[1][2] == 'O' && tic[2][0] == 'O')
                {
                    tic[2][2] = 'X';
                    line6 = false;
                    line3 = false;
                }
                else if(tic[1][2] == 'O' && tic[1][0] == 'O')
                {
                    tic[2][2] = 'X';
                    line6 = false;
                    line3 = false;
                }
                else if(tic[2][1] == 'O' && tic[1][0] == 'O')
                {
                    tic[2][2] = 'X';
                    line6 = false;
                    line3 = false;
                }

                else if(tic[2][2] == 'O' && tic[1][2] == 'O')
                {
                    tic[0][2] = 'X';
                    line6 = false;
                }

                else if(tic[0][2] == 'O' && tic[2][1] == 'O')
                {
                    tic[2][2] = 'X';
                    line6 = false;
                    line3 = false;
                }
                else if(tic[0][2] == 'O' && tic[2][0] == 'O')
                {
                    tic[2][2] = 'X';
                    line6 = false;
                    line3 = false;
                }
                else if(tic[0][2] == 'O' && tic[1][0] == 'O')
                {
                    tic[2][2] = 'X';
                    line6 = false;
                    line3 = false;
                }
                else if(tic[0][1] == 'O' && tic[0][2] == 'O')
                {
                    tic[2][2] = 'X';
                    line6 = false;
                    line3 = false;
                }

                else if(tic[2][2] == 'O' && tic[2][1] == 'O')
                {
                    tic[2][0] = 'X';
                    line3 = false;
                }

                else if(tic[2][0] == 'O' && tic[2][1] == 'O')
                {
                    tic[2][2] = 'X';
                    line3 = false;
                }

                else if(tic[0][2] == 'O' && tic[2][2] == 'O')
                {
                    tic[1][2] = 'X';
                    line6 = false;
                }

                else if(tic[0][1] == 'O' && tic[2][2] == 'O')
                {
                    tic[1][2] = 'X';
                    line6 = false;
                }

                else if(tic[1][0] == 'O' && tic[2][2] == 'O'){
                    tic[1][2] = 'X';
                    line6 = false;
                }

                else if(tic[0][1] == 'O' && tic[0][2] == 'O')
                {
                    tic[1][2] = 'X';
                    line6 = false;
                }
                else if(tic[0][1] == 'O' && tic[1][2] == 'O')
                {
                    tic[2][2] = 'X';
                    line6 = false;
                }
                else if(tic[0][1] == 'O' && tic[2][1] == 'O')
                {
                    tic[2][2] = 'X';
                    line6 = false;
                }
                else if(tic[0][1] == 'O' && tic[2][0] == 'O')
                {
                    tic[2][2] = 'X';
                    line6 = false;
                    line3 = false;
                }
                else if(tic[0][1] == 'O' && tic[1][0] == 'O')
                {
                    tic[2][2] = 'X';
                    line6 = false;
                    line3 = false;
                }

                else
                {
                    if(tic[2][0] == 'O' && tic[2][2] == 'O')
                    {
                    tic[2][1] = 'X';
                    line3 = false;
                    }
                }
            }

        }

        //action for move 7
        else if(move == 7)
        {
            /*algorithm finds rows or columns that are available for user to win and
            blocks the row or column*/

            if(line1 == true)
            {
                if(tic[0][0] == ' ')
                {
                    tic[0][0] = 'X';
                }

                else if(tic[0][1] == ' ')
                {
                    tic[0][1] = 'X';
                }

                else
                {
                    tic[0][2] = 'X';
                }
            }

            else if(line3 == true)
            {
                if(tic[2][0] == ' ')
                {
                    tic[2][0] = 'X';
                }
                else if(tic[2][1] == ' ')
                {
                    tic[2][1] = 'X';
                }
                else
                {
                    tic[2][2] = 'X';
                }
            }

            else if(line4 == true)
            {
                if(tic[2][0] == ' ')
                {
                    tic[2][0] = 'X';
                }

                else if(tic[1][0] == ' ')
                {
                    tic[1][0] = 'X';
                }

                else
                {
                    tic[0][0] = 'X';
                }
            }

            else if(line6 == true)
            {
                if(tic[0][2] == ' ')
                {
                    tic[0][2] = 'X';
                }

                else if(tic[1][2] == ' '){
                    tic[1][2] = 'X';
                }

                else
                {
                    tic[2][2] = 'X';
                }
            }
        }

        //action for move 9
        else if(move == 9)
        {
            /*algorithm finds remaining space available and fills it if game has not
            ended*/

            if(tic[0][1] == ' ')
            {
                tic[0][1] = 'X';
            }

            else if(tic[0][2] == ' ')
            {
                tic[0][2] = 'X';
            }

            else if(tic[1][0] == ' ')
            {
                tic[1][0] = 'X';
            }

            else if(tic[1][1] == ' ')
            {
                tic[1][1] = 'X';
            }

            else if(tic[1][2] == ' ')
            {
                tic[1][2] = 'X';
            }

            else if(tic[2][0] == ' ')
            {
                tic[2][0] = 'X';
            }

            else if(tic[2][1] == ' ')
            {
                tic[2][1] = 'X';
            }

            else
            {
                tic[2][2] = 'X';
            }

        }


}

void TicTacToe::userMove(int move)
{
    int t=0;
    //loop to control user input
    while(t==0)
    {
        //wants a int for the row number
        cout<< "Type a row number 1 through 3"<< endl;
        int row;
        cin>>row;

        //if input not an int this code ignores it
        while(cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid input, please enter an integer from 1 to 3."<<endl;
            std::cin>> row;
        }

        //wants an int for the column number
        int column;
        cout<<"Type a column number 1 through 3"<<endl;
        cin>>column;

        //functions same as above
        while(cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid input, please enter an integer from 1 to 3."<<endl;
            std::cin>> column;
        }

        if((row<1||row>3||column<1||column>3))
        {
            cout<<"Spot already taken or does not exist. Please choose again.\n"<<endl;
            t=0;
            //if the input is not one of the desired characters, send to begining of while loop
        }

        else
        {
            //process for odd number
            if(move%2==1)
            {
                //recognizes if space is filled
                if(tic[row-1][column-1]==' ')
                {
                    tic[row-1][column-1]='X';
                    t=1;
                }
                else
                {
                    cout<<"Spot already taken or does not exist. Please choose again.\n"<<endl;
                    t=0;
                    //if spot is filled return to beginning of while loop in function
                }
            }


            //process for even number
            else
            {
                //recognizes if space is filled
                if(tic[row-1][column-1]==' ')
                {
                    tic[row-1][column-1]='O';
                    t=1;
                }
                else
                {
                    cout<<"Spot already taken or does not exist. Please choose again.\n"<<endl;
                    t=0;
                    //if spot is filled return to beginning of while loop in function
                }
            }
        }
    }
}

//gives outputs and calls functions for the easy menu and game
void TicTacToe::methodEasy()
{
    //if user wins the coinflip
    if(CoinFlip()==true)
    {
        //loop to run game
        for(int move=1; move<10;)
        {
            //user goes first because they won the coin flip
            userMove(move);
            printBoard();
            move++;
            //calls checkFin to see if user wins
            if(checkFin()==true)
            {
                cout<<"YOU WIN!!!!"<<endl;
                break;
            }

            /*if move gets iterated to 10 its an automatic tie, because there are only
            9 total moves in a game of tic tac toe*/

            else if (move==10)
            {
                cout<<"It's a tie nobody wins."<<endl;
                break;
            }

            cout<<"It's the computers turn.\n"<<endl;
            //calls the easy algorithm
            compLogicEasy(move);
            printBoard();
            move++;
            //checks if the AI has won
            if(checkFin()==true)
            {
                cout<<"You lose :'("<<endl;
                break;
            }

            //checks for a tie
            else if (move==10)
            {
                cout<<"It's a tie nobody wins."<<endl;
                break;
            }

        }
    }

    //if user loses coinflip
    else
    {
        for(int move=1; move<10;)
        {
            //AI goes first
            cout<<"It's the computer's turn.\n"<<endl;
            compLogicEasy(move);
            printBoard();
            move++;
            //checks if AI has won
            if(checkFin()==true)
            {
                cout<<"You lose :'("<<endl;
                break;
            }

            //checks for tie
            else if (move==10)
            {
                cout<<"It's a tie nobody wins."<<endl;
                break;
            }

            //user goes second
            userMove(move);
            printBoard();
            move++;
            //checks if user has won
            if(checkFin()==true)
            {
                cout<<"YOU WIN!!!!"<<endl;
                break;
            }

            //checks for tie
            else if (move==10)
            {
                cout<<"It's a tie nobody wins."<<endl;
                break;
            }

        }
    }
}

/*gives outputs and calls functions for the random(medium) menu and game
same logic as the easy method throughout*/

void TicTacToe::methodRandom()
{
    if(CoinFlip()==true)
    {
        for(int move=1; move<10;)
        {
            userMove(move);
            printBoard();
            move++;
            if(checkFin()==true)
            {
                cout<<"YOU WIN!!!!"<<endl;
                break;
            }
            else if (move==10)
            {
                cout<<"It's a tie nobody wins."<<endl;
                break;
            }

            cout<<"It's the computer's turn.\n"<<endl;
            compLogicRandom(move);
            printBoard();
            move++;
            if(checkFin()==true)
            {
                cout<<"You lose :'("<<endl;
                break;
            }

            else if (move==10)
            {
                cout<<"Its a tie nobody wins."<<endl;
                break;
            }

        }
    }
    else
    {
        for(int move=1; move<10;)
        {
            cout<<"It's the computer's turn.\n"<<endl;
            compLogicRandom(move);
            printBoard();
            move++;
            if(checkFin()==true)
            {
                cout<<"You lose :'("<<endl;
                break;
            }
            else if (move==10)
            {
                cout<<"It's a tie nobody wins."<<endl;
                break;
            }

            userMove(move);
            printBoard();
            move++;
            if(checkFin()==true)
            {
                cout<<"YOU WIN!!!!"<<endl;
                break;
            }

            else if (move==10)
            {
                cout<<"It's a tie nobody wins."<<endl;
                break;
            }
        }
    }
}

//gives outputs and calls functions for the impossible(hard) menu and game
void TicTacToe::methodImpossible()
{
    cout<<"Because you picked the impossible level, the computer will go first."<<endl;
    //AI goes first to make hard algorithm more simplistic and less buggy
    for(int move=1; move<10;)
    {
        cout<<"It's the computer's turn.\n"<<endl;
        compLogicHard(move);
        printBoard();
        move++;
        if(checkFin()==true)
        {
            cout<<"You lose :'("<<endl;
            break;
        }

        else if (move==10)
        {
            cout<<"It's a tie nobody wins."<<endl;
            break;
        }

        userMove(move);
        printBoard();
        move++;
        if(checkFin()==true)
        {
            cout<<"YOU WIN!!!!"<<endl;
            break;
        }

        else if (move==10)
        {
            cout<<"It's a tie nobody wins."<<endl;
            break;
        }
    }
}
//END OF TIC TAC TOE DECLARATION


//DECLARE MEMORY GAME
class MemMatch
{
    public:
        //constructor to create object in the main game library
        MemMatch();
        //used to initialize game and and main menu
        void runMemMatch();

    private:
        //called inside runMemMatch() and controls the game
        int play();
};

MemMatch::MemMatch()
{
   //empty constructor, will only be used to implement run()
}

int MemMatch::play()
{
    //dimensions of board/array
    int dim;
    cout<<"Enter the dimensions (2-9) of the board"<<endl;
    cin>>dim;
    //Need to make sure the input is correct, and the dimensions are in the domain

    while(std::cin.fail() || dim<2 || dim>9)
    {
            //clear input
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
            //get new input
            std::cout << "Bad input.  Please enter an integer greater than 1 and less than 10, or enter 0 to quit: "<<endl;
            std::cin >> dim;
    }

    //add one to dimensions to label board so the user can easily communicate the box they want
    //one to be printed & played with
    char board[dim + 1][dim + 1];
    //one to store hidden characters
    char hide[dim + 1][dim + 1];

    //initialize both arrays
    int temp;
    for (int i = 0; i < dim+1; ++i)
    {
        for (int j = 0; j < dim+1; ++j)
        {
            board[i][j] = 'X';
            hide[i][j] = 'X';
        }
    }

    //Fill hidden array with matches
    int numMatches = dim*dim/2;
    //create random number generated to generate pairs
    srand (time(NULL));
    //ascii value for A is 65
    int symbol = 65;
    //to add to symbol to get new ascii character
    int add;
    //if we have an odd number of spaces, one must be empty or else you can't match all entries
    if (dim%2==1)
    {
        int half = dim/2 + 1;
        hide[half][half] = '!';
    }

    //fill hidden array
    for (int i = 1; i < dim+1; ++i)
    {
        for (int j = 1; j < dim+1; ++j)
        {
            while(numMatches>=0)
            {
                if(hide[i][j]=='X')
                {
                    //26 letters so use modular arithmetic
                    add = rand()%26;
                    if (symbol+add == 88)
                    {
                        add++;
                    }
                    //cast ascii value to char
                    hide[i][j] = (char) symbol+add;
                    int a = 1+ rand()%dim;
                    int b = 1+ rand()%dim;
                    //puts the match somewhere in the array
                    while (hide[a][b] != 'X')
                    {
                        a = 1 + rand()%dim;
                        b = 1 + rand()%dim;
                    }
                    hide[a][b] = (char) symbol+add;
                    //decrease matches to keep track of how many times to iterate through loop
                    numMatches--;
                }
                break;
            }
        }
    }

    //switch ! to a blank space if it exists
    for (int i = 0; i < dim+1; ++i)
    {
        for (int j = 0; j < dim+1; ++j)
        {
            if (hide[i][j]=='!')
            {
                hide[i][j] = ' ';
                board[i][j] = ' ';
            }
        }
        cout<<endl;
    }

	//label columns and rows
	//ascii for 1
    int columnL = 49;
    //ascii for 1
    int rowL = 49;
    //create labels for rows and columns
    for (int i = 0; i <= dim; ++i)
    {
        for (int j = 0; j <=dim; ++j)
        {
            if (i == 0 && j == 0)
            {
                board[i][j] = ' ';
                hide[i][j] = ' ';
            }
            else if (i == 0)
            {
                board[i][j] = (char) rowL;
                hide[i][j] = (char) rowL;
                rowL++;
            }
            else if (j == 0)
            {
                board[i][j] = (char) columnL;
                hide[i][j] = (char) columnL;
                columnL++;
            }
        }
    }

    //Now that the board is set up, let's play!
    cout<<"Match all pairs of letters by denoting the row and column numbers of the letters you want to reveal!"<<endl;
    //keep track of users progress with matches
    int matches = 0;
    //when numMatches = matches, we know the user finished the game
    numMatches = dim*dim/2;

    //time how long it takes the user
    //begin time
    time_t now = time(0);

    //begin game
    while(matches<numMatches)
    {
        //print out the board
        for (int i = 0; i < (dim+1); ++i)
        {
            for (int j = 0; j < (dim+1); ++j)
            {
                cout<<"|| "<<board[i][j]<<" ||\t";
            }
            cout<<endl;
        }

        //Get the first index by asking for the row and column
        cout<<"Enter the row number: "<<endl;
        int rowN;
        cin>>rowN;
        //once again check user input
        while(std::cin.fail() || rowN<1 || rowN>dim)
        {
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
            std::cout << "Bad input.  Please enter a row number: "<<endl;
            std::cin >> rowN;
        }

        cout<<"Enter the column number: "<<endl;
        int colN;
        cin>>colN;
        //check user input
        while(std::cin.fail() || colN<1 || colN>dim)
        {
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
            std::cout << "Bad input.  Please enter a column number: "<<endl;
            std::cin >> colN;
        }

        //reveals entry of the hidden array
        board[rowN][colN] = hide[rowN][colN];
        for (int i = 0; i < (dim+1); ++i)
        {
            for (int j = 0; j < (dim+1); ++j)
            {
                cout<<"|| "<<board[i][j]<<" ||\t";
            }
            cout<<endl;
        }

        //Repeat the same process to find the 2nd row and column
        cout<<"Enter the 2nd row number: "<<endl;
        int row2N;
        cin>>row2N;
        //check user input
        while(std::cin.fail() || row2N<1 || row2N>dim)
        {
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
            std::cout << "Bad input.  Please enter a row number: "<<endl;
            std::cin >> row2N;
        }

        cout<<"Enter the second column number: "<<endl;
        int col2N;
        cin>>col2N;
        //check user input
        while(std::cin.fail() || col2N<1 || col2N>dim)
        {
            std::cin.clear();
            std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
            std::cout << "Bad input.  Please enter a column number: "<<endl;
            std::cin >> col2N;
        }

        //reveal 2nd hidden variable
        board[row2N][col2N] = hide[row2N][col2N];
        for (int i = 0; i < (dim+1); ++i)
        {
            for (int j = 0; j < (dim+1); ++j)
            {
                cout<<"|| "<<board[i][j]<<" ||\t";
            }
            cout<<endl;
        }

        //now test for a match!
        bool test = false;
        if (board[rowN][colN]==board[row2N][col2N])
            {
            if (board[rowN][colN]==' ' || board[row2N][col2N]==' ')
            {
                //test stays false since blank spaces aren't part of the game
            }
            else
            {
                cout<<"You found a match!"<<endl;
                //empty the board and hidden board since the user found a match
                board[rowN][colN] = ' ';
                board[row2N][col2N] = ' ';
                hide[rowN][colN] = ' ';
                hide[row2N][col2N] = ' ';
                matches++;
                test = true;
            }
        }

        //if they didn't find a match... :(
        if(test == false)
        {
            //test to see if they had chosen a blank space. If they did, give some advice.
            //if they aren't blank, change them back to X's, so they can't cheat
            cout<<"Not a match :("<<endl;
            if (board[rowN][colN]==' ' && board[row2N][col2N]==' ')
            {
                cout<<"Next time don't choose a blank space. It cannot be matched."<<endl;
            }
            else if (board[rowN][colN]==' ' && board[row2N][col2N]!=' ')
            {
                cout<<"Next time don't choose a blank space. It cannot be matched."<<endl;
                board[row2N][col2N] = 'X';
            }
            else if (board[rowN][colN]!=' ' && board[row2N][col2N]==' ')
            {
                cout<<"Next time don't choose a blank space. It cannot be matched."<<endl;
                board[rowN][colN] = 'X';
            }
            else
            {
                board[rowN][colN] = 'X';
                board[row2N][col2N] = 'X';
            }
        }

        bool cont = false;
        while (cont == false)
        {
            char input;
            cout<<"Would you like to continue (y/n)?"<<endl;
            cin >> input;

            while(std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(numeric_limits<streamsize>::max(),'\n');
                std::cout << "Bad input.  Please enter y for yes or n for no."<<endl;
                std::cin >> input;
            }

                if(input=='Y' || input=='y')
                {
                    break;
                }
                else if(input=='N' || input=='n')
                {
                    return 0;
                }
                else
                {
                    cout << "Bad input. Please enter y or n";
                    cin >> input;
                }
        }

    //enter 50 times so user can't cheat
    cout<<string(50, '\n');
    }

    //end time
    time_t then = time(0);
    //time it took them to finish the game:
    double secs = double(then - now);
    //print out they're results
    cout<<"Congratulations! You found "<<matches<<" matches in "<<secs<<" seconds!"<<endl;

    //return output required of the method
    return 0;
}

void MemMatch::runMemMatch()
{
    //Initialize game and main menu
    cout<<"Welcome to Memory Match!"<<endl;
    cout<<"Choose an option by entering the list number."<<endl;
    //kick user out if they can't follow instructions by keeping track of bad input
    int badInput = 0;
    int choice = 0;

    //keep menu in while loop so they can keep choosing options
    while (choice != 3)
        {
        //print menu
        cout<<"1. How to Play"<<endl;
        cout<<"2. Play"<<endl;
        cout<<"3. Quit"<<endl;
        cin>>choice;
        // this handles when user enters wrong data type
        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore();
            //chance choice so it goes to the default part of the switch statement
            choice = 4;
        }

        //executes choice of user
        switch (choice)
        {
            case 1:
                //Print out rules here
                cout<<"There will be a board of X's."<<endl;
                cout<<"Turn over two X's to see if they match."<<endl;
                cout<<"If they don't, they will be turned back over."<<endl;
                cout<<"Try to find all the matches as fast as possible."<<endl;
                break;
            case 2:
                play();
                break;
            case 3:
                cout << "Goodbye, play again soon!\n"<<endl;
                cout << "\n";
                break;
            default:
                //Let's user know they didn't follow instructions
                cout << "You have not entered 1, 2 or 3. Please try again."<<endl;
                //adds to the bad input count
                badInput++;
                //if the amount of bad input is too large, user is kicked out
                if (badInput >= 10)
                {
                    cout<<"You have entered a lot of wrong input, so we assume you don't want to play!"<<endl;
                    choice = 3;
                }
        }
    }
}



//DECLARE MAIN METHOD
int main(){
	bool quit = false;
	int playerin;
	//define ConnectFour class header
	//define tictactoe class header
	//define blackhack class header


	//prints out game center main menue and welcoming
	std::cout << "\nḠαмε ℭ℮ηтεя\n"
			  << "\nGreetings player, welcome to the GameCenter! Let the games begin...\n"
			  << "\n";

	//loop to keep the player in the game until they choose to quit
	while(!quit){
		std::cout << "Please choose which game you would like to play.\n";
		std::cout << "\nEnter 1 for Connect 4..\n"
				  << "Enter 2 for Tic Tac Toe..\n"
				  << "Enter 3 for Memory Check..\n"
				  << "Enter 4 to quit..\n"
				  << "\nEnter your choice now : ";
		std::cin >> playerin;
		std:: cout<< "\n";

		//ensuring correct input from user
		while(cin.fail()){
			std::cin.clear();
			std::cin.ignore();
			std::cout << "Invalid input, please enter an integer from 1 to 4! .. : ";
			std::cin >> playerin;
		}

		//checking game selection
		if(playerin == 1){
			ConnectFour gameC;
			cout << "\n";
		}
		else if(playerin == 2){
 		   TicTacToe gameT;
 			cout << "\n";
		}
		else if(playerin == 3){
			MemMatch* gameM = new MemMatch();
    		gameM->runMemMatch();
			delete gameM;
		}
		else if(playerin == 4){
			quit = true;
		}

	}

	//exit and exit greeting
	std::cout << "\nThanks for playing! We hope it was time well spent.\n"
			  << "\n";

}
