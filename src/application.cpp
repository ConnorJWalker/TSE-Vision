#include "application.h"

Application::Application(std::string outputFilepath, bool shouldRender) : renderer(shouldRender) {
    output.open(outputFilepath);
}

Application::~Application() {
    output.close();
}

void Application::run() {
    while (true) {
        camera.getNextFrame();

        renderer.render(camera.getImages());

        if (cv::waitKey(30) >= 0) break;
    }
}
