#include "renderer.h"

Renderer::Renderer(bool shouldRender) {
    this->shouldRender = shouldRender;
}

Renderer::~Renderer() {
    cv::destroyAllWindows();
}

void Renderer::render(Images images) {
    if (!shouldRender) return;

    cv::imshow("Original", images.original);
    cv::imshow("Greyscale", images.greyscale);
    cv::imshow("Canny", images.canny);
    cv::imshow("HSV", images.hsv);
}
