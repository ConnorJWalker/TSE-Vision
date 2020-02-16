#include <opencv.h>

int main() {
    cv::Mat image(200, 200, CV_8UC1, cv::Scalar(0, 0, 255));

    imshow("Test", image);

    while (true) {
        if (cv::waitKey(30) >= 0) break;
    }
}