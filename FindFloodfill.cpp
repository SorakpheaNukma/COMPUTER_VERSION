#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <vector>
#include <iostream>

using namespace cv;
using namespace std;

struct Blob
{
    Size matContainSize;
    Rect boundingRect;
    vector<Point2i> points;
    Blob() {};
};

vector<Blob> FindBlobs(Mat& matBinary, Size minSize, Size maxSize)
{
    assert(matBinary.channels() == 1, "Image is not binary");//check kênh màu

    vector<Blob> blobs;

    uchar label_count = 2;

    for (int y = 0; y < matBinary.rows; y++)//quét và l?y t?ng giá tr? ?i?m ?nh
    {
        for (int x = 0; x < matBinary.cols; x++)
        {
            uchar val = matBinary.at<uchar>(y, x);
            if (val != 255)
                continue;

            Rect rect;
            floodFill(matBinary, Point(x, y), ++label_count, &rect);//tìm và ??m s? ?i?m ?ã fill màu
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
    Mat image = imread("BSX.jpg"); //??c m?t ?nh màu 
    Mat a = image.clone();
    cvtColor(image, image, COLOR_BGR2GRAY); //chuy?n sáng ?nh xám 
    threshold(image, image, 127, 255, THRESH_BINARY); // chuy?n sáng nh? phân 


    bitwise_not(image, image); // ??o ng??c màu s?c trong ?nh nh? phân
    imshow("threshold", image);

    vector<Blob> blobs = FindBlobs(image, Size(1, 1), Size(500, 500));


    Mat result = Mat::zeros(image.size(), CV_8UC3);//kênh 3 màu RGB
    Scalar color1(0, 0, 255);  // red 
    Scalar color2(0, 255, 0);  // green 
    Scalar color3(255, 0, 0);  // blue 

    for (size_t i = 0; i < blobs.size(); i++)
    {
        Scalar color;

        if (i % 3 == 0)
            color = color1;
        else if (i % 3 == 1)
            color = color2;
        else
            color = color3;
        for (size_t j = 0; j < blobs[i].points.size(); j++)
        {
            result.at<Vec3b>(blobs[i].points[j]) = Vec3b(color[0], color[1], color[2]);
        }
    }

    imshow("Result Image", result);
    imshow("Original Pic", a);
    waitKey(0);
    return 0;
}
