# New Snakes and Ladders
I have recreated the children's game "Snakes and Ladders" using C++. It has Snakes and Ladders, obviously, as well as a couple of my own additions: Chance tiles, which result in a random event occuring, and Trivia tiles, which pose you a question and the possibility of a reward for correct answers or a punishment for incorrect answers. It can be played alone or with a friend.

# Classes #
## Tile ##
This class simply stores the visual information for the tile as well the previous and next tiles.

## Board ##
This class acts as a memory manager for the tile objects. It is modelled off a linked list so it only directly stores the location of the start and end tiles.

## Player ##
The player is an iterator for the board class. It holds all the function pertaining to the players actions, such as moving on the board, which is just like navigating a linked list, and performing any special functions pertaining to any special tiles the player may have landed on.
