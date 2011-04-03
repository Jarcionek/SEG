/*
 * File:   Point.cpp
 * Author: Group Papa
 */

#ifndef POINT_CPP
#define POINT_CPP

#include <vector>

class Point {
    public:
        int x;
        int y;
        Point() {
            this->x = 0;
            this->y = 0;
        };
        Point(int x, int y) {
            this->x = x;
            this->y = y;
        };
        bool operator == (Point p) {
            return x == p.x && y == p.y;
        };
        /**
         * @return abs(x - p.x) <= r && abs(y - p.y) <= r
         */
        bool isCloseTo(Point p, int r) {
            return abs(x - p.x) <= r && abs(y - p.y) <= r;
        };
        
        /**
         * Returns a vector of all points which lie on the line between
         * this and p. This and p will be in the vector returned.
         * @param p other point
         * @return vector of points
         */
        std::vector<Point> getPointsBetween(Point p) {
            std::vector<Point> result = std::vector<Point>();
            int xdif = abs(p.x - x);
            int ydif = abs(p.y - y);
            int xpos = p.x - x > 0 ? 1 : -1;
            int ypos = p.y - y > 0 ? 1 : -1;

            if (xdif > ydif) {
                for (int i = xdif; i >= 0; i--) {
                    result.push_back(Point(x + xpos * i, y + ypos * ( ydif * i/xdif ) ));
                }
            } else if (xdif < ydif) {
                for (int i = ydif; i >= 0; i--) {
                    result.push_back(Point(x + xpos * (xdif * i/ydif), y + ypos * i));
                }
            } else { // xdif == ydif
                for (int i = ydif; i >= 0; i--) {
                    result.push_back(Point(x + xpos * i, y + ypos * i));
                }
            }

            return result;
        };
};

#endif	/* POINT_CPP */