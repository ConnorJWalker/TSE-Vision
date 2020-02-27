#include <string>
#include <cstring>
#include <iostream>

#include "application.h"

/*
 * Start our application by passing in the output filepath for card data and a flag
 * for if we should render to screen. These will be stored in argv array as such:
 *
 * argv[0] - Application name
 * argv[1] - Filepath to detected card output file
 * argv[2] - Should render to screen for debug (optional, default to false)
 */
int main(int argc, char** argv) {
    if (argc == 1) {
        std::cerr << "No arguments have been entered\n" << std::endl;
        std::cerr << "Please use the following format: ./vision.exe <card output filepath> [<-r>]" << std::endl;

        return 1;
    }

    std::string outputFilepath = argv[1];

    bool shouldRender = false;
    if (argc == 3) {
        if (std::strcmp("-r", argv[2]) == 0) {
            shouldRender = true;
        }
    }
    else if (argc > 3) {
        std::cout << "More than 2 arguments have been entered, extra arguments have been ignored" << std::endl;
    }

    Application app(outputFilepath, shouldRender);
    app.run();

    return 0;
}