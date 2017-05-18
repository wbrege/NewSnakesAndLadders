/** @file snakesAndHeaders.h
    @author William Brege
    @date 05/16/2017
 
    This contains the classes for my "Snakes and Ladders" reboot
 */

#include <string>


#ifndef snakesAndHeaders_h
#define snakesAndHeaders_h

////////////////////// CLASSES ////////////////////////
class player;

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
        
        //For now the rest of the board will be assembled manually, in future I hope to add a function that will procedurally generate the board
        
        
    }
    virtual ~board(){
        
    }
    void printBoard();
    void push_back(std::string);
    player start();
private:
    tile* startTile;
    tile* endTile;
};

/** The "player" is actually an iterator for the board class. Represented on the board as @
 */
class player{
public:
    player(tile* inputPosition): position(inputPosition){}
    player& operator++();
    player& operator--();
    std::string operator*();
    
private:
    tile* position;
};

////////////////////////// FUNCTIONS //////////////////////////

//// Board Functions ////
/** Returns a player pointing to the starting tile */
player board::start(){
    player returnPlayer(startTile);
    return returnPlayer;
}

//// Player Functions ////
/** Moves the player to the next tile */
player& player::operator++(){
    if(position->nextTile != nullptr){
        position = position->nextTile;
    }
    return *this;
}

/** Moves the player to the previous tile */
player& player::operator--(){
    if(position->prevTile != nullptr){
        position = position->prevTile;
    }
    return *this;
}

/** Returns the icon of the tile the player is standing on */
std::string player::operator*(){
    return position->icon;
}

#endif /* snakesAndHeaders_h */
