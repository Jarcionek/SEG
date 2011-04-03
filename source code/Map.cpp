/*
 * File:   Map.cpp
 * Author: Group Papa
 */

#ifndef MAP_CPP
#define MAP_CPP

#include <libplayerc++/playerc++.h>
#include "Map.h"
#include "Constants.cpp"
#include "MapSquare.cpp"
#include "PathFinder.cpp"
#include "Utilities.cpp"
#include "Point.cpp"
#include <cmath>

Map::Map() {
    grid = new MapSquare*[WIDTH];
    for (int i = 0; i < WIDTH; i++) {
        grid[i] = new MapSquare[HEIGHT];
        for (int j = 0; j < HEIGHT; j++) {
            grid[i][j] = MapSquare();
        }
    }
    objects = new std::vector<Object>();
    footprints = new std::vector<Point>();
};
Map::~Map() {
    for (int i = 0; i < WIDTH; i++) {
        delete grid[i];
    }
    delete grid;
    delete objects;
    delete footprints;
};
void Map::read(PlayerCc::LaserProxy *lp, PlayerCc::FiducialProxy *fp, PlayerCc::Position2dProxy *pp) {
    Point robpos = Point(WIDTH / 2 + pp->GetXPos() * PIXELS_PER_METER,
                        HEIGHT / 2 - pp->GetYPos() * PIXELS_PER_METER);
    double robangle = pp->GetYaw();
    double max = lp->GetMaxRange();
    int lasers = lp->GetCount() - 1;

    // FOOTPRINTS
    footprints->push_back(robpos);

    // FIDUCIAL
    for (int i = 0; i < fp->GetCount(); i++) {
        player_fiducial_item_t f = fp->GetFiducialItem(i);
        Object object = Object();

        // calculate the angle
        double x = f.pose.px < 0 ? -f.pose.px : f.pose.px;
        double y = f.pose.py < 0 ? -f.pose.py : f.pose.py;

        double angle = x != 0 ? atan( y / x ) : M_PI_2;
        angle = f.pose.px < 0 ? M_PI - angle : angle;
        angle = f.pose.py < 0 ? robangle - angle : robangle + angle;

        // calculate the position
        Point p = calculatePosition(sqrt(x*x + y*y), angle);
        p.x += robpos.x;
        p.y += robpos.y;

        // assign a color
        if (f.id == 19) { // dead
            object = Object(p, f.id, 1.1, 127, 127, 0);
        } else if (f.id == 40) { // live
            object = Object(p, f.id, 0.36, 0, 190, 0);
        } else if (f.id == 105) { // fire
            object = Object(p, f.id, 0.6, 255, 127, 0);
        }

        // check if object is already in the list
        if (object.id != -1) {
            bool exists = 0;
            for (int j = 0; j < objects->size(); j++) {
                if (objects->at(j).mayBeTheSame(object, PIXELS_PER_METER / 5)) {
                    exists = 1;
                    break;
                }
            }
            if (!exists) {
                objects->push_back(object);
                #ifdef PRINT
                    if (f.id == 19) {
                        PRINT("BODY FOUND");
                    } else if (f.id == 40) {
                        PRINT("HUMAN FOUND");
                    } else if (f.id == 105) {
                        PRINT("FIRE DETECTED");
                    }
                #endif
            }
            
        }
    }

    // LASERS
    for (int l = 0; l < lasers; l++) {
        double dist = lp->GetRange(l);

        //           = robangle + 2*M_PI*(l - lasers/2)/lasers;
        double angle = robangle + l * 2 * M_PI / lasers - M_PI;

        Point p = calculatePosition(dist, angle);
        p.x += robpos.x;
        p.y += robpos.y;

        // set unwalkable on the grid and inform path finder about a wall
        checkMap(p.x, p.y, WALLS_BOLDING_PX);
        if (dist < max) {
            for (int a = -WALLS_BOLDING_PX; a <= WALLS_BOLDING_PX; a++) {
                for (int b = -WALLS_BOLDING_PX; b <= WALLS_BOLDING_PX; b++) {
                    grid[p.x + a][p.y + b].walkable = 0;
                }
            }
            pathFinder->setWallDetectedAt(p.x, p.y);
        }

        // set seen
        std::vector<Point> points = p.getPointsBetween(robpos);
        for (int i = 0; i < (int) points.size() - (SEEN_BOLDING_PX + WALLS_BOLDING_PX + 1); i++) {
            Point r = points.at(i);
            for (int a = -SEEN_BOLDING_PX; a <= SEEN_BOLDING_PX; a++) {
                for (int b = -SEEN_BOLDING_PX; b <= SEEN_BOLDING_PX; b++) {
                    grid[r.x + a][r.y + b].seen = 1;
                }
            }
//            if (!grid[r.x][r.y].walkable) {
//                /* Is not necessary for static environments
//                 * Slightly modifies existing walls
//                 * Margin is not removed, but it doesn't really matter
//                 * as long as return path may be created through the margin
//                 */
//                grid[r.x][r.y].walkable = 1;
//            }
        }

    }
};

MapSquare **Map::getGrid() {
    return grid;
};

std::vector<Object> *Map::getObjects() {
    return objects;
};

std::vector<Point> *Map::getFootprints() {
    return footprints;
};

void Map::setPathFinder(PathFinder *pathFinder) {
    this->pathFinder = pathFinder;
};

#endif	/* MAP_CPP */
