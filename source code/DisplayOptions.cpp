/*
 * File:   DisplayOptions.cpp
 * Author: Group Papa
 */

#ifndef DISPLAYOPTIONS_CPP
#define	DISPLAYOPTIONS_CPP

class DisplayOptions {
    public:
        /**
         * Robot's x coordinate in the map grid
         */
        int robx;
        /**
         * Robot's y coordinate in the map grid
         */
        int roby;
        /**
         * Robot's display size in pixels, -1 = disabled, 0 = 1x1 px, 1 = 3x3 px
         */
        int robsize;
        /**
         * Displays robot's footprints
         */
        bool footprints;
        /**
         * Displays robot's current path
         */
        bool path;
        /**
         * Displays margins from walls
         */
        bool margin;
        /**
         * Displays recognised objects in different colour
         */
        bool objects;
        /**
         * Highlights objects by drawing circles around them
         */
        bool objectsH;
        /**
         * If true, map will be displayed only once it is finished
         */
        bool atEndOnly;
        /**
         * Displays walls bolded
         */
        int walls;
        /**
         * Display path finder's penalties from the walls
         */
        bool penalties;

        /**
         * Displays objects, their highlights and unbolded walls.
         * Does not display robot, footprints, path, margin.
         */
        DisplayOptions() {
            robx = -1;
            roby = -1;
            robsize = -1;
            footprints = 0;
            path = 0;
            margin = 0;
            objects = 1;
            objectsH = 1;
            atEndOnly = 1;
            walls = 0;
            penalties = 0;
        };
};

#endif	/* DISPLAYOTPIONS_CPP */