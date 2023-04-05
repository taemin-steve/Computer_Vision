#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include "gray_histogram.hpp"

int main()
{
    // Load a grayscale image
    Mat img = imread("noisy2.png", IMREAD_GRAYSCALE);

    // Check if image loading is successful
    if (img.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Thresholded images
    Mat thresholdedImgs[3];

    // Global thresholding
    threshold(img, thresholdedImgs[0], 127, 255, THRESH_BINARY);

    // Otsu's thresholding
    threshold(img, thresholdedImgs[1], 0, 255, THRESH_BINARY+THRESH_OTSU);

    // Otsu's thresholding after Gaussian filtering
    Mat blurImg;
    GaussianBlur(img, blurImg, Size(5,5), 0);
    threshold(blurImg, thresholdedImgs[2], 0, 255, THRESH_BINARY+THRESH_OTSU);

    // Display the image and its histogram
    Mat resultImg1, resultImg2, resultImg3;
    hconcat(img,     thresholdedImgs[0], resultImg1);
    hconcat(img,     thresholdedImgs[1], resultImg2);
    hconcat(blurImg, thresholdedImgs[2], resultImg3);
    imshow("Global Thresholding", resultImg1);
    imshow("Otsu's Thresholding", resultImg2);
    imshow("Otsu's Thresholding after Smoothing", resultImg3);

    Mat resultImg4;
    hconcat(gray_histogram(img,     512, 400, Scalar(255, 0, 0)), 
            gray_histogram(blurImg, 512, 400, Scalar(0, 0, 255)),
            resultImg4);
    imshow("Histogram", resultImg4);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}