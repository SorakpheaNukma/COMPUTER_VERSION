#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <math.h>
#include<iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
    Mat img, B;
    img = imread("images.png");
    B = img.clone();
   
    cvtColor(img, img, COLOR_BGR2GRAY);
 
    Mat circles;
    HoughCircles(img, circles, HOUGH_GRADIENT_ALT,1,50,50,0.9,10,150);

    cout << circles.type() << endl;
    cout << circles.size() << endl;
    cout << circles << endl;


    for (int i = 0; i < circles.cols; i++)
    {
        int xAxis = circles.at<Vec3f>(Point(i, 0))[0];
        int yAxis = circles.at<Vec3f>(Point(i, 0))[1];
        int radius = circles.at<Vec3f>(Point(i, 0))[2];

        circle(B, Point(xAxis, yAxis), radius, Scalar(0, 255, 255), 5);

    imshow("Pic", img);
    imshow("Cycle", B);

    waitKey(0);
    return 0;
}