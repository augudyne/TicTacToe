#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>

using namespace std;

enum PLAYER{X = 0, O = 1, E = 2};		   
enum GameState{STARTED = 0, PLAYER_X_WIN = 1, PLAYER_O_WIN = 2, BOARD_IS_FULL = 3};
class Game{
private:
  char gameBoard[3][3];
  PLAYER activePlayer;
  GameState state;

public:
  Game(){
    
    //initialize values
    activePlayer = X;
    state = STARTED;
    
    for(int i = 0; i < 3; i ++){
      for(int j = 0; j< 3; j++){
	gameBoard[i][j] =' ';
      }
    }
  }

  GameState getGameState(){
    return state;
  }

  char getActivePlayer(){
    if(activePlayer == X) return 'X';
    else return 'O';
  }

  void printBoard(){
    printf("Printing the board...\n");
    for(int i = 0; i < 3; i++){
      for(int j = 0; j < 3; j++){
	printf("%c", gameBoard[i][j]);
      }
      printf("\n");
    }
  }

  bool isBoardFull(){
    for(int i = 0; i < 3; i++){
      for(int j = 0; j< 3; j++){
	if(gameBoard[i][j] != ' ') return false;
      }
    }

    return true;
  }

  PLAYER getWinner(){
    //check rows for winner
    for(int i = 0; i < 3; i++){
      if(gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][1] == gameBoard[i][2] && gameBoard[i][0] != ' ') return (gameBoard[i][0] == 'X')? X:O;
    }

    //check columns for winner
    for(int i = 0; i < 3; i++){
      if(gameBoard[0][i] == gameBoard[1][i] && gameBoard[1][i] == gameBoard[2][i] && gameBoard[0][i] != ' ') return (gameBoard[0][i] == 'X')? X:O;
    }

    //check left right diagonal for winner
    if (gameBoard[0][0] == gameBoard[1][1] && gameBoard[2][2] == gameBoard[1][1] && gameBoard[0][0] != ' ')  return (gameBoard[0][0] == 'X')? X:O;

    //check right left diagonal for winnner
    if (gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0] && gameBoard[2][0] != ' ')  return (gameBoard[0][2] == 'X')? X:O;

    //no winner
    return E;
  }
  

  bool advanceTurn(){
    //After a player has made a move, check the board for winning or full state

    //check the board for a winner
    PLAYER result = getWinner();

    switch(result){
    case X:
      state = PLAYER_X_WIN;
      return false; //a game ending state has been reached
    case O:
      state = PLAYER_O_WIN;
      return false; //a game ending state has been reached
    default:
      printf("No player has won this turn...");
      if(activePlayer == X) activePlayer = O;
      else activePlayer = X;
      //board game state updated
      //check if the board is full
      if(isBoardFull()) {
	state = BOARD_IS_FULL;
	return false;//a game ending state has been reached
      } else return true;// game can continue to the next turn
    }

  }

  bool isValidMove(int x, int y){
    //simple on-board constraints
    return (0 <= x && x <= 3 && 0 <= y && y <= 3);
  }

  
  bool tryMove(int x, int y){
    if(!isValidMove(x,y) || gameBoard[y][x] != ' ') {
      printf("Invalid Move, please try again...\n");
      return false;
    } else {
      gameBoard[y][x] = getActivePlayer();
      return true;
    }
  }

  
};

  



int main(int argc, char ** argv){
 
  printf("Welcome to Tic Tac Toe...starting game\n");
  string s;
  printf("Type [s] to start or [e] to exit\n");
  cin >> s;
  if(s.compare("s") != 0 && s.compare("e")!= 0){
    printf("Invalid Input...exiting");
    return 1;
  } else if(s == "e"){
    printf("Exiting...");
    return 0;
  }
  int x,y;
 string input;
    Game* myGame = new Game();
 while(s == "s"){
    

    myGame->printBoard();
    printf("It is %c's turn to move...\n", myGame->getActivePlayer());

    do {
     
      printf("Specify X index (top right has x = 2, y = 0): \n");
      cin >> input;
      x = atoi(input.c_str());
      
      printf("Specify Y index (bottom left has x = 0, y = 2): \n");
      cin >> input;
      y = atoi(input.c_str());

    } while(!myGame->tryMove(x, y));

    myGame->printBoard();
    if(!myGame->advanceTurn()){
      cout << "GAME ENDED\n";
      GameState state = myGame->getGameState();
      switch(state){
      case PLAYER_X_WIN:
	printf("Player X has won!!!!\n");
	return 0;
      case PLAYER_O_WIN:
	printf("Player O has won!!!!\n");
	return 0;
      case BOARD_IS_FULL:
	printf("Board is full, do you wish to [s]tart a new game or [e]xit...?");
	cin >> s;
      }
    }
  }
  printf("exiting normally....");
  return 0;
}
      
