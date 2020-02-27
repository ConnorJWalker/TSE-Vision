#include "renderer.h"

Renderer::Renderer(bool shouldRender) {
    this->shouldRender = shouldRender;
}

Renderer::~Renderer() {
    cv::destroyAllWindows();
}

void Renderer::render(Images images) {
    if (shouldRender) {
        cv::imshow("Original", images.original);
    }
}
