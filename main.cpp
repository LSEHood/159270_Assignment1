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
    cout << "Green = 2" << endl << "Red = 1" << endl;
    gameState->display();

        while (gameState->is_game_over() == false) {
            if (gameState->is_green_turn()) { cout << "Green, its your turn. "; }
            else { cout << "Red, its your turn. "; }

            // Make a move
            _move first_move =_move(); // initialise to nothing for now - we are gonna read in from the user
            first_move.get_move();
            while (!gameState->check_move(first_move)) {
                cout << "That is an invalid move. Please try again. " << endl; // TODO more here, if the move is invalid a second time it'll run anyways - maybe use a loop?
                first_move.get_move();
                if(retries >= maxNumOfRetries) { return 1; }
            }
            gameState->make_move(first_move);

            gameState->increment_move();
            cout << "Number of moves (after increment): " << gameState->get_move_number() << endl;

            gameState->display();




        } //TOD ask teach about my count issue

        //Comment graveyard
//    gameState->get_piece(p_to);
//    if(gameState->get_move_number() < 4){
//        p_to.offset(1, 1);
//        p_from.offset(1, 1);
//    }
//      cout << "Is it greens turn? " << gameState->is_green_turn() << endl;
//      cout << "Is it reds turn? " << gameState->is_red_turn() << endl;
//        first_move.from_text("A4-B3");
//        char* str = first_move.to_text();
//        cout << "Move printed using str, should be A4-B3 : " << str << endl;
//
//        position new_pos = position('A', '1');
//        cout << "new position is (should be A1): " << new_pos.to_text() << endl;
//
//        first_move.set_from(new_pos);
//        cout << "Move after set from text: " << first_move.to_text() << endl;
//        cout << "whats str doing: " << str << endl;
//
//        position new_pos2 = position('C', '3');
//        first_move.set_to(new_pos2);
//        cout << "first_move after set the 'to' position, should be C3: " << first_move.to_text() << endl;
//
//        position get_from = first_move.get_from();
//        position get_to = first_move.get_to();
//
//    first_move.get_move();
//


//        char* str = first_move.to_text(); // memory leak here

    cout << "Final game print out" << endl;
    gameState->display();


    return 0;
}


//int main(int argc, char *argv[]) {
//    QCoreApplication a(argc, argv);
//    qDebug() << "Hello World";
//    return QCoreApplication::exec();
//}
