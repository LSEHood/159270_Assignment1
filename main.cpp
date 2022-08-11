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

//        while (gameState->is_game_over() == false) {
//            if (gameState->is_green_turn()) { std::cout << "Green, its your turn. "; }
//            else { std::cout << "Red, its your turn. "; }
////            std::cout << "Number of moves (before increment): " << gameState->get_move_number() << std::endl;
//            // fake move
//            gameState->increment_move();
//            std::cout << "Number of moves (after increment): " << gameState->get_move_number() << std::endl;
////            std::cout << "Is it greens turn? " << gameState->is_green_turn() << std::endl;
////            std::cout << "Is it reds turn? " << gameState->is_red_turn() << std::endl;



////            gameState->get_piece(p_to);
//            if(gameState->get_move_number() < 4){
//                p_to.offset(1, 1);
//                p_from.offset(1, 1);
//            }

//        }
        move first_move = move(p_from, p_to); // B2-A1
        std::cout << "first move should be B2-A1, actually: " << first_move.to_text() << std::endl;

        first_move.from_text("A4-B3");
        char* str = first_move.to_text();
        std::cout << "Move printed using str, should be A4-B3 : " << str << std::endl;

        position new_pos = position('A', '1');
        std::cout << "new position is, should be A1: " << new_pos.to_text() << std::endl;

        first_move.set_from(new_pos);
        std::cout << "Move after set from text: " << first_move.to_text() << std::endl;
        std::cout << "whats str doing: " << str << std::endl;

        position new_pos2 = position('C', '3');
        first_move.set_to(new_pos2);
        std::cout << "first_move after set the 'to' position, should be C3: " << first_move.to_text() << std::endl;

        position get_from = first_move.get_from();
        position get_to = first_move.get_to();



        delete[] str;

//        char* str = first_move.to_text(); // memory leak here
        gameState->printBoard();


    return 0;
}
