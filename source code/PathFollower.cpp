/*
 * File:   PathFollower.cpp
 * Author: Group Papa
 */

#ifndef PATHFOLLOWER_CPP
#define PATHFOLLOWER_CPP

#include "PathFollower.h"
#include "Constants.cpp"

PathFollower::PathFollower(PlayerCc::Position2dProxy *pp, PlayerCc::SonarProxy *sp, PathFinder *pf) {
    this->pp = pp;
    this->sp = sp;
    this->pf = pf;
    closeObstacle = 0;
};

PathFollower::~PathFollower() {};

void PathFollower::operate() {
    int robx = WIDTH / 2 + pp->GetXPos() * PIXELS_PER_METER;
    int roby = HEIGHT / 2 - pp->GetYPos() * PIXELS_PER_METER;
    double scan = sp->GetScan(0);

    // SAFETY PATH FINDER
    if (scan < 1 && !closeObstacle) {
        #ifdef PRINT
            PRINT("CLOSE OBSTACLE. FINDING NEW PATH");
        #endif
        closeObstacle = 1;
        pf->findNewPath(robx, roby);
    } else {
        closeObstacle = 0;
    }

    // PATH MODIFIER
    int front = scan * PIXELS_PER_METER / 2;
    while (!pf->path.empty()) {
        Point p = pf->path.at(pf->path.size() - 1);
        if (abs(p.x - robx) < front && abs(p.y - roby) < front) {
            pf->path.erase(pf->path.end());
        } else {
            break;
        }
    }

    double speed = 1.5;
    if (!pf->path.empty()) {
        // calculate the angle
        int x = pf->path.at(pf->path.size() - 1).x;
        int y = pf->path.at(pf->path.size() - 1).y;

        double angle;
        if (x < robx) {
            angle = asin(abs(x-robx) / sqrt((x-robx)*(x-robx) + (y-roby)*(y-roby))) + M_PI_2;
        } else {
            angle = asin(abs(y-roby) / sqrt((x-robx)*(x-robx) + (y-roby)*(y-roby)));
        }
        if (y > roby) {
            angle = -angle;
        }
        angle -= pp->GetYaw();

        angle = angle > M_PI ? angle - 2.0 * M_PI : angle;
        angle = angle < -M_PI ? angle + 2.0 * M_PI : angle;

        // set speed
        double tangle = angle < 0 ? -angle : angle;
        if (tangle > M_PI_4 * scan) {
            pp->SetSpeed(0, angle * 2);
		} else {
            pp->SetSpeed(speed, angle * 2);
        }
    }
};

#endif	/* PATHFOLLOWER_CPP */
