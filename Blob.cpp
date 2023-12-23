#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <vector>
#include <iostream>

using namespace std;
using namespace cv;

struct Blob
{
	cv::Size matContainSize;
	cv::Rect boundingRect;
	std::vector<cv::Point2i> points;

	Blob(Blob* b);
	Blob() {};
};

vector<Blob> FindBlobs(cv::Mat& matBinary, cv::Size minSize, cv::Size maxSize)
{
	assert(matBinary.channels() == 1, "Image is not binary");


	std::vector<Blob> blobs;

	// Fill the label_image with the blobs
	// 0  - background
	// 1  - unlabelled foreground
	// 2+ - labelled foreground

	uchar label_count = 2; // starts at 2 because 0,1 are used already

	for (int y = 0; y < matBinary.rows; y++)
	{
		for (int x = 0; x < matBinary.cols; x++)
		{
			uchar val = matBinary.at<uchar>(y, x);
			if (val != 255)
				continue;

			cv::Rect rect;
			cv::floodFill(matBinary, cv::Point(x, y), ++label_count, &rect);
			if (label_count == 255)
				label_count = 2;

			if (minSize.area() > 0 && (rect.width < minSize.width || rect.height < minSize.height))
				continue;

			if (maxSize.area() > 0 && (rect.width > maxSize.width || rect.height > maxSize.height))
				continue;

			Blob blob;

			for (int i = rect.y; i < (rect.y + rect.height); i++)
			{
				for (int j = rect.x; j < (rect.x + rect.width); j++)
				{
					if (matBinary.at<uchar>(i, j) == label_count)
						blob.points.push_back(cv::Point2i(j, i));
				}
			}

			if (blob.points.size() == 0)
				continue;

			blob.boundingRect = rect;
			blob.matContainSize = matBinary.size();
			blobs.push_back(blob);

		}
	}

	return blobs;
}

int main()
{
	// Load the image
	Mat image = cv::imread("BSX.jpg", cv::IMREAD_GRAYSCALE);

	// Binary threshold the image (adjust threshold value as needed)
	Mat binaryImage;
	threshold(image, binaryImage, 128, 255, THRESH_BINARY);

	// Define minSize and maxSize parameters
	Size minSize(30, 30);
	Size maxSize(500, 500);

	// Find blobs
	vector<Blob> blobs = FindBlobs(binaryImage, minSize, maxSize);

	// Display the original image
	imshow("Original Image", image);

	// Display the binary image
	imshow("Binary Image", binaryImage);

	// Draw bounding rectangles around blobs on the original image
	for (const auto& blob : blobs)
	{
		cv::rectangle(image, blob.boundingRect, Scalar(255, 0, 200), 2);
	}

	// Display the image with bounding rectangles
	imshow("Image with Blobs", image);

	// Wait for a key press
	waitKey(0);

	return 0;
}
