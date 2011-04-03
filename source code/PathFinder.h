/* 
 * File:   PathFinder.h
 * Author: Group Papa
 */

#ifndef PATHFINDER_H
#define	PATHFINDER_H

#include "Constants.cpp"
#include "MapSquare.cpp"
#include "PathFinderSquare.cpp"
#include "Point.cpp"
#include <vector>
#include <queue>

class PathFinder {
public:
    std::vector<Point> path;
    PathFinder(MapSquare **grid);
    ~PathFinder();
    bool isMapExplored();
    bool isStartAccessible();
    /**
     * Standard path is valid if a path list:<ul>
     * <li> is not empty
     * <li> its last point is marked as unseen
     * <li> all points in the path are not margin ones
     * </ul>
     * @return
     */
    bool isPathValid();
    /**
     * Return path is valid if a path list:<ul>
     * <li> is not empty
     * <li> its last point is the center of the grid (it's a robot's starting position)
     * <li> all points in the path are walkable
     * </ul>
     * @return true if return path is valid, false otherwise
     */
    bool isReturnPathValid();
    /**
     * Clears existing costs and fills a grid with new costs, starting from
     * robot's position and expanding equally in every direction until unseen
     * square is found. If no unseen square is found, invokes
     * findReturnPath(robx, roby).<p>
     * If grid[robx][roby].margin is true, then a method first looks for
     * walkable not-margin position and then from there looks for unseen.
     * @param robx robot's x position in the grid
     * @param roby robot's y position in the grid
     * @see void findReturnPath(int robx, int roby)
     */
    void findNewPath(int robx, int roby);
    /**
     * Works similary to findNewPath(int robx, int roby) with the diference
     * that this method looks for a path through any seen square and DOES ignore
     * margins. Safe distance from the obstacles is kept because of penalties.
     * May not create a path if robot is separated with unwalkables and unseens.
     * @param robx robot's x position in the grid
     * @param roby robot's y position in the grid
     * @see void findNewPath(int robx, int roby);
     */
    void findReturnPath(int robx, int roby);
    std::vector<Point> *getPath();
    PathFinderSquare **getGrid();
    /**
     * Sends information to path finder to update its grid with margin and
     * penalties.
     * @param x x position in the grid
     * @param y y position in the grid
     */
    void setWallDetectedAt(int x, int y);
    /**
     * Returns the biggest possible penalty for map displayer.
     * @return the biggest possible penalty for map displayer
     */
    int getBiggestPenalty();
private:
    bool mapExplored;
    MapSquare **grid;
    PathFinderSquare **PFgrid;
    /**
     * Default penalties of squares depending on their distance from the
     * closest unwalkable. 0 is wall's penalty.
     */
    int defValues[PIXELS_PER_METER + 1];
    /**
     * Sets costs of all squares to not filled.
     */
    void restore();
    /**
     * If costs are already set, this method finds the path of the lowest cost
     * from target point to robot's position. It should be checked if target
     * position is accessible before invoking this method (usually a target
     * is chosen by costs filling algorithm, the only exception is a return path),
     * however, this method does not hang up if target is inaccessible.
     * @param target target position in the grid
     * @param robx robot's current x position in the grid
     * @param roby robot's current y postion in the grid
     */
    void choosePath(Point target, int robx, int roby);
    /**
     * If adjacent square is not a margin, invokes fill(std::queue<Point>, Point, int, int, int).
     * For more information see there.
     * @see void fill(std::queue<Point> *list, Point p, int xm, int ym, int cost)
     */
    void fillNotMarginAround(std::queue<Point> *list, Point p, int xm, int ym, int cost);
    /**
     * If adjacent square is walkable, invokes fill(std::queue<Point>, Point, int, int, int).
     * For more information see there.
     * @see void fill(std::queue<Point> *list, Point p, int xm, int ym, int cost)
     */
    void fillWalkableAround(std::queue<Point> *list, Point p, int xm, int ym, int cost);
    /**
     * If adjacent square is seen and walkable, invokes fill(std::queue<Point>, Point, int, int, int).
     * For more information see there.<p>
     * One may say that it is the same as fillWalkableAround, but in case there
     * was a little gap between readings and a robot did not map a wall there,
     * we do not want the algorithm to set costs somewhere inside the walls.
     * @see void fill(std::queue<Point> *list, Point p, int xm, int ym, int cost)
     */
    void fillSeenAround(std::queue<Point> *list, Point p, int xm, int ym, int cost);
    /**
     * Takes a point from the grid which is adjacent to p with [xm, ym] direction
     * and updates its cost in two cases:<ul>
     * <li>the cost has not beet set yet
     * <li>cost of adjacent square is bigger than current one's cost + adjacent one's
     * penalty + movement cost
     * </ul>
     * If adjacent's square cost has been changed, point is added to the list.
     * @param list list of points
     * @param p current point
     * @param xm x modifier, should be 0, -1 or 1
     * @param ym y modifier, should be 0, -1 or 1
     * @param cost cost of movement from current point to adjacent one
     */
    void fill(std::queue<Point> *list, Point p, int xm, int ym, int cost);
};

#endif	/* PATHFINDER_H */

