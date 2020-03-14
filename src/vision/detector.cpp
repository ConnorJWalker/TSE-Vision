#include "detector.h"

std::vector<DetectedCard> Detector::detectCards(const Images& images) {
	detectedCards.clear();
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(images.canny, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

	// For each detected contour, create a rectangle object in its location and add it to the
	// detected card vector to be returned to renderer. 

	for (const auto& contour : contours) {
		std::vector<cv::Point> contoursPoly;
		cv::approxPolyDP(contour, contoursPoly, 3, true);

		cv::Rect card = cv::boundingRect(contoursPoly);

		if (isCardValid(card, detectedCards)) {
			detectedCards.push_back(addCardData(images, card));
		}
	}
	return detectedCards;
}

bool Detector::isCardValid(const cv::Rect& card, std::vector<DetectedCard> detectedCards) {
	// Make sure the "card" is a reasonable width and height to avoid
	// noise being detected
	if (card.width < 100 && card.height < 200) return false;

	// Make sure that the card is at least 10px away from the last to prevent cards being counted
	// multiple times
	if (detectedCards.size() >= 1) {
		int previous = detectedCards.size() - 1;
		int distanceX = abs(card.tl().x - detectedCards[previous].cardRectangle.tl().x);
		int distanceY = abs(card.tl().y - detectedCards[previous].cardRectangle.tl().y);

		if (distanceX < 50 && distanceY < 50) {
			return false;
		}

		// Make sure that the new card is not inside the previous card
		cv::Rect previousCard = detectedCards[previous].cardRectangle;
		int previousWidth = previousCard.width;
		int previousHeight = previousCard.height;

		bool isXInside = card.tl().x > previousCard.tl().x&&
			card.tl().x < previousCard.tl().x + previousWidth;
		bool isYInside = card.br().y < previousCard.br().y &&
			card.br().y > previousCard.br().y - previousHeight;

		return !(isXInside && isYInside);
	}

	return true;
}

DetectedCard Detector::addCardData(const Images& images, cv::Rect roi) {
	bool isFaceUp = detectIfFaceUp(images.hsv, roi);
	
	return {
		cv::Point2f(
			roi.tl().x + (roi.width / 2),
			roi.br().y - (roi.height / 2)
		),
		roi,
		isFaceUp ? detectColour(images.hsv, roi) : Colour::Unknown,
		isFaceUp,
		false, // TODO,
		isFaceUp ? detectCardValue(images.hsv, roi) : -1
	};
}

bool Detector::detectIfFaceUp(const cv::Mat& hsvImage, cv::Rect roi) {
	cv::Mat Roi(hsvImage, roi);
	std::vector<int> lowerWhite = { 200, 200, 200 };
	std::vector<int> upperWhite = { 255, 255, 255 };
	std::vector<int> lowerNotWhite = { 0, 0, 0 };
	std::vector<int> upperNotWhite = { 128, 128, 128 };

	double whitePercentage = getColourPercentage(Roi, lowerWhite, upperWhite);
    double notWhitePercentage = getColourPercentage(Roi, lowerNotWhite, upperNotWhite);

	if (whitePercentage > notWhitePercentage) {
		return true;
	}
	else {
		return false;
	}
}

Colour Detector::detectColour(const cv::Mat& hsvImage, cv::Rect roi) {
    cv::Mat Roi(hsvImage, roi);
	std::vector<int> lowerRed = { 0, 120, 70 };
	std::vector<int> upperRed = { 10, 255, 255 };
	std::vector<int> lowerBlack = { 0, 0, 0 };
	std::vector<int> upperBlack = { 180, 255, 125 };
	
	double redPercentage = getColourPercentage(Roi, upperRed, lowerRed);
	double blackPercentage = getColourPercentage(Roi, upperBlack, lowerBlack);

	if (redPercentage > blackPercentage) {
		return Colour::Red;
	}
		
	return Colour::Black;
}

int Detector::detectCardValue(const cv::Mat& image, cv::Rect roi) {
	return -1;
}

double Detector::getColourPercentage(const cv::Mat &roi, const std::vector<int> &upperBound, const std::vector<int> &lowerBound) {
    cv::Mat mask;
    cv::inRange(roi, lowerBound, upperBound, mask);

    int imageSize = mask.rows * mask.cols;
    cv::threshold(mask, mask, 120, -1, cv::THRESH_TOZERO);

    return 1 - (imageSize - cv::countNonZero(mask)) / (double)imageSize;
}
