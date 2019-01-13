typedef struct _state {
    int move;
    int status; // winning, losing, or drawing
} State;


//createstate initializes a state structure
State createstate(int move, int status); 

//returns 1 if the board is full, 0 if not
int boardfull(int b[9]);

//returns 1 if the next player is X
//returns 2 if the next player is O 
//returns 0 if board is full 
int whoplays(int b[9]); 

//returns the other player
int otherplayer(int x); 

//returns a copy of the board
int* copyboard(int b[9]);

//returns the better state given two states s1 and s2
State betterstate(State s1, State s2, int player);

//returns the best move given a board
State bestmove(int b[9]);

//prints the board
void printboard(int b[9]); 

//initializes the board to all zeroes
void initboard(int a[9]); 

//takes and checks the player input to make sure it is a valid integer between 0-9
int checkmove();

//populates the array value of the players chosen move unless it is already populated 
void playmove(int b[9], int move);

//checks the board to see if a player has won, returns the winner as 1 or 2
int checkwin(int b[9]); 
