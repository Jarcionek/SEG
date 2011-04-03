/*
 * File:   main.cpp
 * Author: Group Papa
 */

//#define PRINT(x) std::cout << print++ << ".\t" << x << std::endl

#ifdef PRINT
    int print = 0;
#endif

#include "Robot.cpp"
#include <string>
#include <sstream>
#include <time.h>
#include "DisplayOptions.cpp"

int main(int argc, char **argv) {
    DisplayOptions disopt = DisplayOptions();
    
    for (int i = 1; i < argc; i++) {
        std::string x = argv[i];
        if (x.compare("-help") == 0) {
            std::cout << "ALLOWED ARGUMENTS:" << std::endl;
            std::cout << "-atend bool - do not display map while exploring" << std::endl;
            std::cout << "-objects bool - displays recognised objects in different color" << std::endl;
            std::cout << "-objectsh bool - displays circles around recognised objects" << std::endl;
            std::cout << "-robsize int - displays a robot of given size, -1 to disable" << std::endl;
            std::cout << "-footprints - displays robot's footprints" << std::endl;
            std::cout << "-path - displays robot's current path" << std::endl;
            std::cout << "-margin - displays path finder's margin from the walls" << std::endl;
            std::cout << "-walls int - displays walls bolded by given amount of pixels" << std::endl;
            std::cout << "-penalties - displays path finder's penalties from the walls" << std::endl;
            exit(0);
        } else if (x.compare("-atend") == 0) {
            std::stringstream ss(argv[++i]);
            ss >> disopt.atEndOnly;
        } else if (x.compare("-objects") == 0) {
            std::stringstream ss(argv[++i]);
            ss >> disopt.objects;
        } else if (x.compare("-objectsh") == 0) {
            std::stringstream ss(argv[++i]);
            ss >> disopt.objectsH;
        } else if (x.compare("-robsize") == 0) {
            std::stringstream ss(argv[++i]);
            ss >> disopt.robsize;
        } else if (x.compare("-footprints") == 0) {
            disopt.footprints = 1;
        } else if (x.compare("-path") == 0) {
            disopt.path = 1;
        } else if (x.compare("-margin") == 0) {
            disopt.margin = 1;
        } else if (x.compare("-walls") == 0) {
            std::stringstream ss(argv[++i]);
            ss >> disopt.walls;
        } else if (x.compare("-penalties") == 0) {
            disopt.penalties = 1;
        } else {
            std::cout << "Unknown argument: "<< x << " Try -help" << std::endl;
            exit(0);
        }
    }

    #ifdef PRINT
        PRINT("USER DEFINED:");
        PRINT("PIXELS_PER_METER = " << PIXELS_PER_METER);
        PRINT("MAX_DIST_FROM_START = " << MAX_DIST_FROM_START);
        PRINT("MARGIN_M = " << MARGIN_M);
        PRINT("SEEN_BOLDING_M = " << SEEN_BOLDING_M);
        PRINT("WALLS_BOLDING_M = " << WALLS_BOLDING_M);
        PRINT("");
        PRINT("CALCULATED:");
        PRINT("MARGIN_PX = " << MARGIN_PX);
        PRINT("WIDTH = " << WIDTH);
        PRINT("HEIGHT = " << HEIGHT);
        PRINT("SEEN_BOLDING_PX = " << SEEN_BOLDING_PX);
        PRINT("WALLS_BOLDING_PX = " << WALLS_BOLDING_PX);
    #endif

    Robot *papabot = new Robot();
    papabot->disopt = disopt;

    #ifdef PRINT
        time_t start = time(NULL);
    #endif

    papabot->operate();

    #ifdef PRINT
        PRINT("DONE WITHIN " << (time(NULL) - start) << " SECONDS");
        PRINT("SNAPSHOTS: " << papabot->getSnapshots());
    #endif

    papabot->disopt.path = 0;
    papabot->saveMap();
    papabot->disopt = DisplayOptions();
    papabot->disopt.walls = disopt.walls;
    papabot->displayMap();
    sleep(1); // to ensure different file name in saving
    papabot->saveMap();

    delete papabot;
    return 0;
};
