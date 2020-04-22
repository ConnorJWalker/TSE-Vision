#include "ocr.h"

Ocr::Ocr() {
    ocr = new tesseract::TessBaseAPI();

    ocr->Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);
    ocr->SetPageSegMode(tesseract::PSM_SINGLE_CHAR);

    ocr->SetVariable("tessedit_char_whitelist", "A0123456789JQK");
    ocr->SetVariable("load_system_dawg", "false");
    ocr->SetVariable("load_freq_dawg", "false");
}

Ocr::~Ocr() {
    ocr->End();
    delete ocr;
}

char Ocr::detectCardValue(const Images& images, cv::Rect originalRoi, Colour colour) {
    getColourMasks(cv::Mat(images.hsv, cv::Rect(originalRoi.tl().x, originalRoi.tl().y, originalRoi.width / 2, originalRoi.height / 2)), colour);
    for (auto roi : findValueLocations()) {
        cv::Mat valueLocation(currentMask, roi);

        // Erode image
        constexpr int erosionSize = 3, width = 2 * erosionSize + 1;
        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(width, width), cv::Point(erosionSize, erosionSize));
        cv::erode(valueLocation, valueLocation, element);

        ocr->SetImage(valueLocation.data, valueLocation.cols, valueLocation.rows, 3, valueLocation.step);
        cv::rectangle(images.original, roi, cv::Scalar(255, 255, 0));
        std::cout << std::string(ocr->GetUTF8Text()).c_str()  << std::endl;
        return std::string(ocr->GetUTF8Text()).c_str()[0];
    }
}

double Ocr::getBlackPercentage(cv::Mat numberRoi) {
    int imageSize = numberRoi.rows * numberRoi.cols;
    return (imageSize - cv::countNonZero(numberRoi)) / (double)imageSize;
}

void Ocr::getColourMasks(cv::Mat hsv, Colour colour) {
    if (hsv.empty()) return;

    if (colour == Colour::Black) {
        cv::inRange(hsv, std::vector<int> {0, 120, 70}, std::vector<int> {10, 255, 255}, currentMask);
        cv::threshold(currentMask, currentMask, 120, 255, cv::THRESH_TOZERO);
    } else {
        cv::inRange(hsv, std::vector<int> {0, 0, 0}, std::vector<int> {180, 255, 125}, currentMask);
        cv::threshold(currentMask, currentMask, 120, 255, cv::THRESH_TOZERO);
    }

    cv::bitwise_not(currentMask, currentMaskInverted);
}

std::vector<cv::Rect> Ocr::findValueLocations() {
    cv::Mat cannyOutput;
    cv::Canny(currentMask, cannyOutput, 120.f, 240.f);

    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(cannyOutput, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    cv::imshow("REE", currentMask);

    std::vector<cv::Rect> rectangles;
    for (auto contour : contours) {
        std::vector<cv::Point> contoursPoly;
        cv::approxPolyDP(contour, contoursPoly, 3, true);

        cv::Rect roi = cv::boundingRect(contoursPoly);
        double blackPercentage = getBlackPercentage(cv::Mat(currentMask, roi));
        if (blackPercentage > 0.45 && roi.width > currentMask.cols / 10) {
            cv::Rect paddedRoi(roi.tl() - cv::Point(15, 15), roi.br() + cv::Point(15, 15));

            // Ensure the rectangle is valid before drawing / testing character value inside
            if (0 <= paddedRoi.x && 0 <= paddedRoi.width && paddedRoi.x + paddedRoi.width <= currentMask.cols) {
                if (0 <= paddedRoi.y && 0 <= paddedRoi.height && paddedRoi.y + paddedRoi.height <= currentMask.rows) {
                    rectangles.push_back(paddedRoi);
                }
            }
        }
    }

    return rectangles;
}
