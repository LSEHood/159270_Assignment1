#include <QCoreApplication>
#include <QDebug>

// Name: Laressa Hood
// ID:  15331224

#include <iostream>
#include "checkers.h"

using namespace std;

int main()
{
    const int maxNumOfRetries = 4;
    int retries = 0;
    game_state *gameState = new game_state();
    //gameState->new_game();
    cout << "For now, green always starts. " << endl;
    gameState->display();

    while (gameState->is_game_over() == false) {
        if (gameState->is_green_turn()) { cout << "Green, its your turn. "; }
        else { cout << "Red, its your turn. "; }

        // Making a move
        _move first_move =_move(); // initialise to nothing for now - we are gonna read in from the user
        first_move.get_move();
        while (!gameState->check_move(first_move)) {
            cout << "That is an invalid move. Please try again. " << endl;
            first_move.get_move();
            if(retries >= maxNumOfRetries) { cout << "You've reached the maximum number of retries" << endl; return 1; }
            retries++;
        }

        gameState->make_move(first_move);

        gameState->increment_move();

        gameState->display();
    }
    cout << "Is it greens turn:  " << gameState->is_green_turn() << endl;
    cout << "Is it red turn:  " << gameState->is_red_turn() << endl;
    cout << "Number of moves: " << gameState->get_move_number() << endl;
    return 0;
}