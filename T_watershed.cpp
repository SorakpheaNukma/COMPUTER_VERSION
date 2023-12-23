#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;

int main() {
    // Read an image
    Mat image = imread("7bxj7_5c.jpg");


    if (image.empty()) {
        std::cerr << "Error: Could not read the image." << std::endl;
        return -1;
    }

    // Convert the image to grayscale
    Mat gray;
    cvtColor(image, gray, COLOR_BGR2GRAY);

    // Apply thresholding to create a binary image
    threshold(gray, gray, 0, 255, THRESH_BINARY | THRESH_OTSU);

    // Perform morphological operations to clean up the image
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(gray, gray, MORPH_OPEN, kernel, Point(-1, -1), 2);

    // Apply distance transform
    Mat dist;
    distanceTransform(gray, dist, DIST_L2, 5);

    // Normalize the distance transform
    normalize(dist, dist, 0, 1.0, NORM_MINMAX);

    // Threshold the distance transform
    threshold(dist, dist, 0.6, 1.0, THRESH_BINARY);

    // Perform a dilation to fill gaps in the regions
    dilate(dist, dist, Mat(), Point(-1, -1), 2);

    // Convert back to 8-bit image for markers
    dist *= 255;

    // Convert to 8-bit single channel
    dist.convertTo(dist, CV_8U);

    // Find contours in the distance transform
    std::vector<std::vector<Point>> contours;
    findContours(dist, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    // Create markers for watershed algorithm
    Mat markers = Mat::zeros(dist.size(), CV_32SC1);
    for (size_t i = 0; i < contours.size(); i++)
        drawContours(markers, contours, static_cast<int>(i), Scalar(static_cast<int>(i) + 1), -1);

    // Apply watershed algorithm
    watershed(image, markers);

    // Display the result
    imshow("Original Image", image);
    imshow("Watershed Result", image);
    waitKey(0);

    return 0;
}

