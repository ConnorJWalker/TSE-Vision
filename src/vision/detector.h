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
    std::vector<DetectedCard> detectCards(const Images& images);

private:
 	static DetectedCard addCardData(const Images& images, cv::Rect roi);
	static bool isCardValid(const cv::Rect& card, std::vector<DetectedCard> detectedCards);
    static bool detectIfFaceUp(const cv::Mat& image, cv::Rect roi);
    static Colour detectColour(const cv::Mat& hsvImage, cv::Rect roi);
    static int detectCardValue(const cv::Mat& image, cv::Rect roi);

    static double getColourPercentage(const cv::Mat& roi, const std::vector<int>& upperBound, const std::vector<int>& lowerBound);

	std::vector<DetectedCard> detectedCards;

};
