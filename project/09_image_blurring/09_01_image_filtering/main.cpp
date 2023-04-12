#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load color images
    Mat img = imread("opencv_logo.jpg");

    // Check if image loading is successful
    if (img.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Kernel
    Mat kernel = Mat::ones(5, 5, CV_32F) / (float) 25;

    // Image Filtering
    Mat img_filtered;
    filter2D(img, img_filtered, -1, kernel);

    // Display the result
    Mat img_result;
    hconcat(img, img_filtered, img_result);
    imshow("Image Filtering", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}