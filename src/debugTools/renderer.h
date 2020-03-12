#pragma once
#include <string>
#include <vector>
#include <opencv.h>
#include "../vision/detector.h"

#include "../vision/camera.h"

class Renderer {
public:
    Renderer(unsigned int gridWidth, unsigned int gridHeight, bool shouldRender = false);
    ~Renderer();

    void render(Images images, std::vector<DetectedCard>cards);
private:
    void renderGrid(cv::Mat image);
    void renderCoordinates(cv::Mat image);

    bool shouldRender;
    unsigned int gridWidth, gridHeight;
};

