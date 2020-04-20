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

char Ocr::run(cv::Mat hsv, cv::Rect roi) {

}

double Ocr::getBlackPercentage(cv::Mat numberRoi) {
    int imageSize = numberRoi.rows * numberRoi.cols;
    return (imageSize - cv::countNonZero(numberRoi)) / (double)imageSize;
}

void Ocr::getColourMasks(cv::Mat hsv, cv::Rect roi) {
    if (Detector::detectColour(hsv, roi) == Colour::Black) {
        cv::inRange(hsv, std::vector<int> {0, 120, 70}, std::vector<int> {10, 255, 255}, currentMask);
        cv::threshold(currentMask, currentMask, 120, 255, cv::THRESH_TOZERO);
    } else {
        cv::inRange(hsv, std::vector<int> {0, 0, 0}, std::vector<int> {180, 255, 125}, currentMask);
        cv::threshold(currentMask, currentMask, 120, 255, cv::THRESH_TOZERO);
    }

    cv::bitwise_not(currentMask, currentMaskInverted);
}
