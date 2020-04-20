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

DetectedCard Ocr::run(cv::Mat roi, DetectedCard card) {
    return DetectedCard();
}

double Ocr::getBlackPercentage(cv::Mat numberRoi) {
    return 0;
}

void Ocr::getColourMasks(cv::Mat roi) {

}
