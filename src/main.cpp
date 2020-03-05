#include <string>
#include <cstring>
#include <iostream>

#include "application.h"

/*
 * Start our application by passing in the output filepath for card data, card grid width,
 * card grid height and a flag for if we should render to screen. These passed in argv
 */
int main(int argc, char** argv) {
    if (argc == 1) {
        std::cerr << "No arguments have been entered\n" << std::endl;
        std::cerr << "Please use the following format: ./vision.exe <card output filepath> [<-r>]" << std::endl;

        return 1;
    }

    std::string outputFilepath;
    bool shouldRender = false, heightGiven = false, widthGiven = false;
    unsigned int gridWidth, gridHeight;

    // begin loop at 1 as index 0 will always be the executable name
    for (size_t i = 1; i < argc; i++) {
        if (std::strcmp("-r", argv[i]) == 0 || std::strcmp("-render", argv[i]) == 0) {
            shouldRender = true;
        }
        else if (std::strcmp("-o", argv[i]) == 0) {
            outputFilepath = argv[++i];
        }
        else if (std::strcmp("-w", argv[i]) == 0) {
            widthGiven = true;
            gridWidth = std::stoul(argv[++i]);
        }
        else if (std::strcmp("-h", argv[i]) == 0) {
            heightGiven = true;
            gridHeight = std::stoul(argv[++i]);
        }
    }

    if (widthGiven && heightGiven) {
        Application app(outputFilepath, shouldRender, gridWidth, gridHeight);
        app.run();
    } else {
        Application app(outputFilepath, shouldRender);
        app.run();
    }

    return 0;
}