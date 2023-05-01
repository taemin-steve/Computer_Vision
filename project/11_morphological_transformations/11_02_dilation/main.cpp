#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load color images
    Mat img_orig = imread("j.png", IMREAD_GRAYSCALE);

    // Check if image loading is successful
    if (img_orig.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // For each kernel size
    Mat img_result;
    for (int kernel_size = 3; kernel_size <= 7; kernel_size+=2)
    {
        // Row image 
        Mat img_result_row = img_orig.clone();

        // For each iteration
        for (int iter = 1; iter <= 3; iter++)
        {
            // Kernel
            Mat kernel = Mat::ones(kernel_size, kernel_size, CV_8U);

            // Erosion
            Mat img_erosion;
            dilate(img_orig, img_erosion, kernel, Point(-1,-1), iter);

            // Horizontal concatenate
            hconcat(img_result_row, img_erosion, img_result_row);
        }

        // Vertical concatenate
        if (img_result.empty()) 
            img_result_row.copyTo(img_result);
        else
            vconcat(img_result, img_result_row, img_result);
    }
            
    // Display the result
    imshow("Erosion", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}