#include "application.h"

Application::Application(std::string outputFilepath, bool shouldRender) : renderer(shouldRender) {
    output.open(outputFilepath);
}

Application::~Application() {
    output.close();
}

void Application::run() {

}
