// Name: Laressa Hood
// ID:  15331224

#include <iostream>
#include "checkers.h"

using namespace std;

int main() {
    const int maxNumOfRetries = 4;
    int retries = 0;
    game_state *gameState = new game_state();
    //gameState->new_game();
    cout << "For now, green always starts. " << endl;
    gameState->display();
//    move_list * moveList = nullptr;
//    move_list * possibleMovesList = nullptr;


    while (gameState->is_game_over() == false) {
        if (gameState->is_green_turn()) { cout << "Green, its your turn. "; }
        else { cout << "Red, its your turn. "; }

        // Making a move
        _move current_move =_move(); // initialise to nothing for now - we are gonna read in from the user

        move_list * main_possibleMovesList = gameState->find_moves();

//        cout << "Your possible moves are: ";

        current_move.get_move();
        while (!gameState->check_move(current_move)) {
//            clear();
            gameState->display();
            cout << "That is an invalid move. Please try again. " << endl;
            current_move.get_move();
        }

        if (gameState->get_move_number() < 1 ) { // if no moves have been played, start the list

            gameState->moveList = new move_list(current_move);
        } else {
            gameState->moveList = gameState->moveList->add(new move_list(current_move));
        }


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