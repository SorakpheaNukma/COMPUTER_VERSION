#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main() {

	Mat A = imread("8.jpg", 1);
	Mat B = A.clone();

	Mat kenel = Mat::ones(Size(3, 3), CV_32F) / (float)(9);
	blur(A, B, Size(3, 3), Point(-1, -1), 4);

	imshow("Pic", A);
	imshow("Blur Pic", B);

	waitKey(0);
	return 0;

}