#pragma once
#include <fstream>

#include "vision/camera.h"
#include "vision/detector.h"
#include "debugTools/renderer.h"

class Application {
public:
    /*!
     * @brief create instances of camera, detector and render classes as well as open file stream to output
     * file
     *
     * @param outputFilepath - String containing the filepath for the card data to be saved to
     * @param shouldRender - Bool value to determine if generated images should be displayed on screen
     *
     * @todo implement and add camera, detector and render classes
     */
    Application(std::string outputFilepath, bool shouldRender, unsigned int gridWidth = 5, unsigned int gridHeight = 5);
    ~Application();

    /*!
     * @brief Start the main application loop. This will continue to run the card detection
     * and output continuously until the exit condition is met
     * @todo Work out the exit condition for the main loop
     */
    void run();
private:
    std::fstream output;

    Camera camera;
    Detector detector;
    Renderer renderer;

    unsigned int gridWidth, gridHeight;
};
