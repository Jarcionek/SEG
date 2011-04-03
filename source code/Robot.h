/* 
 * File:   Robot.h
 * Author: Group Papa
 */

#ifndef ROBOT_H
#define	ROBOT_H

#include <libplayerc++/playerc++.h>
#include "Map.cpp"
#include "PathFinder.cpp"
#include "MapDisplayer.cpp"
#include "PathFollower.cpp"
#include "DisplayOptions.cpp"

class Robot {
    public:
        DisplayOptions disopt;
        Robot();
        ~Robot();
        void operate();
        /**
         * Displays a map without a robot.
         * @see DisplayOptions.cpp
         */
        void displayMap();
        void saveMap();
        /**
         * Returns the amount of reading from all sensors.
         * @return the amount of reading from all sensors
         */
        int getSnapshots();
    private:
        PlayerCc::PlayerClient *robot;
        PlayerCc::Position2dProxy *pp;
        PlayerCc::SonarProxy *sp;
        PlayerCc::LaserProxy *lp;
        PlayerCc::FiducialProxy *fp;
        Map *map;
        PathFinder *pathFinder;
        MapDisplayer *mapDisplayer;
        PathFollower *pathFollower;
        /**
         * Number of times data has been collected from the sensors.
         */
        int snapshots;
};

#endif	/* ROBOT_H */

