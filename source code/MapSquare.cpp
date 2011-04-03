/*
 * File:   MapSquare.cpp
 * Author: Group Papa
 */

#ifndef MAP_SQUARE_CPP
#define MAP_SQUARE_CPP

class MapSquare {
    public:
        bool walkable;
        bool seen;
        
        MapSquare() {
            walkable = 1;
            seen = 0;
        };
};

#endif	/* MAP_SQUARE_CPP */