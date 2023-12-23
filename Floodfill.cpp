#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <vector>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
	Mat img = imread("draw.png",IMREAD_GRAYSCALE); //anh có hình d?ng RGB 
	Mat dst = img.clone();
	
	Mat mask;
	Rect r;
	
	floodFill(dst, Point(150, 100), Scalar(125),&r, Scalar(100),Scalar(100),FLOODFILL_FIXED_RANGE);
//foodFill(dst, Point(100, 100), Scalar(125));
	
	imshow("Original image", img);
	imshow("Floodfill", dst);
	waitKey();
	return 0;
}