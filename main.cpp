// Name: Laressa Hood
// ID:  15331224

#include <iostream>
#include "checkers.h"

using namespace std;

int main()
{
//    const int maxNumOfRetries = 4;
//    int retries = 0;
    game_state *gameState = new game_state();
    //gameState->new_game();
    cout << "For now, green always starts. " << endl;
    gameState->display();

    while (gameState->is_game_over() == false) {
        if (gameState->is_green_turn()) { cout << "Green, its your turn. "; }
        else { cout << "Red, its your turn. "; }

        // Making a move
        _move current_move =_move(); // initialise to nothing for now - we are gonna read in from the user

        gameState->find_moves(gameState->movesPlayed);
        cout << "Your possible moves are: ";
        for(int i = 0; i< (int)gameState->possibleMoves.size(); i++){
            cout << gameState->possibleMoves[i].to_text();
            if(i < ((int)gameState->possibleMoves.size()-1)) {// more then one move left
                cout << ", ";
            } else {
                cout << "." << endl;
            }
        }

        current_move.get_move();
        while (!gameState->check_move(current_move)) {
//            clear();
            gameState->display();
            cout << "That is an invalid move. Please try again. " << endl;
            current_move.get_move();
//            if(retries >= maxNumOfRetries) { cout << "You've reached the maximum number of retries" << endl; return 1; }
//            retries++;
        }
        //moveList = new move_list(current_move);
        gameState->movesPlayed.push_back(current_move);




        gameState->make_move(current_move);

        gameState->increment_move();

        cout << "Number of moves played: " << gameState->get_move_number() << endl;

        gameState->display();
    }
    cout << "Is it greens turn:  " << gameState->is_green_turn() << endl;
    cout << "Is it red turn:  " << gameState->is_red_turn() << endl;
    cout << "Number of moves: " << gameState->get_move_number() << endl;
    return 0;
}
