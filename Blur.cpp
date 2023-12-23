#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main() {

	Mat A = imread("8.jpg", 1);
	Mat B = A.clone();



	imshow("Pic", A);
	imshow("Blur Pic", B);
	waitKey(0);
	return 0;

}