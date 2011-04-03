/* 
 * File:   MapDisplayer.h
 * Author: Group Papa
 */

#ifndef MAPDISPLAYER_H
#define	MAPDISPLAYER_H

#include "Map.cpp"
#include "Point.cpp"
#include "PathFinder.cpp"
#include <vector>
#include "DisplayOptions.cpp"
#include <opencv/cv.h>
#include <opencv/highgui.h>

class MapDisplayer {
public:
    MapDisplayer(Map *map, PathFinder *pathFinder, DisplayOptions *disopt);
    ~MapDisplayer();
    /**
     * Displays a map with robot.
     * @param delay sets how long the map will be displayed waiting for a key
     * event. 0 for infinitely
     * @param robx robot's x position in the grid
     * @param roby robot's y position in the grid
     */
    void display(int delay, int robx, int roby);
    /**
     * Displays a map with robot.
     * @param delay sets how long the map will be displayed waiting for a key
     * event. 0 for infinitely
     */
    void display(int delay);
    void save();
private:
    Map *map;
    PathFinder *pathFinder;
    DisplayOptions *disopt;
    IplImage *createMap(int robx, int roby);
};

#endif	/* MAPDISPLAYER_H */

