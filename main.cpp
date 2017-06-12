/** @file main.cpp
    @author William Brege
    @date 05/16/2017
 
    This is a recreation of the children's game "Snakes and Ladders", with some creative additions
 */

#include <iostream>
#include "snakesAndHeaders.h"
#include <time.h>

void manualConstruct(board&);
void proceduralGen(board&);
int rollDice();

int main() {
    srand(time(nullptr)); //Set a time based seed
    //Prepare the game board
    board gameBoard;
    //manualConstruct(gameBoard);
    proceduralGen(gameBoard);
    gameBoard.connectTiles();
    char response;
    
    std::cout << "How many people are playing (1/2)? " << std::endl;
    std::cin >> response;
    
    gameBoard.printBoard();
    
    //Prepare the players
    bool AI = true;
    player humanPlayer = gameBoard.start(); //Represented by '1' on the board
    player AIPlayer = gameBoard.start(); //Represented by '2' on the board
    
    if(response == '2'){
        AI = false;
    }
    else{
        AIPlayer.setAI(true);
    }
    
    //Begin the game!
    while(*humanPlayer != 'E' && *AIPlayer != 'E'){
        //////// HUMAN TURN ////////
        std::cout << std::endl << std::endl << "Player 1 turn!" << std::endl << "Roll the dice (y/n)? ";
        std::cin >> response;
        
        if(response == 'n'){
            std::cout << "Player 1 forfeits!" << std::endl;
            return 0;
        }
        
        //Move the player
        int playerRoll = rollDice();
        for(int i = 0; i < playerRoll; ++i){
            ++humanPlayer;
        }
        std::cout << "Player 1 rolled a " << playerRoll << "!" << std::endl;
        
        //Check for special tiles
        humanPlayer.checkTile();
        
        ///////// AI TURN //////////
        std::cout << std::endl << "Player 2 turn!" << std::endl << std::endl;
        
        //If playing with a human:
        if(AI == false){
            std::cout << "Roll the dice (y/n)? ";
            std::cin >> response;
        
            if(response == 'n'){
                std::cout << "Player 2 forfeits!" << std::endl;
                return 0;
            }
        }
        
        //Move the AI
        int AIRoll = rollDice();
        for(int i = 0; i < AIRoll; ++i){
            ++AIPlayer;
        }
        std::cout << "Player 2 rolled a " << AIRoll << "!" << std::endl;
        
        //Check for special tiles
        AIPlayer.checkTile();
        
        ///////// PRINT THE BOARD //////////
        char tempPlayer = *humanPlayer;
        *humanPlayer = '1';
        char tempAI = *AIPlayer;
        *AIPlayer = '2';
        gameBoard.printBoard();
        *AIPlayer = tempAI;
        *humanPlayer = tempPlayer; //In this order it shouldn't matter if both players are on the same tile
    }
    
    //Check who is the winner
    if(*humanPlayer == 'E'){
        std::cout << std::endl << "Congratulations Player 1! You Win!!!" << std::endl;
        return 0;
    }
    else{
        std::cout << std::endl << "Congratulations Player 2! You Win!!!" << std::endl;
        return 0;
    }
    
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

/** Rolls two "6-sided dice" and returns the result
 */
int rollDice(){
    int die1 = rand()%5 + 1;
    int die2 = rand()%5 + 1;
    return (die1 + die2);
}

/** Procedurally generates a 100 tile board
 */
void proceduralGen(board& procBoard){
    int tileCounter = 2;
    while(tileCounter < 85){
        int randNum = rand()%14 + 1;
        for(int i = 0; i < randNum; ++i){
            procBoard.push_back(' ');
        }
        
        int randSpec = rand()%4;
        if(randSpec == 0){
            procBoard.push_back('$');
        }
        else if(randSpec == 1){
            procBoard.push_back('#');
        }
        else if(randSpec == 2){
            procBoard.push_back('?');
        }
        else if(randSpec == 3){
            procBoard.push_back('T');
        }
        
        tileCounter += (randNum + 1);
    }
    
    int remaining = 100 - tileCounter;
    for(int i = 0; i < remaining; ++i){
        procBoard.push_back(' ');
    }
    
    return;
}

