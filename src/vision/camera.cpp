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

}

void Camera::genCannyImage() {

}

void Camera::genHSVImage() {

}
