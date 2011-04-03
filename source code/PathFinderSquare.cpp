/*
 * File:   PathFinderSquare.cpp
 * Author: Group Papa
 */

#ifndef PATHFINDERSQUARE_CPP
#define PATHFINDERSQUARE_CPP

class PathFinderSquare {
    public:
        bool margin;
        int penalty;
        int cost;

        PathFinderSquare() {
            margin = 0;
            penalty = 0;
            cost = -1;
        };
};

#endif	/* PATHFINDERSQUARE_CPP */