#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include<iostream>

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
    Mat src, dst, color_dst;
    src = imread("duong-bang-san-bay-1.jpg");
    dst = src.clone();


    Canny(src, dst, 80, 200, 3);
    cvtColor(dst, color_dst, COLOR_GRAY2BGR);
    vector<Vec4i> lines;
    HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 30, 10);
    for (size_t i = 0; i < lines.size(); i++)
    {
        line(color_dst, Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 3, 8);
    }
    namedWindow("Source", 1);
    imshow("Source", src);
    namedWindow("Detected Lines", 1);
    imshow("Detected Lines", color_dst);

    waitKey(0);
    return 0;
}