/*
 * File:   Constants.cpp
 * Author: Group Papa
 */

#ifndef CONSTANTS_CPP
#define CONSTANTS_CPP

const int PIXELS_PER_METER = 20;
/**
 * Ensure that it is correct to avoid segmentation fault.
 */
const int MAX_DIST_FROM_START = 20;
const double MARGIN_M = 0.55;
const double SEEN_BOLDING_M = 0.1;
const double WALLS_BOLDING_M = 0.00;
/**
 * Maximum distance from the obtacles, within which penalties will be set.
 */
const double PENALTY_DIST_M = 1;


const int MARGIN_PX = MARGIN_M * PIXELS_PER_METER;
const int WIDTH = 2 * MAX_DIST_FROM_START * PIXELS_PER_METER + 2 * MARGIN_PX;
const int HEIGHT = 2 * MAX_DIST_FROM_START * PIXELS_PER_METER + 2 * MARGIN_PX;
const int SEEN_BOLDING_PX = SEEN_BOLDING_M * PIXELS_PER_METER;
const int WALLS_BOLDING_PX = WALLS_BOLDING_M * PIXELS_PER_METER;
const int PENALTY_DIST_PX = PENALTY_DIST_M * PIXELS_PER_METER;

#endif	/* CONSTANTS_CPP */
