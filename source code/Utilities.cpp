/*
 * File:   Constants.cpp
 * Author: Group Papa
 */

#ifndef UTILITIES_CPP
#define UTILITIES_CPP

#include "Constants.cpp"
#include "Point.cpp"

/**
 * Checks if point p(x, y), or any other point not further from p than range,
 * is not out of bounds
 * @param x x position in the grid
 * @param y y position in the grid
 * @param range minimum required distance from an array's bounds
 */
void checkMap(int x, int y, int range) {
    if (x - range < 0
            || x + range >= WIDTH
            || y - range < 0
            || y + range >= HEIGHT) {
        std::cerr << "ERROR - map initialised too small: " << std::endl
                << "WIDTH = " << WIDTH << std::endl
                << "HEIGHT = " << HEIGHT << std::endl
                << "x = " << x << std::endl
                << "y = " << y << std::endl
                << "r = " << range << std::endl;
    };
};

/**
 * Calculates a position of an object in robot's grid from the distance and the
 * angle given. Angle is not depended on robot's yaw but is relative to the map.
 * @param dist distance in meters
 * @param angle angle in radians
 * @return x, y postion of an object in robot's grid (relative to the robot)
 */
Point calculatePosition(double dist, double angle) {
    angle = angle > M_PI ? angle - 2 * M_PI : angle;
    angle = angle < -M_PI ? angle + 2 * M_PI : angle;

    bool top, right;
    if (angle > M_PI_2) { // top left
        angle -= M_PI;
        top = 1;
        right = 0;
    } else if (angle > 0) { // top right
        top = 1;
        right = 1;
    } else if (angle > -M_PI_2) { // bottom right
        angle += M_PI;
        top = 0;
        right = 1;
    } else { // bottom left
        angle += M_PI;
        top = 0;
        right = 0;
    }

    int x = abs(PIXELS_PER_METER * dist * cos(angle));
    int y = abs(PIXELS_PER_METER * dist * sin(angle));
    return Point(right? x : -x, top? -y : y);
};

#endif	/* CONSTANTS_CPP */