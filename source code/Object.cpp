/*
 * File:   Robot.cpp
 * Author: Group Papa
 */

#ifndef OBJECT_CPP
#define OBJECT_CPP

#include "Point.cpp"

class Object {
    public:
        Point p;
        int id;
        /**
         * Color in RGB.
         */
        int color[3];
        double size;
        Object() {
            this->p = Point();
            this->id = -1;
            color[0] = 0;
            color[1] = 0;
            color[2] = 0;
            size = 0;
        };
        /**
         * @param p object's position
         * @param id object's id
         * @param size radius in meters
         * @param r part of object's RGB color
         * @param g part of object's RGB color
         * @param b part of object's RGB color
         */
        Object(Point p, int id, double size, int r, int g, int b) {
            this->p = p;
            this->id = id;
            color[0] = r;
            color[1] = g;
            color[2] = b;
            this->size = size;
        };
        /**
         * Compares all objects' values.
         * @param o other object
         * @return true if objects are exactly the same, false otherwise
         */
        bool operator == (Object o) {
            return p == o.p
                    && id == o.id
                    && color[0] == o.color[0]
                    && color[1] == o.color[1]
                    && color[2] == o.color[2];
        };
        /**
         * Checks for coordinates of two objects and their ids in case they
         * are similar. Does not check the color.
         * @return p.isCloseTo(o.p, r) && id == o.id
         * @see Point.cpp
         */
        bool mayBeTheSame(Object o, int r) {
            return p.isCloseTo(o.p, r) && id == o.id;
        };
};

#endif	/* OBJECT_CPP */