// Name: Laressa Hood
// ID:  15331224

#include <iostream>
#include "checkers.h"

//using namespace std;

int main()
{
    game_state *gameState = new game_state();
        //gameState->new_game();
        std::cout << "For now, green always starts. " << std::endl;
        position p_from = position('B', '2');
        position p_to = position('A', '1');

        while (gameState->is_game_over() == false) {
            if (gameState->is_green_turn()) { std::cout << "Green, its your turn. "; }
            else { std::cout << "Red, its your turn. "; }

            // fake move
            gameState->increment_move();
            std::cout << "Number of moves: " << gameState->get_move_number() << std::endl;
//            std::cout << "Is it greens turn? " << gameState->is_green_turn() << std::endl;
//            std::cout << "Is it reds turn? " << gameState->is_red_turn() << std::endl;

            gameState->get_piece(p_to);
            if(gameState->get_move_number() < 4){
                p_to.offset(1, 1);
            }

        }
        move first_move = move(p_from, p_to);
        first_move.from_text("A4-B3");
        char* str = first_move.to_text();
        gameState->printBoard();


    return 0;
}
