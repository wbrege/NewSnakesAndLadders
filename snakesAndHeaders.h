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
public:
    tile(std::string inputIcon): icon(inputIcon){}
private:
    std::string icon;
    tile* nextTile;
    tile* prevTile;
};

/** The "board" is essentially just a manager for the tiles
 */
class board{
public:
    board(){}
    ~board();
    void printBoard();
    void push_back(*tile);
private:
    tile* startTile;
    tile* endTile;
};

/** The "player" is actually an iterator for the board class
 */
class player{
public:
    player(tile* inputPosition): position(inputPostion){}
    void operator++();
    void operator--();
    
private:
    tile* position;
};

#endif /* snakesAndHeaders_h */
