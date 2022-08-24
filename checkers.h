#ifndef CHECKERS_H
#define CHECKERS_H

#include <iostream>
#include <ostream>
#endif // CHECKERS_H

#include <iostream>
#include <ostream>
#include <cctype>
#include <vector>

using namespace std;
// TODO when using record from the lecture slides, declare a move_list * first and THAT IS YOUR ENTIRE LIST
// Name: Laressa Hood
// ID:  15331224

// Header file for checkers game.

//---------------------------------------------------------------------
// Represents a square on the checkers board, for example A2, or B4
//---------------------------------------------------------------------
class position {
    friend class game_state;		// Allow game state to directly access private parts
private:
    char x, y;                      // Think of this like coordinates, so each instance of this wil only be one coordinate e.g. A, 1
public:
    position(void);					// Default constructor
    position(char a, char b);
    position(position &p);
    ~position();
    void from_text(const char* str);	// Sets a position from a string
    char* to_text(void);				// Converts the internal representation to a string

    bool is_valid(void);				// Returns true if the position is valid
    void operator =(const position& p);	// Copies the contents of a position into this one

    void offset(const int x, const int y);	// Offsets a position by x in the alpha value and y in the numeric value.
};



position::position() {
    x = '\0';
    y = '\0';
}

position::position(char a, char b) // Main constructor
{
    x = a;
    y = b;
}

position::position(position &p){
    this->x = p.x;
    this->y = p.y;
}
position::~position(){
    //delete[] positionStr;
}

// Sets a position from a string
void position::from_text( const char *str ) { //"A1"
    this->x = str[0];
    this->y = str[1];
}

// Converts the internal representation to a string
char* position::to_text(void) { //"A1"
    static char positionStr[3] = {'0', '0', '\0'};
    positionStr[0] = this->x;
    positionStr[1] = this->y;
    return positionStr;
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
class _move {
private:
    position from;
    position to;
    //char* moveStr = new char[6];
//    char moveStr [6];
public:
    _move(void);							        // Default constructor
    _move(position& f, position& t);	        // From two positions

    ~_move(); /* #TO DO SHOULD I BE HAVING DESTRUCTORS HERE OR SHOULD/CAN IT BE DONE VIA THE GAME STATE DESTRCUTOR??? */

    void from_text(const char* str);		    // Converts a string to a move. String must be in the form "A4-B3"
    char* to_text(void);					    // Converts the internal representation to a string
    void set_from(const position& from);		// Sets the from using a position
    void set_to(const position& to);			// Sets the to using a position
    position& get_from(void);		            // Gets either the starting
    position& get_to(void);		                // or ending position
    void get_move(void);                        //Provides a prompt to the user to enter a move. Make use of the from_text() method to convert the entered move appropriately.
    //  Note that for the move_list constructor, you may find it convenient to implement either:
    _move( const _move &m ); // move copy constructor or,
    void operator =(_move &m ); // move assignment operator
};


_move::_move(void){
    this->from = position('x', 'y');
    this->to = position('x', 'y');
}
_move::_move(position& f, position& t) { //Eg. B1 to A2
    this->from = f;
    this->to = t;
}
_move::~_move(){
    //delete[] moveStr;
}
void _move::from_text(const char* str) { // Converts a string to a move. String must be in the form "A4-B3"
    this->from = position(str[0], str[1]);
    this->to = position(str[3], str[4]);
}
char* _move::to_text(void) { //converts a move to a string. String must be in the form "A4-B3"
    //i have a new variable (moveStr) and i want to assign e.g. "A4-B3
    static char moveStr[6] = {'0','0', '-', '0','0','\0'};
    strncpy(moveStr, from.to_text(), 2);
    strncpy(moveStr+3, to.to_text(), 2);
    return moveStr;
}
void _move::set_from(const position& new_from) { // Sets the 'from' using a position
    this->from = new_from;
}

void _move::set_to(const position& new_to) {
    this->to = new_to;
}

position& _move::get_from(void) {
    return this->from;
}

position& _move::get_to(void) {
    return this->to;
}

void _move::get_move(void) { //Provides a prompt to the user to enter a move. Make use of the from_text() method to convert the entered move appropriately.
    static char usersMove[6] = {'0','0', '-', '0', '0', '\0' };
    cout << "Please enter a move in the form of \"A1-B2\": " << endl;
    cin >> usersMove;
//    cout << "You entered: " << usersMove << endl;
    //Convert to uppercase if not already
    for(int i=0; i<strlen(usersMove); i++){
        if(!isupper(usersMove[i])){
            usersMove[i] = toupper(usersMove[i]);
        }
    }
    //cout << "Converting to uppercase: " << usersMove << endl;
    from_text(usersMove);
}

_move::_move( const _move &m ) { // move copy constructor TODO
    this->from = m.from;
    this->to = m.to;
}
void _move::operator =(_move &m ) { // move assignment operator TODO add a draw function
    this->from = m.from; //assigning 'from' position so using the position::operator =
    this->to = m.to;
}










//---------------------------------------------------------------------
// Represents a linked list of moves
//---------------------------------------------------------------------


class move_list { // this is like a "node" class ???? #TODO
    friend class game_state;
private:
    _move m;             // The (current??) move in the list
    move_list *next;// The next entry in the list.

public:
//    move_list * remove( move_list *e );
//    void print( void );
//    void insertion_sort_height( void );

    move_list();            // default constructor for first entry
    move_list(_move &m );   // Constructor
    ~move_list();                 // Destructor – removes all items in the list.
    move_list * add( move_list* m ); // Inserts m into the start of the list, and returns the new start.

};


move_list::move_list(_move &m) {
    this->m = m;
    this->next = NULL;
}

move_list::~move_list() {
    if (next != NULL) delete next;
}

/**
 * Daniel, please help
 * @param new_item
 * @return
 */
move_list * move_list::add( move_list *new_item ) { // Inserts m into the start of the list, and returns the new start.
//    if (first == NULL)       // List is empty
//        last = new_item;       // New item will also be last
//    new_item->next = first;  // Point from new item to head
//    first = new_item;	  // Change head to new item
//    gameState->add_first()
    return new_item;
}












//---------------------------------------------------------------------
// The types of pieces
//---------------------------------------------------------------------
enum piece { EMPTY, RED_PAWN, GREEN_PAWN, RED_KING, GREEN_KING, INVALID };







//---------------------------------------------------------------------
// Represents the state of a game
//---------------------------------------------------------------------
class game_state {
private:
    //can do this, but, not ideal. 'Bad' practise because of memory issues
    piece board[4][4] = { {INVALID, GREEN_PAWN, INVALID, GREEN_PAWN},
                          { EMPTY, INVALID, EMPTY, INVALID },
                          { INVALID, EMPTY, INVALID, EMPTY },
                          { RED_PAWN, INVALID, RED_PAWN, INVALID } };
//    piece board[4][4] = { { INVALID,    EMPTY,    INVALID,  GREEN_PAWN  },            // TODO REMOVE BEFORE SUBMISSION
//                          { GREEN_PAWN, INVALID,  EMPTY ,   INVALID },
//                          { INVALID,    RED_PAWN, INVALID,  EMPTY },
//                          { RED_PAWN,   INVALID,  EMPTY ,   INVALID } };

    int redPiecesCaptured = 0;
    int greenPiecesCaptured = 0;

    int moveCount = 0;
    bool isGameOver = false;
    bool isRedTurn = false;
    bool isGreenTurn = true; // Green will always start in my game - can change later, easier for now

    move_list *first;    // First item in list
    move_list *last;     // Pointer to last item in the list
public:
    vector<_move> movesPlayed;
    vector<_move> possibleMoves;

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

    void display( void ); // Provides a simple user interface to display your game using text-based graphics on the console window.
    bool check_move(_move m );// Checks if a provided move is a legal move, and return true if it is, otherwise return false. Note that if there is no piece at the starting square, the move is not legal.
    void make_move( _move &m ); // Plays the move, and updates the game state accordingly. This includes the position of pieces on the board, the move counter, and whether or not the game is over. Don’t forget to convert pawns to kings when they reach the opposite end of the board.

//    QList<_move *> find_moves( QList<_move*> &myQList );   // This should return a linked list of possible moves that can be made from the current position (depending on which player it is to play).

    int getIntFromABC(char m) const;

    void add( move_list *new_item );
    vector<_move> find_moves(vector<_move> movesPlayed);

};

game_state::game_state( void ){
    first = NULL;   // Initialise to an empty list
    last = NULL;
    new_game();
}
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
    first = NULL;   // Initialise to an empty list
    last = NULL;
}

game_state::~game_state(){
    if (first != NULL)
        delete first;    // Delete the list
}

void game_state::new_game( void ){
    //Reset board pieces TODO
//    for (int row = 0; row < 4; row++) {
//        for (int col = 0; col < 4; col++) {
//            board[row][col] = EMPTY;
//        }
//    }
//    this->board[3][0] = RED_PAWN;
//    this->board[3][2] = RED_PAWN;
//    this->board[0][3] = GREEN_PAWN;
//    this->board[0][1] = GREEN_PAWN;

//    this->board[4][4] = { {INVALID, GREEN_PAWN, INVALID, GREEN_PAWN},
//                              { EMPTY, INVALID, EMPTY, INVALID },
//                              { INVALID, EMPTY, INVALID, EMPTY },
//                              { RED_PAWN, INVALID, RED_PAWN, INVALID } };
    this->moveCount = 0;
    this->isGameOver = false;
    this->isRedTurn = false;
    this->isGreenTurn = true; // Green will always start in my game - can change later, easier for now
}


bool game_state::is_game_over( void ){
    // if A player loses the game if they cannot make a legal move. Either their pieces are blocked, or
    //all of their pieces have been captured.
    if (moveCount > 39) {
        this->isGameOver = true;
        isRedTurn = false;
        isGreenTurn = false;
        cout << "Game over function: You've reached the maximum number of turns" << endl;
        if (greenPiecesCaptured > redPiecesCaptured) {
            cout << "Green wins!" << endl;
        } else if (greenPiecesCaptured < redPiecesCaptured){
            cout << "Red wins!" << endl;
        } else {
            cout << "It's a draw!" << endl;
        }

        return true;
    } else if (isGameOver) { // game over triggered somewhere else
        std::cout << "Game is over -> currently for debugging" << std::endl;
        isRedTurn = false;
        isGreenTurn = false;
        return true;
    } else if (redPiecesCaptured == 2) {
        cout << "All reds pieces are captured. Green Wins!" << endl;
        isGameOver = true;
        isRedTurn = false;
        isGreenTurn = false;
        return true;
    } else if (greenPiecesCaptured == 2) {
        cout << "All greens pieces are captured. Red Wins!" << endl;
        isGameOver = true;
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
    if(is_game_over()) { return; }

    this->moveCount += 1;

    if (isRedTurn && !isGameOver) {
        isRedTurn = false;
        isGreenTurn = true;
    }
    else if (isGreenTurn && !isGameOver) {
        isGreenTurn = false;
        isRedTurn = true;

    }
    else {
        //error or game is over? TODO
        cout << "error in increment_move" << endl;
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

/**
 * Display the game board
 */
void game_state::display()
{
    cout << endl;
    cout << "******************************" << endl;
    cout << "     ||  A  |  B  |  C  |  D  |" << endl;
    cout << " ------------------------------ " << endl;
    for (int row = 3; row >= 0; row--) {
        cout << "|| "<< row+1 << " ||  ";
        for (int col = 0; col < 4; col++) {
            if(board[row][col] == INVALID || board[row][col] == EMPTY) {
                cout << " " << "  |  ";
            } else if(board[row][col] == GREEN_PAWN) {
                cout << 'g' << "  |  ";
            } else if(board[row][col] == GREEN_KING) {
                cout << 'G' << "  |  ";
            } else if(board[row][col] == RED_PAWN) {
                cout << 'r' << "  |  ";
            } else if(board[row][col] == RED_KING) {
                cout << 'R' << "  |  ";
            }
        }
        cout << endl;
    }
}

/**
 * Checks if a provided move is a legal move, and return true if it is, otherwise return false.
 * Note that if there is no piece at the starting square, the move is not legal.
 **/
bool game_state::check_move(_move m) // todo A player loses the game if they cannot make a legal move. Either their pieces are blocked, or all of their pieces have been captured.
{
    //find starting position of piece on board
    int from_row = int(m.get_from().y) - 49; // "- 48" converts the char to int
    int from_col = getIntFromABC(m.get_from().x);

    //find ending position of piece on board
    int to_row = int(m.get_to().y) - 49;
    int to_col = getIntFromABC(m.get_to().x);

    if (m.get_to().is_valid() && m.get_from().is_valid()) { //move is a valid location on board
        if(get_piece(m.get_to()) == EMPTY) { // if the 'to' position isnt taken already/if there's a vacant space on the other side
            /**
             * Check if its (1) greens move, and (2) is trying to move it's own piece and (3) pawns can only go one direction
             */
            if (isGreenTurn) {
                if(this->board[from_row][from_col] == GREEN_PAWN) { // if pawn, can only go forwards
                    if(from_row < to_row) { // if 1 < 2 then green pawn is going forwards which is allowed
                        return true;
                    } else {
                        cout << "Pawns can't go backwards" << endl;
                        return false; //TODO limit number of spaces
                    }
                }

                if (this->board[from_row][from_col] == GREEN_KING) {
                    return true; //Kings can go in both directions
                }
                cout << "This doesnt seem to be your player" << endl;
                return false; // From position isn't a green character player
            }
            else if (isRedTurn) {
                if(this->board[from_row][from_col] == RED_PAWN) { // if pawn, can only go forwards
                    if(to_row < from_row) { // red pawn is going forwards
                        return true;
                    } else {
                        cout << "Pawns can't go backwards" << endl;
                        return false;
                    }
                } else if (this->board[from_row][from_col] == RED_KING) {
                    return true; //Kings can go in both directions
                }
                cout << "This doesnt seem to be your player" << endl;
                return false; // From position isn't a red player
            } else {
                cout << "You haven't selected a valid starting (or 'from') position." << endl; //TODO not necessarily true anymore?
                return false;
            }
        }
        else {
            cout << "Destination is occupied or a black square." << endl;
        }
    }
    return false;
}

void game_state::make_move(_move &m) // removed const
{
    //find starting position of piece on board
    int from_row = int(m.get_from().y) - 49; // "- 48" converts the char to int, the additional -1 make '1' into int 0
    int from_col = getIntFromABC(m.get_from().x);

    //find ending position of piece on board
    int to_row = int(m.get_to().y) - 49;
    int to_col = getIntFromABC(m.get_to().x);

    // if either columns or rows are +/- 2 ==> they are trying to take a player
    if(((from_row+2) == to_row || (from_row-2) == to_row) && ((from_col+2) == to_col || (from_col-2) == to_col)) {
        if (isGreenTurn) { //  this is to stop them being able to move an opposite piece abd make it their colour

            // The below is to calculate what piece is being jumped so we can set it to empty
            int middle_row = from_row;
            int middle_col = from_col;
            if (board[middle_row + 1][middle_col + 1] == RED_PAWN || board[middle_row + 1][middle_col + 1] == RED_KING) {
                middle_row += 1;
                middle_col += 1;
            } else if (board[middle_row - 1][middle_col + 1] == RED_PAWN || board[middle_row - 1][middle_col + 1] == RED_KING) {
                middle_row -= 1;
                middle_col += 1;
            } else if (board[middle_row - 1][middle_col - 1] == RED_PAWN || board[middle_row - 1][middle_col - 1] == RED_KING) {
                middle_row -= 1;
                middle_col -= 1;
            } else if (board[middle_row + 1][middle_col - 1] == RED_PAWN || board[middle_row + 1][middle_col - 1] == RED_KING){ // just assume its correct
                middle_row += 1;
                middle_col -= 1;
            } else {
                cout << "You cant jump an empty square." << endl; //TODO this needs to be done in the check move somehow
                //return;
            }

            // Take the player
            redPiecesCaptured++;
            board[middle_row][middle_col] = EMPTY;
            cout << "You captured a red piece!" << endl;
        } else if (isRedTurn){
            // The below is to calculate what piece is being jumped so we can set it to empty
            int middle_row = from_row;
            int middle_col = from_col;
            if (board[middle_row + 1][middle_col + 1] == GREEN_PAWN || board[middle_row + 1][middle_col + 1] == GREEN_KING) {
                middle_row += 1;
                middle_col += 1;
            } else if (board[middle_row - 1][middle_col + 1] == GREEN_PAWN || board[middle_row - 1][middle_col + 1] == GREEN_KING) {
                middle_row -= 1;
                middle_col += 1;
            } else if (board[middle_row - 1][middle_col - 1] == GREEN_PAWN || board[middle_row - 1][middle_col - 1] == GREEN_KING) {
                middle_row -= 1;
                middle_col -= 1;
            } else { // just assume its correct
                middle_row += 1;
                middle_col -= 1;
            }

            // Take the player
            greenPiecesCaptured++;
            board[middle_row][middle_col] = EMPTY;
            cout << "You captured a green piece!" << endl;
        }
    }

    //move piece from a to b - set start to empty --> set end to new location
    if (isGreenTurn) { //  this is to stop them being able to move an opposite piece abd make it their colour
        // if reaching the end of the board, turn into a king OR if already a king, keep as a king
        if(to_row == 3 || this->board[from_row][from_col] == GREEN_KING) {
            board[to_row][to_col] = GREEN_KING;
        } else {
            board[to_row][to_col] = GREEN_PAWN;
        }
        this->board[from_row][from_col] = EMPTY; // set the old position to empty

    } else if(isRedTurn){
        if(to_row == 0 || this->board[from_row][from_col] == RED_KING) {
            board[to_row][to_col] = RED_KING;
        } else {
            board[to_row][to_col] = RED_PAWN;
        }
        this->board[from_row][from_col] = EMPTY;
    } else {
        cout << "Game state is confused" << endl;
    }
}

int game_state::getIntFromABC(char m) const {
    int from_col = -1;
    switch(m) {
        case 'A':
            from_col = 0;
            break;
        case 'B':
            from_col = 1;
            break;
        case 'C':
            from_col = 2;
            break;
        case 'D':
            from_col = 3;
            break;
        default:
            cout << "error in getIntFromABC()" << endl;
    }
    return from_col;
}

//To add to the head of list:
void game_state::add( move_list *new_item ) {
    if (first == NULL)       // List is empty
        last = new_item;       // New item will also be last
    new_item->next = first;  // Point from new item to head
    first = new_item;	  // Change head to new item
}


/**
 * This should return a linked list of possible moves that can be made from the current position
 * @return  a move list
 */
 //old find moves function was here

/**
 *
 * @param movesPlayed
 * @return a list of possible moves
 */
vector<_move> game_state::find_moves(vector<_move> movesPlayed) //TODO
{
    if(!this->possibleMoves.empty()){
        possibleMoves.clear();
    }

    if(isGreenTurn)
    {
        for (int row = 0; row < 4; row++) {
            for (int col = 0; col < 4; col++) {
                if(board[row][col] == GREEN_PAWN || board[row][col] == GREEN_KING) {
                    if ( board[row+1][col-1] == EMPTY ) { //left most column's move
                        position from = position( (char)(col+65), (char)(row + 49));
                        position to = position( (char)(col -1+65), (char)(row + 1+ 49));
                        _move possible_move = _move(from, to);
                        if(check_move(possible_move)) {
                            possibleMoves.push_back(possible_move);
                        }
                    }

                    if (board[row+1][col+1] == EMPTY) {
                        position from = position( (char)(col+65), (char)(row + 49));
                        position to = position( (char)(col +1+65), (char)(row + 1+ 49));
                        _move possible_move = _move(from, to);
                        if(check_move(possible_move)) {
                            possibleMoves.push_back(possible_move);
                        }
                    }

                    /**
                     *  try find a position to jump Red
                     */
                    if ((board[row+1][col+1] == RED_PAWN || board[row+1][col+1] == RED_KING) ||
                        (board[row+1][col-1] == RED_PAWN || board[row+1][col-1] == RED_KING) ||
                        (board[row-1][col-1] == RED_PAWN || board[row-1][col-1] == RED_KING) ||
                        (board[row-1][col+1] == RED_PAWN || board[row-1][col+1] == RED_KING))
                    {
                        if ( board[row+2][col-2] == EMPTY ) { //left most column's move
                            position from = position( (char)(col+65), (char)(row + 49));
                            position to = position( (char)(col -2+65), (char)(row + 2+ 49));
                            _move possible_move = _move(from, to);
                            if(check_move(possible_move)) {
                                possibleMoves.push_back(possible_move);
                            }
                        }

                        if (board[row+2][col+2] == EMPTY) {
                            position from = position( (char)(col+65), (char)(row + 49));
                            position to = position( (char)(col +2+65), (char)(row + 2+ 49));
                            _move possible_move = _move(from, to);
                            if(check_move(possible_move)) {
                                possibleMoves.push_back(possible_move);
                            }

                        }

                        if (board[row-2][col+2] == EMPTY) {
                            position from = position( (char)(col+65), (char)(row + 49));
                            position to = position( (char)(col +2+65), (char)(row-2+ 49));
                            _move possible_move = _move(from, to);
                            if(check_move(possible_move)) {
                                possibleMoves.push_back(possible_move);
                            }

                        }

                        if (board[row-2][col-2] == EMPTY) {
                            position from = position( (char)(col+65), (char)(row + 49));
                            position to = position( (char)(col-2+65), (char)(row-2+ 49));
                            _move possible_move = _move(from, to);
                            if(check_move(possible_move)) {
                                possibleMoves.push_back(possible_move);
                            }

                        }
                    }
                }
            }
        }

    } else if (isRedTurn){

        for (int row = 3; row > 0; row--) {
            for (int col = 0; col < 4; col++) {
                if(board[row][col] == RED_PAWN || board[row][col] == RED_KING) {
                    if ( board[row-1][col-1] == EMPTY ) { //left most column's move
                        position from = position( (char)(col+65), (char)(row + 49));
                        position to = position( (char)(col -1+65), (char)(row - 1+ 49));
                        _move possible_move = _move(from, to);
                        if(check_move(possible_move)) {
                            possibleMoves.push_back(possible_move);
                        }
                    }

                    if (board[row-1][col+1] == EMPTY) {
                        position from = position( (char)(col+65), (char)(row + 49));
                        position to = position( (char)(col +1+65), (char)(row - 1+ 49));
                        _move possible_move = _move(from, to);
                        if(check_move(possible_move)) {
                            possibleMoves.push_back(possible_move);
                        }

                    }
                }
            }
        }

    } else {
        cout << "Error in find moves function." << endl;
    }


    return possibleMoves;
}

