#pragma once
#include <string>
#include <opencv.h>
#include <vector>
#include <opencv2/highgui.hpp>
#include "Detector.h"

#include "../vision/camera.h"

class Renderer {
public:
    Renderer(unsigned int gridWidth, unsigned int gridHeight, bool shouldRender = false);
    ~Renderer();

    void render(Images images);
private:
    void renderGrid(cv::Mat image);
    void renderCoordinates(cv::Mat image);

    bool shouldRender;
    unsigned int gridWidth, gridHeight;

	// Properties
private:
	// Name of window the original image will be displayed in
	std::string windowName = "Simple Card Detection";

	// Name of windown the canny output image will be displyed in
	std::string cannyWindow = "Canny Card Detection Result";
	// Amount to scale images X by to make it fit on displays better
	const float scaleX = 0.5f;
	// Amount to scale images Y by to make it fit on displays better
	const float scaleY = 0.5f;

public:
	// Name of window the outlines and meta data will be displayed in
	// Public so threshold trackbar can be added
	std::string outlineWindow = "Outline of Card Detection";

	// Methods
public:
	void render(std::vector<DetectedCard> cards, cv::Mat image);
	void renderCanny(std::vector<DetectedCard> cards, cv::Mat cannyImage);
	void renderOutline(std::vector<DetectedCard> cards, int width, int height);
};
