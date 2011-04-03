/* 
 * File:   PathFinder.cpp
 * Author: Group Papa
 */

#ifndef PATHFINDER_CPP
#define PATHFINDER_CPP

#include "PathFinder.h"
#include "Constants.cpp"
#include "Utilities.cpp"

PathFinder::PathFinder(MapSquare **grid) {
    this->grid = grid;
    PFgrid = new PathFinderSquare*[WIDTH];
    for (int i = 0; i < WIDTH; i++) {
        PFgrid[i] = new PathFinderSquare[HEIGHT];
        for (int j = 0; j < HEIGHT; j++) {
            PFgrid[i][j] = PathFinderSquare();
        }
    }
    for(int i = 0; i <= PIXELS_PER_METER; i++) {
        defValues[i] = (PIXELS_PER_METER + 5 - i) * (PIXELS_PER_METER + 5 - i);
    }
    mapExplored = 0;
    path = std::vector<Point>();
};

PathFinder::~PathFinder() {
    for (int i = 0; i < WIDTH; i++) {
        delete PFgrid[i];
    }
    delete PFgrid;
};

bool PathFinder::isMapExplored() {
    return mapExplored;
};

bool PathFinder::isStartAccessible() {
    return PFgrid[WIDTH/2][HEIGHT/2].cost != -1;
};

bool PathFinder::isPathValid() {
    if (path.empty()) {
        return 0;
    };
    Point p = path.front();
    if (grid[p.x][p.y].seen) {
        return 0;
    }
    for (int i = 0; i < path.size(); i++) {
        p = path.at(i);
        if (PFgrid[p.x][p.y].margin) {
            return 0;
        }
    }
    return 1;
};

bool PathFinder::isReturnPathValid() {
    if (path.empty()) {
        return 0;
    };
    Point p = path.front();
    if (p.x != WIDTH / 2 && p.y != HEIGHT / 2) {
        return 0;
    };
    for (int i = 0; i < path.size(); i++) {
        p = path.at(i);
        if (!grid[p.x][p.y].walkable) {
            return 0;
        }
    }
    return 1;
};

void PathFinder::findNewPath(int robx, int roby) {
    restore();
    
    std::queue<Point> list = std::queue<Point>();

    Point target = Point(robx, roby);
    list.push(target);
    PFgrid[robx][roby].cost = 0;

    bool margin = PFgrid[robx][roby].margin;
    // 0 margins not filled, break at !seen
    // 1 unwalkable not filled, switch at !margin

    while (true) {
        target = list.front();

        // if unseen found
        if (!grid[target.x][target.y].seen) {
            mapExplored = 0;
            break;
        }

        // if not-margin found, stop searching through the margin
        if (!PFgrid[target.x][target.y].margin) {
            margin = 0;
        }

        if (margin) {
            fillWalkableAround(&list, target, -1, 0, 2);
            fillWalkableAround(&list, target, 1, 0, 2);
            fillWalkableAround(&list, target, 0, -1, 2);
            fillWalkableAround(&list, target, 0, 1, 2);
            fillWalkableAround(&list, target, -1, -1, 3);
            fillWalkableAround(&list, target, -1, 1, 3);
            fillWalkableAround(&list, target, 1, -1, 3);
            fillWalkableAround(&list, target, 1, 1, 3);
        } else {
            fillNotMarginAround(&list, target, -1, 0, 2);
            fillNotMarginAround(&list, target, 1, 0, 2);
            fillNotMarginAround(&list, target, 0, -1, 2);
            fillNotMarginAround(&list, target, 0, 1, 2);
            fillNotMarginAround(&list, target, -1, -1, 3);
            fillNotMarginAround(&list, target, -1, 1, 3);
            fillNotMarginAround(&list, target, 1, -1, 3);
            fillNotMarginAround(&list, target, 1, 1, 3);
        }

        list.pop();
        if (list.empty()) {
            mapExplored = 1;
            break;
        }
    }
    if (mapExplored) {
        #ifdef PRINT
            PRINT("MAX EXPLORED");
        #endif
        findReturnPath(robx, roby);
    } else {
        choosePath(target, robx, roby);
    }
};

void PathFinder::findReturnPath(int robx, int roby) {
    restore();

    std::queue<Point> list = std::queue<Point>();

    Point target = Point(robx, roby);
    list.push(target);
    PFgrid[robx][roby].cost = 0;

    while (true) {
        target = list.front();

        if (target.x == WIDTH / 2 && target.y == HEIGHT / 2) {
            break;
        }

        fillSeenAround(&list, target, -1, 0, 2);
        fillSeenAround(&list, target, 1, 0, 2);
        fillSeenAround(&list, target, 0, -1, 2);
        fillSeenAround(&list, target, 0, 1, 2);
        fillSeenAround(&list, target, -1, -1, 3);
        fillSeenAround(&list, target, -1, 1, 3);
        fillSeenAround(&list, target, 1, -1, 3);
        fillSeenAround(&list, target, 1, 1, 3);

        list.pop();
        if (list.empty()) {
            break;
        }
    }
    if (isStartAccessible()) {
        choosePath(Point(WIDTH / 2, HEIGHT / 2), robx, roby);
        #ifdef PRINT
            PRINT("RETURN PATH FOUND");
        #endif
    }
};

std::vector<Point> *PathFinder::getPath() {
    return &path;
};

PathFinderSquare **PathFinder::getGrid() {
    return PFgrid;
};

void PathFinder::setWallDetectedAt(int x, int y) {
    // set margin
    checkMap(x, y, MARGIN_PX + WALLS_BOLDING_PX);
    for (int a = -(MARGIN_PX + WALLS_BOLDING_PX); a <= (MARGIN_PX + WALLS_BOLDING_PX); a++) {
        for (int b = -(MARGIN_PX + WALLS_BOLDING_PX); b <= (MARGIN_PX + WALLS_BOLDING_PX); b++) {
            PFgrid[x + a][y + b].margin = 1;
        }
    }
    // set penalty
    checkMap(x, y, PENALTY_DIST_PX);
    for (int a = -PENALTY_DIST_PX; a <= PENALTY_DIST_PX; a++) {
        for (int b = -PENALTY_DIST_PX; b <= PENALTY_DIST_PX; b++) {
            int k = abs(a) > abs(b)? abs(a) : abs(b);
            if (PFgrid[x + a][y + b].penalty < defValues[k])  {
                PFgrid[x + a][y + b].penalty = defValues[k];
            }
        }
    }
};

int PathFinder::getBiggestPenalty() {
    return defValues[0];
};

void PathFinder::restore() {
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            PFgrid[i][j].cost = -1;
        }
    }
};

void PathFinder::choosePath(Point target, int robx, int roby) {
    path.clear();
    Point current = Point(target.x, target.y);
    while (current.x != robx || current.y != roby) {
        path.push_back(Point(current.x, current.y));
        
        int nx = current.x;
        int ny = current.y;
        // find adjacent square with the lowest cost
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (PFgrid[current.x + i][current.y + j].cost != -1
                        && PFgrid[current.x + i][current.y + j].cost < PFgrid[nx][ny].cost) {
                    nx = current.x + i;
                    ny = current.y + j;
                }
            }
        }

        if (nx == current.x && ny == current.y) {
            /*
             * This may be invoked only while choosing as a target a point
             * which not necessarily has a cost set. It may occur only
             * in finding return path, so ensure that start point is accessible
             * after setting costs and before calling this method.
             */
            std::cerr << "ERROR - TARGET IS INACCESSIBLE" << std::endl;
            break;
        }

        current.x = nx;
        current.y = ny;
    }
};

void PathFinder::fillNotMarginAround(std::queue<Point> *list, Point p, int xm, int ym, int cost) {
    if (!PFgrid[p.x + xm][p.y + ym].margin) {
        fill(list, p, xm, ym, cost);
    }
};

void PathFinder::fillWalkableAround(std::queue<Point> *list, Point p, int xm, int ym, int cost) {
    if (grid[p.x + xm][p.y + ym].walkable) {
        fill(list, p, xm, ym, cost);
    }
};

void PathFinder::fillSeenAround(std::queue<Point> *list, Point p, int xm, int ym, int cost) {
    if (grid[p.x + xm][p.y + ym].seen && grid[p.x + xm][p.y + ym].walkable) {
        fill(list, p, xm, ym, cost);
    }
};

void PathFinder::fill(std::queue<Point> *list, Point p, int xm, int ym, int cost) {
    PathFinderSquare *current = &PFgrid[p.x][p.y];
    PathFinderSquare *adjacent = &PFgrid[p.x + xm][p.y + ym];
    if (adjacent->cost == -1 || adjacent->cost > current->cost + adjacent->penalty + cost) {
        adjacent->cost = current->cost + adjacent->penalty + cost;
        list->push(Point(p.x + xm, p.y + ym));
    }
};

#endif	/* PATHFINDER_CPP */