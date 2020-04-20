#include "ocr.h"

Ocr::Ocr() {

}

Ocr::~Ocr() {

}

DetectedCard Ocr::run(cv::Mat roi, DetectedCard card) {
    return DetectedCard();
}

double Ocr::getBlackPercentage(cv::Mat numberRoi) {
    return 0;
}

void Ocr::getColourMasks(cv::Mat roi) {

}
