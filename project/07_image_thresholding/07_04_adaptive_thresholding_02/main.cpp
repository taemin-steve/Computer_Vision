#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load a grayscale image
    Mat img_gray = imread("book-scan.png", IMREAD_GRAYSCALE);

    // Check if image loading is successful
    if (img_gray.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Threshold the image
    Mat img_results[3];
    threshold(img_gray, img_results[0], 127, 255, THRESH_BINARY);
    adaptiveThreshold(img_gray, img_results[1], 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 21, 5);
    adaptiveThreshold(img_gray, img_results[2], 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 21, 5);

    imshow("Original Image",                   img_gray);
    imshow("Global Thresholding",              img_results[0]);
    imshow("Adaptive Thresholding - Mean",     img_results[1]);
    imshow("Adaptive Thresholding - Gaussian", img_results[2]);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}