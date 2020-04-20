#pragma once
#include <opencv.h>
#include <tesseract/baseapi.h>
#include "detector.h"

class Ocr {
public:
    Ocr();
    ~Ocr();

    DetectedCard run(cv::Mat roi, DetectedCard card);

private:
    tesseract::TessBaseAPI* ocr;
    cv::Mat currentMask, currentMaskInverted;

    double getBlackPercentage(cv::Mat numberRoi);
    void getColourMasks(cv::Mat roi);
};
