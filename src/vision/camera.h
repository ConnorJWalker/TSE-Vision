#pragma once
#include <opencv.h>

struct Images {
    cv::Mat original;
    cv::Mat greyscale;
    cv::Mat canny;
    cv::Mat hsv;
};

class Camera {
public:
    Camera();

    void getNextFrame();
    Images getImages() const;
private:
    cv::VideoCapture camera;
    Images images;

    void genGreyscaleImage();
    void genCannyImage();
    void genHSVImage();
};
