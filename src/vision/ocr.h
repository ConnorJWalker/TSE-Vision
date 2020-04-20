#pragma once
#include <vector>
#include <opencv.h>
#include <tesseract/baseapi.h>
#include "detector.h"

class Ocr {
public:
    Ocr();
    ~Ocr();

    char detectCardValue(cv::Mat hsv, cv::Rect roi);

private:
    tesseract::TessBaseAPI* ocr;
    cv::Mat currentMask, currentMaskInverted;

    double getBlackPercentage(cv::Mat numberRoi);
    void getColourMasks(cv::Mat hsv, cv::Rect roi);
    std::vector<cv::Rect> findValueLocations();
};
