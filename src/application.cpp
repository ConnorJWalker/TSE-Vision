#include "application.h"

Application::Application(std::string outputFilePath, bool shouldRender, unsigned int gridWidth, unsigned int gridHeight) :
    renderer(gridWidth, gridHeight, shouldRender)
{
    this->gridWidth = gridWidth;
    this->gridHeight = gridHeight;
    this->outputFilePath = outputFilePath;
}

Application::~Application() {
    output.close();
}

void Application::run() {
    while (true) {
        camera.getNextFrame();

        auto cards = detector.detectCards(camera.getImages());
        renderer.render(camera.getImages(), cards);
        writeToFile(cards);

        if (cv::waitKey(30) >= 0) break;
    }
}

void Application::writeToFile(std::vector<DetectedCard> cards) {
    if (!output) {
        std::cerr << "File could not be opened: " << std::strerror(errno) << std::endl;
        return;
    }

    output.open(outputFilePath, std::ofstream::out | std::ofstream::trunc);

    for (auto card : cards) {
        if (card.colour == Colour::Unknown) {
            output << "Unknown\n";
            continue;
        }

        output << (card.colour == Colour::Black ? "Black" : "Red" ) << "\n";
    }

    output.close();
}
