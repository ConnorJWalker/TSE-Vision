#include "application.h"

Application::Application(std::string outputFilepath, bool shouldRender, unsigned int gridWidth, unsigned int gridHeight) :
    renderer(gridWidth, gridHeight, shouldRender)
{
    this->gridWidth = gridWidth;
    this->gridHeight = gridHeight;
    output.open(outputFilepath);
}

Application::~Application() {
    output.close();
}

void Application::run() {
    while (true) {
        camera.getNextFrame();

        auto cards = detector.detectCards(camera.getImages());
        renderer.render(camera.getImages(), cards);

        if (cv::waitKey(30) >= 0) break;
    }
}
