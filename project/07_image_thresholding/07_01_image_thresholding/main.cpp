#include <iostream>
#include <string>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Create a grayscale image
    Mat img(160, 256, CV_8UC1);

    // Gradient image
    for (int i = 0; i < img.cols; i++)
    {
        img.col(i) = i;
    }

    // Image thresholding
    Mat thresholdedImgs[5];
    double thld = 127;
    double max_v = 255;
    threshold(img, thresholdedImgs[0], thld, max_v, THRESH_BINARY);
    threshold(img, thresholdedImgs[1], thld, max_v, THRESH_BINARY_INV);
    threshold(img, thresholdedImgs[2], thld, 0,     THRESH_TRUNC);
    threshold(img, thresholdedImgs[3], thld, 0,     THRESH_TOZERO);
    threshold(img, thresholdedImgs[4], thld, 0,     THRESH_TOZERO_INV);

    // Display the result
    imshow("Original Image", img);
    string strWindowNames[] = {"BINARY", "BINARY_INV", 
                               "TRUNC", 
                               "TOZERO", "TOZERO_INV"};
    for (int i = 0; i < 5; i++)
    {
        imshow(strWindowNames[i], thresholdedImgs[i]);
    }
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}