#include "detector.h"

std::vector<DetectedCard> Detector::detectCards(Images images) {
    return std::vector<DetectedCard>();
}

void Detector::addCardData(Images images, cv::Rect roi) {

}

void Detector::detectIfFaceUp(cv::Mat image, cv::Rect roi) {

}

void Detector::detectColour(cv::Mat hsvImage, cv::Rect roi) {
    cv::Mat Roi(hsvImage, roi);
	double redPrecentage, blackPercentage;
	std::vector<int> lowerRed = { 0, 120, 70 };
	std::vector<int> upperRed = { 10, 255, 255 };
	std::vector<int> lowerBlack = { 0, 0, 0 };
	std::vector<int> upperBlack = { 180, 255, 125 };
	auto colourDetection = [](double& percentage, cv::Mat roi, std::vector<int>upperBound, std::vector<int>lowerBound) {
		cv::Mat mask;
		cv::inRange(roi, lowerBound, upperBound, mask);

		int imageSize = mask.rows * mask.cols;
		cv::threshold(mask, mask, 120, -1, cv::THRESH_TOZERO);

		percentage = 1 - (imageSize - cv::countNonZero(mask)) / (double)imageSize;
	};
	
	colourDetection(redPrecentage, Roi, upperRed, lowerRed);

	
	colourDetection(blackPercentage, Roi, upperBlack, lowerBlack);

	if (redPrecentage > blackPercentage) {
		
		Colour::Red;
	}
		
	Colour::Black;
}

void Detector::detectCardValue(cv::Mat image, cv::Rect roi) {

}
