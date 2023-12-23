#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <vector>
#include <iostream>
using namespace std;
using namespace cv;
int main()
{
	Mat img = imread("7bxj7_5c.jpg"); //anh c� h�nh d?ng RGB 
	imshow("Original image", img);
	
	Mat grayImg; 
	cvtColor(img, grayImg, COLOR_BGR2GRAY); // chuy?n s�ng ?nh x�m
	imshow("Gray image", grayImg);
	
	Mat binImg;
	threshold(grayImg, binImg, 100, 255,THRESH_BINARY);// nh? ph?n h�nh ?nh 
	imshow("Binary image", binImg);
	
	vector< vector<Point> > contours;
	findContours(binImg, contours, RETR_TREE,CHAIN_APPROX_SIMPLE);
	
	//cout << "Contours number found: " << contours.size() << std::endl;
	
	/*for (int iContours = 0; iContours < contours.size(); iContours++)
	{
		std::cout << "Contour #" << iContours + 1 << ": { ";
		for (Point p : contours[iContours])
			std::cout << "( " << p.x << ", " << p.y << " ) ";
		std::cout << "}\n";
	}*/
	waitKey();
	return 0;
}