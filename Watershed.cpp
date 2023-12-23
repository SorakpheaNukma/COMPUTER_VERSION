#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main()
{
    Mat src = imread("7bxj7_5c.jpg");
    if (src.empty())
        return -1;

    imshow("src", src);

    // Convert the image to grayscale
    Mat gray;
    cvtColor(src, gray, COLOR_BGR2GRAY);

    // Apply GaussianBlur to reduce noise and improve results
    GaussianBlur(gray, gray, Size(3, 3), 0);

    // Threshold the image to create a binary image
    Mat binary;
    threshold(gray, binary, 40, 255, THRESH_BINARY);
    imshow("Binary Image", binary);

    // Perform the distance transform algorithm
    Mat dist;
    distanceTransform(binary, dist, DIST_L2, 3);

    // Normalize the distance image for range = {0.0, 1.0}
    normalize(dist, dist, 0, 1., NORM_MINMAX);
    imshow("Distance Transform", dist);

    // Threshold to obtain the peaks
    threshold(dist, dist, 0.5, 1., THRESH_BINARY);
    imshow("Peaks", dist);

    // Create the CV_8U version of the distance image
    Mat dist_8u;
    dist.convertTo(dist_8u, CV_8U);

    // Find contours
    vector<vector<Point>> contours;
    findContours(dist_8u, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    int ncomp = contours.size();

    cout << "Number of coins: " << ncomp << endl;

    // Create the marker image for the watershed algorithm
    Mat markers = Mat::zeros(dist.size(), CV_32S);

    // Draw the foreground markers
    for (int i = 0; i < ncomp; i++)
        drawContours(markers, contours, i, Scalar::all(i + 1), -1);


    // Perform the watershed algorithm
    watershed(src, markers);

    // Generate random colors
    vector<Vec3b> colors;
    for (int i = 0; i < ncomp; i++)
    {
        int b = theRNG().uniform(0, 255);
        int g = theRNG().uniform(0, 255);
        int r = theRNG().uniform(0, 255);

        colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
    }

    // Create the result image
    Mat dst = Mat::zeros(markers.size(), CV_8UC3);

    // Fill labeled objects with random colors
    for (int i = 0; i < markers.rows; i++)
    {
        for (int j = 0; j < markers.cols; j++)
        {
            int index = markers.at<int>(i, j);
            if (index > 0 && index <= ncomp)
                dst.at<Vec3b>(i, j) = colors[index - 1];
            else
                dst.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
        }
    }

    imshow("Result", dst);
    waitKey(0);

    return 0;
}
