/* 
 * File:   PathFollower.h
 * Author: Group Papa
 */

#ifndef PATHFOLLOWER_H
#define	PATHFOLLOWER_H

#include <libplayerc++/playerc++.h>
#include "PathFinder.h"

class PathFollower {
    public:
        PathFollower(PlayerCc::Position2dProxy *pp, PlayerCc::SonarProxy *sp, PathFinder *pathFinder);
        ~PathFollower();
        /**
         * Firstly, this method checks a safety distance using sonar, and if the
         * reading is too small, requests to find a new path (because robot
         * is probably on the margin, so a new path will lead to non-margin first).<p>
         * Secondly, method removes from path finder's path all those points
         * which are close to the robot (how close depends on sonar readings).<p>
         * Finally it calculates in which direction there is a first point from the
         * path and sets motors to go to it. If robot has to turn by a large angle,
         * it turnes in place. It is also modified by the sonar - if the robot is
         * close to an obstacle, it needs higher precision. It means that in a large
         * room the robot may move when turning by 90 degrees, but in narrow corridor it
         * may turn in place even 20 degrees. Also, the robot's speed depends on the
         * distance from the closest obtacle.
         */
        void operate();
    private:
        PlayerCc::Position2dProxy *pp;
        PlayerCc::SonarProxy *sp;
        PathFinder *pf;
        /**
         * In case robot has been found too close to the obstacle, it requests a path
         * finder to find a new path to leave a margin first. This boolean becomes
         * false once robot is further from the obstacle. Briefly, it does not
         * allow multiple path finding in a short period of time.
         */
        bool closeObstacle;
};

#endif	/* PATHFOLLOWER_H */

