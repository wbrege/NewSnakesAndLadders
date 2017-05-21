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
class board;

/** The tiles form the basis of the entire game
 */
class tile{
    friend class board;
    friend class player;
public:
    tile(char inputIcon): icon(inputIcon), nextTile(nullptr), prevTile(nullptr), connectTile(nullptr){}
private:
    char icon; //# for ladders, & for snakes, ' ' for normal
    tile* nextTile;
    tile* prevTile;
    tile* connectTile; //For Snake tiles and Ladder tiles only
};

/** The "board" is essentially just a manager for the tiles
 */
class board{
public:
    board(): startTile(nullptr), endTile(nullptr){
        //Create the start and end tiles
        try{
            //Okay so I'm reinventing the wheel here and probably should just be using smart pointers, but this is a project of passion so I'm gonna go ahead and try and implement proper memory management all by myself anyway.
            startTile = new tile(' ');
            endTile = new tile(' ');
        }
        catch(std::exception &e){
            delete startTile;
            delete endTile;
            return;
        }
        startTile->nextTile = endTile;
        startTile->prevTile = nullptr;
        endTile->nextTile = nullptr;
        endTile->prevTile = startTile;
    }
    
    virtual ~board();
    void printBoard();
    void push_back(char);
    player start();
    player end();
    void connectTiles();
private:
    tile* startTile;
    tile* endTile;
};

/** The "player" is actually an iterator for the board class. Represented on the board as @
 */
class player{
    friend class board;
public:
    player(tile* inputPosition): position(inputPosition){}
    player& operator++();
    player& operator--();
    char operator*();
    
private:
    tile* position;
};

////////////////////////// FUNCTIONS //////////////////////////

//// Board Functions ////
/** Destructor for the board class 
 */
board::~board(){
    player deleter = start();
    while(deleter.position != endTile){
        tile* tempPos = deleter.position->nextTile;
        delete deleter.position;
        deleter.position = tempPos;
    }
    delete deleter.position; //Delete the final tile
}

/** Returns a player pointing to the starting tile 
 */
player board::start(){
    player returnPlayer(startTile);
    return returnPlayer;
}

/** Returns a player pointing to the ending tile
 */
player board::end(){
    player returnPlayer(endTile);
    return returnPlayer;
}

/** Adds a new tile immediately in front of the endTile. Does not connect tiles.
 */
void board::push_back(char inputIcon){
    tile* newTile = nullptr;
    try{
        newTile = new tile(inputIcon);
    }
    catch(std::exception &e){
        delete newTile;
        return;
    }
    
    endTile->prevTile->nextTile = newTile;
    newTile->prevTile = endTile->prevTile;
    newTile->nextTile = endTile;
    endTile->prevTile = newTile;
    
    return;
}

/** Prints the board to the console
 */
void board::printBoard(){
    player printer = end();
    int i = 0;
    
    while(printer.position != startTile){
        std::cout << "|" << *printer;
        ++i;
        if(i%10 == 0){
            std::cout << std::endl;
        }
    }
}

//// Player Functions ////
/** Moves the player to the next tile 
 */
player& player::operator++(){
    if(position->nextTile != nullptr){
        position = position->nextTile;
    }
    return *this;
}

/** Moves the player to the previous tile 
 */
player& player::operator--(){
    if(position->prevTile != nullptr){
        position = position->prevTile;
    }
    return *this;
}

/** Returns the icon of the tile the player is standing on 
 */
char player::operator*(){
    return position->icon;
}

#endif /* snakesAndHeaders_h */
