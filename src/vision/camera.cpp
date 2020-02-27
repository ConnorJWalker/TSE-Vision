#include "camera.h"

Camera::Camera() : camera(0) {

}

void Camera::getNextFrame() {
    camera >> images.original;

    genGreyscaleImage();
    genCannyImage();
    genHSVImage();
}

Images Camera::getImages() const {
    return this->images;
}

void Camera::genGreyscaleImage() {
    cv::cvtColor(images.original, images.greyscale, cv::COLOR_BGR2GRAY);
}

void Camera::genCannyImage() {
    int threshold = 120;
    cv::Canny(images.greyscale, images.canny, threshold, threshold * 2);
}

void Camera::genHSVImage() {
    cv::cvtColor(images.original, images.hsv, cv::COLOR_BGR2HSV);
}
