#pragma once
#include <string>
#include <opencv.h>

#include "../vision/camera.h"

class Renderer {
public:
    explicit Renderer(bool shouldRender = false);
    ~Renderer();

    void render(Images images);
private:
    bool shouldRender;
};
