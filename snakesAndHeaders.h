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
    friend class player;
public:
    board(): startTile(nullptr), endTile(nullptr){
        //Create the start and end tiles
        try{
            //Okay so I'm reinventing the wheel here and probably should just be using smart pointers, but this is a learning project so I'm gonna go ahead and try and implement proper memory management all by myself anyway.
            startTile = new tile('S');
            endTile = new tile('E');
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

/** The "player" is actually an iterator for the board class. Represented on the board as 1 or 2
 */
class player{
    friend class board;
public:
    player(tile* inputPosition, board* inputBoard): position(inputPosition), theBoard(inputBoard){}
    player(tile* inputPosition, board* inputBoard, bool inputAI): position(inputPosition), theBoard(inputBoard), isAI(inputAI) {}
    player& operator++();
    player& operator--();
    char& operator*();
    void checkTile();
    void chanceTile();
    void triviaTile();
    void setAI(bool inputAI){
        isAI = inputAI;
    }
    
private:
    board* theBoard;
    tile* position;
    bool isAI = false;
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
    player returnPlayer(startTile, this);
    return returnPlayer;
}

/** Returns a player pointing to the ending tile
 */
player board::end(){
    player returnPlayer(endTile, this);
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
            std::cout << "|" << std::endl;
        }
        --printer;
    }
    std::cout << "|" << *printer << "|";
}

/** Connects all the snakes and ladders to their exit points "v" and "^" respectively.
 */
void board::connectTiles(){
    //Connect ladders first
    player connector = start();
    while(connector.position != endTile){
        //Check for ladder marker
        if(*connector == '#'){
            tile* origin = connector.position;
            int distance = (rand()%40 + 10);
            
            for(int i = 0; i < distance; ++i){
                ++connector;
            }
            //Check to make sure we are not replacing an already assigned tile
            if(*connector != ' '){
                while(*connector != ' '){
                    --connector; //Find an unassigned tile
                }
            }
            *connector = '^';
            tile* destination = connector.position;
            connector.position = origin;
            connector.position->connectTile = destination;
        }
        ++connector; //Move to next tile
    }
    
    //Connect ladders first
    connector = end();
    while(connector.position != startTile){
        //Check for snake marker
        if(*connector == '$'){
            tile* origin = connector.position;
            int distance = (rand()%40 + 10);
            
            for(int i = 0; i < distance; ++i){
                --connector;
            }
            //Check to make sure we are not replacing an already assigned tile
            if(*connector != ' '){
                while(*connector != ' '){
                    ++connector; //Find an unassigned tile
                }
            }
            *connector = 'v';
            tile* destination = connector.position;
            connector.position = origin;
            connector.position->connectTile = destination;
        }
        --connector; //Move to next tile
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
char& player::operator*(){
    return position->icon;
}

/** Checks if the current tile is special and performs the appropriate action
 */
void player::checkTile(){
    switch(position->icon) {
        case '#':
            std::cout << "Great! You landed on a Ladder!" << std::endl;
            position = position->connectTile;
            return;
        case '$':
            std::cout << "Oh no! You landed on a Snake!" << std::endl;
            position = position->connectTile;
            return;
        case '?':
            std::cout << "Chance Tile!!!" << std::endl;
            chanceTile();
            return;
        case 'T':
            std::cout << "Trivia Tile!!! Answer correctly and you move 5 steps forward! But if you answer wrong you will move 5 steps back!" << std::endl;
            triviaTile();
            return;
    }
}

/** Something interesting happens ;)
 */
void player::chanceTile(){
    int randNum = rand()% 99 + 1;
    if(randNum <= 25){ //Move forward
        std::cout << "Have a little boost ;)" << std::endl;
        for(int i = 0, j = (randNum%5 + 1); i < j; ++i){
            ++(*this);
        }
        return;
    }
    if(randNum > 25 && randNum <= 50){ //Move back
        std::cout << "Uh oh! You slipped back!" << std::endl;
        for(int i = 0, j = ((randNum-25)%5 + 1); i < j; ++i){
            --(*this);
        }
        return;
    }
    if(randNum > 50 && randNum <= 60){ //Make a new ladder
        std::cout << "Secret Ladder! :D" << std::endl;
        position->icon = '#';
        
        //Connect the new ladder
        player connector = *this;
        tile* origin = connector.position;
        int distance = (rand()%40 + 10);
        
        for(int i = 0; i < distance; ++i){
            ++connector;
        }
        if(*connector != ' '){
            while(*connector != ' '){
                --connector;
            }
        }
        *connector = '^';
        tile* destination = connector.position;
        connector.position = origin;
        connector.position->connectTile = destination;
        position = position->connectTile;
        
        return;
    }
    if(randNum > 60 && randNum <= 70){ //Make a new snake
        std::cout << "Secret Snake! D:" << std::endl;
        position->icon = '$';
        
        //Connect the new snake
        player connector = *this;
        tile* origin = connector.position;
        int distance = (rand()%40 + 10);
        
        for(int i = 0; i < distance; ++i){
            --connector;
        }
        if(*connector != ' '){
            while(*connector != ' '){
                ++connector;
            }
        }
        *connector = 'v';
        tile* destination = connector.position;
        connector.position = origin;
        connector.position->connectTile = destination;
        position = position->connectTile;
        
        return;
    }
    if(randNum > 70 && randNum <= 80){ //Make a new trivia
        std::cout << "Secret Trivia Tile!" << std::endl;
        position->icon = 'T';
        triviaTile();
        
        return;
    }
    if(randNum > 80 && randNum <= 99){ //Draw a dog
        std::cout << "Check out this dog!" << std::endl;
        std::cout << "                  ▄              ▄" << std::endl;
        std::cout << "                 ▌▒█           ▄▀▒▌" << std::endl;
        std::cout << "                 ▌▒▒█        ▄▀▒▒▒▐" << std::endl;
        std::cout << "                ▐▄▀▒▒▀▀▀▀▄▄▄▀▒▒▒▒▒▐" << std::endl;
        std::cout << "              ▄▄▀▒░▒▒▒▒▒▒▒▒▒█▒▒▄█▒▐" << std::endl;
        std::cout << "             ▄▀▒▒▒░░░▒▒▒░░░▒▒▒▀██▀▒▌" << std::endl;
        std::cout << "            ▐▒▒▒▄▄▒▒▒▒░░░▒▒▒▒▒▒▒▀▄▒▒▌" << std::endl;
        std::cout << "            ▌░░▌█▀▒▒▒▒▒▄▀█▄▒▒▒▒▒▒▒█▒▐" << std::endl;
        std::cout << "           ▐░░░▒▒▒▒▒▒▒▒▌██▀▒▒░░░▒▒▒▀▄▌" << std::endl;
        std::cout << "           ▌░▒▄██▄▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒▌" << std::endl;
        std::cout << "          ▌▒▀▐▄█▄█▌▄░▀▒▒░░░░░░░░░░▒▒▒▐" << std::endl;
        std::cout << "          ▐▒▒▐▀▐▀▒░▄▄▒▄▒▒▒▒▒▒░▒░▒░▒▒▒▒▌" << std::endl;
        std::cout << "          ▐▒▒▒▀▀▄▄▒▒▒▄▒▒▒▒▒▒▒▒░▒░▒░▒▒▐" << std::endl;
        std::cout << "           ▌▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒░▒░▒░▒░▒▒▒▌" << std::endl;
        std::cout << "           ▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▒▄▒▒▐" << std::endl;
        std::cout << "            ▀▄▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▄▒▒▒▒▌" << std::endl;
        std::cout << "              ▀▄▒▒▒▒▒▒▒▒▒▒▄▄▄▀▒▒▒▒▄▀" << std::endl;
        std::cout << "                ▀▄▄▄▄▄▄▀▀▀▒▒▒▒▒▄▄▀" << std::endl;
        std::cout << "                   ▒▒▒▒▒▒▒▒▒▒▀▀" << std::endl;
        //Thanks to "hoserdude" for putting this dog ascii on github
        
        return;
    }
    if(randNum == 100){ //Move to end
        std::cout << "Wow! Lucky!" << std::endl;
        position = theBoard->endTile;
        --(*this);
        return;
    }
}

/** Asks the player some true/false questions, if they get it right they move forward, if they dont they move back
 */
void player::triviaTile(){
    int randNum = rand()%9 + 1;
    char response;
    char answer = 'X';
    
    switch(randNum) {
        case 1:
            std::cout << "As far as has ever been reported, no-one has ever seen an ostrich bury its head in the sand. (T/F)" << std::endl;
            answer = 'T';
            break;
        case 2:
            std::cout << "Approximately one quarter of human bones are in the feet. (T/F)" << std::endl;
            answer = 'T';
            break;
        case 3:
            std::cout << "Popeye’s nephews were called Peepeye, Poopeye, Pipeye and Pupeye. (T/F)" << std::endl;
            answer = 'T';
            break;
        case 4:
            std::cout << "In ancient Rome, a special room called a vomitorium was available for diners to purge food in during meals. (T/F)" << std::endl;
            answer = 'F';
            break;
        case 5:
            std::cout << "The average person will shed 10 pounds of skin during their lifetime. (T/F)" << std::endl;
            answer = 'F';
            break;
        case 6:
            std::cout << "Sneezes regularly exceed 100 m.p.h. (T/F)" << std::endl;
            answer = 'T';
            break;
        case 7:
            std::cout << "A slug’s blood is green. (T/F)" << std::endl;
            answer = 'T';
            break;
        case 8:
            std::cout << "The Great Wall Of China is visible from the moon. (T/F)" << std::endl;
            answer = 'F';
            break;
        case 9:
            std::cout << "Virtually all Las Vegas gambling casinos ensure that they have no clocks. (T/F)" << std::endl;
            answer = 'T';
            break;
        case 10:
            std::cout << "The total surface area of two human lungs have a surface area of approximately 70 square metres. (T/F)" << std::endl;
            answer = 'T';
            break;
    }
    
    if(isAI == false){
        std::cin >> response;
    }
    else{ //AI always guesses true
        response = 'T';
    }
    
    if(response == answer){
        std::cout << "CORRECT!" << std::endl;
        for(int i = 0; i < 5; ++i){
            ++(*this);
        }
    }
    else{
        std::cout << "INCORRECT!" << std::endl;
        for(int i = 0; i < 5; ++i){
            --(*this);
        }
    }
    
    checkTile();
}

#endif /* snakesAndHeaders_h */
