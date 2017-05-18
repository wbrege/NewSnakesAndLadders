/** @file snakesAndHeaders.h
    @author William Brege
    @date 05/16/2017
 
    This contains the classes for my "Snakes and Ladders" reboot
 */

#include <string>


#ifndef snakesAndHeaders_h
#define snakesAndHeaders_h

/** The tiles form the basis of the entire game
 */
class tile{
    friend class board;
    friend class player;
public:
    tile(std::string inputIcon): icon(inputIcon){}
private:
    std::string icon; //# for ladders, & for snakes, ' ' for normal
    tile* nextTile;
    tile* prevTile;
    tile* connectTile; //For Snake tiles and Ladder tiles only
};

/** The "board" is essentially just a manager for the tiles
 */
class board{
public:
    board(){
        //Create the start and end tiles
        startTile = new tile(" ");
        endTile = new tile(" ");
        startTile->nextTile = endTile;
        startTile->prevTile = nullptr;
        endTile->nextTile = nullptr;
        endTile->prevTile = startTile;
        
        //For now the rest of the board will be assembled manually, in future I hope to add a function that will randomly generate the board
        
        
    }
    ~board();
    void printBoard();
    void push_back(std::string);
private:
    tile* startTile;
    tile* endTile;
};

/** The "player" is actually an iterator for the board class. Represented on the board as @
 */
class player{
public:
    player(tile* inputPosition): position(inputPosition){}
    void operator++();
    void operator--();
    std::string operator*();
    
private:
    tile* position;
};

#endif /* snakesAndHeaders_h */
