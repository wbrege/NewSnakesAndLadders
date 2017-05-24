/** @file main.cpp
    @author William Brege
    @date 05/16/2017
 
    This is a recreation of the children's game "Snakes and Ladders", with some creative additions
 */

#include <iostream>
#include "snakesAndHeaders.h"
#include <time.h>

void manualConstruct(board&);

int main() {
    srand(time(nullptr)); //Set a time based seed
    board gameBoard;
    manualConstruct(gameBoard);
    gameBoard.connectTiles();
    gameBoard.printBoard();
    
    return 0;
}

/** Manual board construction, to be replaced by a procedural generation algorithm later
 */
void manualConstruct(board& manualBoard){
    manualBoard.push_back('#');
    for(int i = 0; i < 5; ++i){
        manualBoard.push_back(' ');
    }
    manualBoard.push_back('#');
    for(int i = 0; i < 12; ++i){
        manualBoard.push_back(' ');
    }
    manualBoard.push_back('#');
    for(int i = 0; i < 8; ++i){
        manualBoard.push_back(' ');
    }
    manualBoard.push_back('$');
    for(int i = 0; i < 15; ++i){
        manualBoard.push_back(' ');
    }
    manualBoard.push_back('#');
    for(int i = 0; i < 9; ++i){
        manualBoard.push_back(' ');
    }
    manualBoard.push_back('$');
    for(int i = 0; i < 13; ++i){
        manualBoard.push_back(' ');
    }
    manualBoard.push_back('$');
    for(int i = 0; i < 10; ++i){
        manualBoard.push_back(' ');
    }
    manualBoard.push_back('$');
    for(int i = 0; i < 18; ++i){
        manualBoard.push_back(' ');
    }
}
