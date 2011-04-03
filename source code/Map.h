/*
 * File:   Map.h
 * Author: Group Papa
 */

#ifndef MAP_H
#define	MAP_H

#include <libplayerc++/playerc++.h>
#include "Constants.cpp"
#include "MapSquare.cpp"
#include "PathFinder.cpp"
#include "Object.cpp"
#include <vector>

class Map {
    public:
        Map();
        ~Map();
        /**
         * Collects data from sensors, saves them to the map and updates path
         * finder.
         * @param lp laser proxy
         * @param fp fiducial proxy
         * @param pp position 2d proxy
         */
        void read(PlayerCc::LaserProxy *lp, PlayerCc::FiducialProxy *fp, PlayerCc::Position2dProxy *pp);
        MapSquare **getGrid();
        std::vector<Object> *getObjects();
        std::vector<Point> *getFootprints();
        /**
         * Assign a path finder to the map, which will be updated in case
         * important data was gathered.
         * @param pathFinder a path finder to be updated
         */
        void setPathFinder(PathFinder *pathFinder);
    private:
        MapSquare **grid;
        PathFinder *pathFinder;
        std::vector<Object> *objects;
        std::vector<Point> *footprints;
};

#endif	/* MAP_H */

