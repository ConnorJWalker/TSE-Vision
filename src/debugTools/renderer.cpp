#include "renderer.h"

Renderer::Renderer(unsigned int gridWidth, unsigned int gridHeight, bool shouldRender) {
    this->gridWidth = gridWidth;
    this->gridHeight = gridHeight;
    this->shouldRender = shouldRender;
}

Renderer::~Renderer() {
    cv::destroyAllWindows();
}

void Renderer::render(Images images) {
    if (!shouldRender) return;

    // Grid renderer must be called after card outline renderer to make sure it isn't drawn over
    renderGrid(images.original);

    cv::imshow("Original", images.original);
    cv::imshow("Greyscale", images.greyscale);
    cv::imshow("Canny", images.canny);
    cv::imshow("HSV", images.hsv);
}

void Renderer::renderGrid(cv::Mat image) {
    // Render vertical lines, skip 0 as we want 1 less line than grid size
    for (size_t i = 1; i < gridWidth; i++) {
        float x = i * image.cols / gridWidth;
        cv::line(image, cv::Point2f(x, 0.f), cv::Point2f(x, image.rows), cv::Scalar(255, 255, 0));
    }

    // Render horizontal lines, skip 0 as we want 1 less line than grid size
    for (size_t i = 1; i < gridHeight; i++) {
        float y = i * image.rows / gridHeight;
        cv::line(image, cv::Point2f(0, y), cv::Point2f(image.cols, y), cv::Scalar(255, 255, 0));
    }
}
