#pragma once
#include <vector>
#include <opencv.h>
#include <tesseract/baseapi.h>
#include <iostream>
#include "camera.h"
#include "colour.h"

class Ocr {
public:
    Ocr();
    ~Ocr();

    char detectCardValue(const Images& images, cv::Rect roi, Colour colour);

private:
    tesseract::TessBaseAPI* ocr;
    cv::Mat currentMask, currentMaskInverted;

    double getBlackPercentage(cv::Mat numberRoi);
    void getColourMasks(cv::Mat hsv, Colour colour);
    std::vector<cv::Rect> findValueLocations();
};
