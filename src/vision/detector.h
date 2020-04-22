#pragma once
#include <vector>
#include <opencv2/opencv.hpp>

#include "ocr.h"
#include "colour.h"
#include "camera.h"

struct DetectedCard {
    cv::Point2f coordinates;
	cv::Rect cardRectangle;
    Colour colour;
    bool isFaceUp;
    bool isKnown;
    char value;
};

class Ocr;

class Detector {
public:
    std::vector<DetectedCard> detectCards(const Images& images, int gridWidth, int gridHeight);
    static Colour detectColour(const cv::Mat& hsvImage, cv::Rect roi);

private:
 	DetectedCard addCardData(const Images& images, cv::Rect roi, int gridWidth, int gridHeight);
	static bool isCardValid(const cv::Rect& card, std::vector<DetectedCard> detectedCards);
    static int detectCardValue(const cv::Mat& image, cv::Rect roi);

    static double getColourPercentage(const cv::Mat& roi, const std::vector<int>& upperBound, const std::vector<int>& lowerBound);

	std::vector<DetectedCard> detectedCards;
    Ocr ocr;
};
