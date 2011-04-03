/*
 * File:   MapDisplayer.cpp
 * Author: Group Papa
 */

#ifndef MAPDISPLAYER_CPP
#define	MAPDISPLAYER_CPP

#include "Constants.cpp"
#include "MapDisplayer.h"
#include <string>
#include <time.h>

#define WALL CV_RGB(0, 0, 0) // black
#define SEEN CV_RGB(255, 255, 255) // white
#define UNSEEN CV_RGB(127, 127, 127) // light gray
#define MARGIN CV_RGB(190, 190, 190) // dark gray
#define PATH CV_RGB(63, 0, 0) // brown
#define ROBOT CV_RGB(255, 0, 0) // red
#define VISITED CV_RGB(127, 127, 255) // light blue
#define OBJECTS_HIGHLIGHT CV_RGB(127, 0, 0) // dark red

MapDisplayer::MapDisplayer(Map *map, PathFinder *pathFinder, DisplayOptions *disopt) {
    this->map = map;
    this->pathFinder = pathFinder;
    this->disopt = disopt;
};

MapDisplayer::~MapDisplayer() {};

void MapDisplayer::display(int delay, int robx, int roby) {
    cvNamedWindow("image", 1);
    cvShowImage("image", createMap(robx, roby));
    cvWaitKey(delay);
};

void MapDisplayer::display(int delay) {
    display(delay, -1, -1);
};

void MapDisplayer::save() {
    time_t t = time(NULL);
    std::string name = ctime(&t);
    cvSaveImage(name.append(".png").c_str(), createMap(-1, -1));
};

IplImage *MapDisplayer::createMap(int robx, int roby) {
    IplImage *img = cvCreateImage(cvSize(WIDTH, HEIGHT), 8, 3);

    // CREATE A MAP
    for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
            cvSetAt(img, UNSEEN, j, i);
            if (map->getGrid()[i][j].seen) {
                cvSetAt(img, SEEN, j, i);
                if (disopt->penalties) {
                    cvSetAt(img, CV_RGB(0, 255 * pathFinder->getGrid()[i][j].penalty
                            / pathFinder->getBiggestPenalty(), 0),
                            j, i);
                }
            }
            if (disopt->margin) {
                if (pathFinder->getGrid()[i][j].margin) {
                    cvSetAt(img, MARGIN, j, i);
                }
            }
            if (!map->getGrid()[i][j].walkable) {
                cvSetAt(img, WALL, j, i);
            }
        }
    }

    // MAKE THE WALLS BOLD
    if (disopt->walls > 0) {
        // for each square
        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                // if square
                if (!map->getGrid()[i][j].walkable) {
                    // set color around square
                    for (int a = -disopt->walls; a <= disopt->walls; a++) {
                        for (int b = -disopt->walls; b <= disopt->walls; b++) {
                            cvSetAt(img, WALL, j + b, i + a);
                        }
                    }
                }
            }
        }
    }

    // CREATE FOOTPRINTS
    if (disopt->footprints) {
        for (int i = 0; i < map->getFootprints()->size(); i++) {
            cvSetAt(img, VISITED, map->getFootprints()->at(i).y, map->getFootprints()->at(i).x);
        }
    }

    // CREATE ROBOT
    if (robx > 0 && roby > 0) {
        for (int a = -disopt->robsize; a <= disopt->robsize; a++) {
            for (int b = -disopt->robsize; b <= disopt->robsize; b++) {
                cvSetAt(img, ROBOT, roby + a, robx + b);
            }
        }

    }

    // CREATE PATH
    if (disopt->path) {
        for (int i = 0; i < pathFinder->getPath()->size(); i++) {
            Point p = pathFinder->getPath()->at(i);
            cvSetAt(img, PATH, p.y, p.x);
        }
    }

    // CREATE OBJECTS
    for (int i = 0; i < map->getObjects()->size(); i++) {
        Object o = map->getObjects()->at(i);
        if (disopt->objects) {
            int r = o.size * PIXELS_PER_METER;
            checkMap(o.p.x, o.p.y, r);
            for (int a = o.p.x - r; a <= o.p.x + r; a++) {
                for (int b = o.p.y - r; b <= o.p.y + r; b++) {
                    if (sqrt( (a-o.p.x) * (a-o.p.x) + (b-o.p.y) * (b-o.p.y) ) <= r
                            && !map->getGrid()[a][b].walkable) {
                        cvSetAt(img, CV_RGB(o.color[0], o.color[1], o.color[2]), b, a);
                    }
                }
            }
        }
        // HIGHLIGHT OBJECTS
        if (disopt->objectsH) {
            cvCircle(img, cvPoint(o.p.x, o.p.y), 1.5 * PIXELS_PER_METER, OBJECTS_HIGHLIGHT, 2);
        }
    }

    return img;
};

#endif	/* MAPDISPLAYER_CPP */
