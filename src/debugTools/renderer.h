#pragma once
#include <string>
#include <opencv.h>

#include "../vision/camera.h"

class Renderer {
public:
    Renderer(unsigned int gridWidth, unsigned int gridHeight, bool shouldRender = false);
    ~Renderer();

    void render(Images images);
private:
    void renderGrid(cv::Mat image);
    void renderCoordinates(cv::Mat image);

    bool shouldRender;
    unsigned int gridWidth, gridHeight;
};
