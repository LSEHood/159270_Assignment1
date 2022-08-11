#ifndef CHECKERS_H
#define CHECKERS_H

#include <iostream>
#include <ostream>
#endif // CHECKERS_H


// Name: Laressa Hood
// ID:  15331224

// Header file for checkers game.
// This version is for the submission at the start of week 3 - due date changed to 8th august

//---------------------------------------------------------------------
// Represents a square on the checkers board, for example A2, or B4
//---------------------------------------------------------------------
class position {
    friend class game_state;		// Allow game state to directly access private parts
private:                          // Put in your internal representation
    char x, y;                      // Think of this like coordinates, so each instance of this wil only be one coordinate e.g. A, 1
public:
    position(void);					// Default constructor
    position(char a, char b);
    void from_text(const char* str);	// Sets a position from a string
    char* to_text(void);				// Converts the internal representation to a string

    bool is_valid(void);				// Returns true if the position is valid
    void operator =(const position& p);	// Copies the contents of a position into this one

    void offset(const int x, const int y);	// Offsets a position by x in the alpha value and y in the numeric value.
};

position::position() { }

position::position(char a, char b) // Main constructor
{
    x = a;
    y = b;
}

// Sets a position from a string
void position::from_text( const char *str ) { //"A1"
    this->x = str[0];
    this->y = str[1];
}

// Converts the internal representation to a string
char* position::to_text(void) { //"A1"
//    char ch[3] = { this->x, this->y, '\0'};
//    ch[0] = 'A';
//    ch[1] = '1';
//    ch[2] = '\0';

//    return ch;
    return nullptr;
}

//The is_valid() method should check that the square is a valid square on the checker board.
//i.e. it should return true for all positions in the range A1 to D4, and false for anything outside of this.
// Returns true if the position is valid
bool position::is_valid(void) {
    if ((this->x == 'A') || (this->x == 'B') || (this->x == 'C') || (this->x == 'D')) { // in range of the board
        if ((this->y == '1') || (this->y == '2') || (this->y == '3') || (this->y == '4')) {
            return true;
        }
    }
    return false;
}

// Copies the contents of a position into this one
void position::operator =(const position& p) {
    this->x = p.x;
    this->y = p.y;
}

//The offset() method should adjust the position by the specified offsets.
//For example position A2 offset by x = 1, y = -1 should adjust the position to B1.
void position::offset(const int a, const int b) {
    this->x = this->x + a;
    this->y = this->y + b;
}

//---------------------------------------------------------------------
// Represents a move to be made
//---------------------------------------------------------------------
class move {
private:
    position from;
    position to;
public:
    move(void);							        // Default constructor
    move(position& f, position& t);	        // From two positions
    void from_text(const char* str);		    // Converts a string to a move. String must be in the form "A4-B3"
    char* to_text(void);					    // Converts the internal representation to a string
    void set_from(const position& from);		// Sets the from using a position
    void set_to(const position& to);			// Sets the to using a position
    position& get_from(void);		            // Gets either the starting
    position& get_to(void);		                // or ending position
    void get_move(void);                        //Provides a prompt to the user to enter a move. Make use of the from_text() method to convert the entered move appropriately.
};


move::move(void){
    this->from = position('x', 'y');
    this->to = position('x', 'y');
}
move::move(position& f, position& t) { //Eg. B1 to A2
    this->from = f;
    this->to = t;
}
void move::from_text(const char* str) { // Converts a string to a move. String must be in the form "A4-B3"
    this->from = position(str[0], str[1]);
    this->to = position(str[3], str[4]);
}
char* move::to_text(void) {
    char* temp = this->to.to_text();
    return temp;
}
//void move::set_from(const position& from) {}
//void move::set_to(const position& to) {}
//position& move::get_from(void) {}
//position& move::get_to(void) {}



//---------------------------------------------------------------------
// The types of pieces
//---------------------------------------------------------------------
enum piece { EMPTY, RED_PAWN, GREEN_PAWN, RED_KING, GREEN_KING, INVALID };






//Create a class representing the state of the game. For your internal representation consider
//• How would you represent the game position? Where are the pieces?
//• Whose turn is it to play?
//• Is the game over?
//• How many turns have been played?
//---------------------------------------------------------------------
// Represents the state of a game
//---------------------------------------------------------------------
class game_state {
private:
    /*char board[4][4] = { { "A1", "B1", "C1", "D1" },
                            { "A2", "B2", "C2", "D2" },
                            { "A3", "B3", "C3", "D3" },
                            { "A4", "B4", "C4", "D4" }};*/
    piece board[4][4] = { {EMPTY, GREEN_PAWN, EMPTY, GREEN_PAWN},
                            { EMPTY, EMPTY, EMPTY, EMPTY },
                            { EMPTY, EMPTY, EMPTY, EMPTY },
                            { RED_PAWN, EMPTY, RED_PAWN, EMPTY } };
    int moveCount = 0;
    bool isGameOver = false;
    bool isRedTurn = false;
    bool isGreenTurn = true; // Green will always start in my game - can change later, easier for now

public:
    game_state(void);				                    // Default constructor
    game_state(game_state& g);	                        // Copy constructor

    ~game_state();			                            // Destructor: do any tidying up required

    void new_game(void); 		                        // Initialises state for the start of a new game #TO DO

    bool is_game_over(void);	                        // Check the game status
    bool is_red_turn(void);
    bool is_green_turn(void);

    int get_move_number(void);	// How many moves have been played?
    void increment_move(void);	// Increment move number (and state)

    piece get_piece(const position& p); 	// What piece is at the specified position

    void printBoard() {
        std::cout << "************************" << std::endl;
        std::cout << "|  " << this->board[3][0] << "  |  " << this->board[3][1] << "  |  " << this->board[3][2] << "  |  " << this->board[3][3] << "  |  " << std::endl;
        std::cout << "|  " << this->board[2][0] << "  |  " << this->board[2][1] << "  |  " << this->board[2][2] << "  |  " << this->board[2][3] << "  |  " << std::endl;
        std::cout << "|  " << this->board[1][0] << "  |  " << this->board[1][1] << "  |  " << this->board[1][2] << "  |  " << this->board[1][3] << "  |  " << std::endl;
        std::cout << "|  " << this->board[0][0] << "  |  " << this->board[0][1] << "  |  " << this->board[0][2] << "  |  " << this->board[0][3] << "  |  " << std::endl;
    }

};

game_state::game_state( void ){}
game_state::game_state( game_state &g ){
    //Assign board values
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            board[row][col] = g.board[row][col];
        }
    }
    //Assigning private variables
    moveCount = g.moveCount;
    isGameOver = g.isGameOver;
    isRedTurn = g.isRedTurn;
    isGreenTurn = g.isGreenTurn;
}

game_state::~game_state(){}

void game_state::new_game( void ){
    //Reset board pieces
    /*this->board[3][0] = "Red1";
    this->board[3][2] = "Red2";
    this->board[0][3] = "Green2";
    this->board[0][1] = "Green1";*/

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            board[row][col] = EMPTY;
        }
    }
    this->board[3][0] = RED_PAWN;
    this->board[3][2] = RED_PAWN;
    this->board[0][3] = GREEN_PAWN;
    this->board[0][1] = GREEN_PAWN;

    //this->board[4][4] = {                                                 WHY DOESNT THIS WORK????
    //    {GREEN_PAWN, GREEN_PAWN, GREEN_PAWN, GREEN_PAWN},
    //    {EMPTY, EMPTY, EMPTY, EMPTY,},
    //    {EMPTY, EMPTY, EMPTY, EMPTY},
    //    { RED_PAWN, EMPTY, RED_PAWN, EMPTY} };
    this->moveCount = 0;
    this->isGameOver = false;
    this->isRedTurn = false;
    this->isGreenTurn = true; // Green will always start in my game - can change later, easier for now
}


bool game_state::is_game_over( void ){
        // if A player loses the game if they cannot make a legal move. Either their pieces are blocked, or
        //all of their pieces have been captured.
        if (moveCount >= 40) {
            this->isGameOver = true;
            isRedTurn = false;
            isGreenTurn = false;
            //std::cout << "Game over function: You've reached the maximum number of turns" << std::endl;
            return true;
        } else if (isGameOver) {
            //std::cout << "Game is over -> currently for debugging" << std::endl;
            isRedTurn = false;
            isGreenTurn = false;
            return true;
        }
        return false;
}
bool game_state::is_red_turn(void) {
    return this->isRedTurn;
}
bool game_state::is_green_turn( void ){
    return this->isGreenTurn;
}

int game_state::get_move_number( void ){
    return moveCount;
}
void game_state::increment_move( void ){
    is_game_over();

    this->moveCount += 1;

    if (isRedTurn) {
        isRedTurn = false;
        isGreenTurn = true;
    }
    else if (isGreenTurn) {
        isGreenTurn = false;
        isRedTurn = true;

    }
    else {
        //error or game is over?
    }
}

piece game_state::get_piece( const position& p ) { // represents a position e.g. A2
    int col;
    int row;
    if (p.x == 'A') { col = 0; }
    else if (p.x == 'B') { col = 1; }
    else if (p.x == 'C') { col = 2; }
    else if (p.x == 'D') { col = 3; }
    else {
        std::cout << "Error with get_piece" << std::endl;
        this->isGameOver = true; // this doesnt necessarily need to be here for the finished product, but i figured it was better to have it for now
        return INVALID;
    }

    if (p.y == '1') { row = 0; }
    else if (p.y == '2') { row = 1; }
    else if (p.y == '3') { row = 2; }
    else if (p.y == '4') { row = 3; }
    else {
        std::cout << "Error with get_piece" << std::endl;
        this->isGameOver = true;
        return INVALID;
    }

    return board[row][col];
}


