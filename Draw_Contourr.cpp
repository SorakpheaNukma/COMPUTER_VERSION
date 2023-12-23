#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;
using namespace std;
int main()
{
    Mat src;
    src = imread("BSX.jpg");
    imshow("Source", src);

    Mat Change;
    cvtColor(src, Change, COLOR_BGR2GRAY);
    imshow("Convert", Change);
  
    Mat dst;
    adaptiveThreshold(Change, dst, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, 5);
    imshow("Components", dst);

    
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    findContours(dst, contours, hierarchy,RETR_CCOMP, CHAIN_APPROX_SIMPLE);
    
    int idx = 0;
    for ( ; idx >= 0; idx = hierarchy[idx][0])
    {
        Scalar color(255); //scalar (R,G,B)
        drawContours(dst, contours, idx, color, FILLED, 8, hierarchy);
    }

    waitKey(0);
}