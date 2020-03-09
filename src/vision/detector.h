#pragma once
#include <vector>
#include <opencv2/opencv.hpp>

#include "camera.h"

enum class Colour {
    Red, Black, Unknown
};

struct DetectedCard {
    cv::Point2f coordinates;
	cv::Rect cardRectangle;
    Colour colour;
    bool isFaceUp;
    bool isKnown;
    int value;
};

class Detector {
public:
    std::vector<DetectedCard> detectCards(Images images);

private:
 	DetectedCard addCardData(Images images, cv::Rect roi);
	bool isCardValid(cv::Rect card, std::vector<DetectedCard> detectedCards);
  bool detectIfFaceUp(cv::Mat image, cv::Rect roi);
    void detectColour(cv::Mat hsvImage, cv::Rect roi);
    void detectCardValue(cv::Mat image, cv::Rect roi);
	std::vector<DetectedCard> detectedCards;

};
