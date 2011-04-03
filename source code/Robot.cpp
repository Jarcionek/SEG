/*
 * File:   Robot.cpp
 * Author: Group Papa
 */

#ifndef ROBOT_CPP
#define	ROBOT_CPP

#include "Robot.h"

Robot::Robot() {
    robot = new PlayerCc::PlayerClient("localhost", 6665);
    pp = new PlayerCc::Position2dProxy(robot, 0);
    sp = new PlayerCc::SonarProxy(robot, 0);
    lp = new PlayerCc::LaserProxy(robot, 0);
    fp = new PlayerCc::FiducialProxy(robot, 0);

    pp->SetMotorEnable(1);
    pp->RequestGeom();
    sp->RequestGeom();
    lp->RequestGeom();
    fp->RequestGeometry();
    
    map = new Map();
    pathFinder = new PathFinder(map->getGrid());
    map->setPathFinder(pathFinder);
    mapDisplayer = new MapDisplayer(map, pathFinder, &disopt);
    pathFollower = new PathFollower(pp, sp, pathFinder);

    // I don't like it, but it's neccessary for first sensors reading to be correct
    pp->SetSpeed(0, 1);
    sleep(1);
    pp->SetSpeed(0, -1);
    sleep(1);
    pp->SetSpeed(0, 0);

    robot->Read();
    #ifdef PRINT
        PRINT("ROBOT INITIALIZED");
    #endif
};

Robot::~Robot() {
    delete map;
    delete pathFinder;
    delete mapDisplayer;
    delete pathFollower;
    delete pp;
    delete sp;
    delete lp;
    delete fp;
    delete robot;
};

void Robot::operate() {
    while (true) {
        robot->Read();

        int robx = disopt.robx = WIDTH / 2 + pp->GetXPos() * PIXELS_PER_METER;
        int roby = disopt.roby = HEIGHT / 2 - pp->GetYPos() * PIXELS_PER_METER;

        pathFollower->operate();

        if (pathFinder->isMapExplored() && pp->GetXPos() < 0.5 && pp->GetXPos() > -0.5
                && pp->GetYPos() < 0.5 && pp->GetYPos() > -0.5) {
            pathFinder->findNewPath(robx, roby);
            if (pathFinder->isPathValid()) {
                #ifdef PRINT
                    PRINT("OPS! I MISSED SOMETHING");
                #endif
            } else {
                break;
            }
        }

        map->read(lp, fp, pp);
        snapshots++;

        if (pathFinder->isMapExplored()) {
            if (!pathFinder->isReturnPathValid()) {
                pathFinder->findReturnPath(robx, roby);
            }
            if (!pathFinder->isStartAccessible()) {
                #ifdef PRINT
                    PRINT("START IS INACCESSIBLE");
                #endif
                break;
            }
        } else {
            if(!pathFinder->isPathValid()) {
                pathFinder->findNewPath(robx, roby);
            }
        }
        if (!disopt.atEndOnly) {
            mapDisplayer->display(2, robx, roby);
        }
    }
    pp->SetSpeed(0, 0);
};
void Robot::displayMap() {
    mapDisplayer->display(0);
};
void Robot::saveMap() {
    mapDisplayer->save();
};
int Robot::getSnapshots() {
    return snapshots;
};

#endif	/* ROBOT_CPP */
