#pragma once
#include <vector>
#include <opencv.h>

#include "camera.h"

enum class Colour {
    Red, Black, Unknown
};

struct DetectedCard {
    cv::Point2f coordinates;
    Colour colour;
    bool isFaceUp;
    bool isKnown;
    int value;
};

class Detector {
public:
    std::vector<DetectedCard> detectCards(Images images);

private:
    void addCardData(Images images, cv::Rect roi);

    void detectIfFaceUp(cv::Mat image, cv::Rect roi);
    void detectColour(cv::Mat hsvImage, cv::Rect roi);
    void detectCardValue(cv::Mat image, cv::Rect roi);

    std::vector<DetectedCard> detectedCards;
};
