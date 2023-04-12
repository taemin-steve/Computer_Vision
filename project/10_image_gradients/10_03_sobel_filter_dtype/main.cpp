#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load color images
    Mat img_gray = imread("box.png", IMREAD_GRAYSCALE);

    // Check if image loading is successful
    if (img_gray.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Apply Sobel filters
    Mat img_sobel_x_8U, img_sobel_y_64F;
    Sobel(img_gray, img_sobel_x_8U,  CV_8U,  1, 0);
    Sobel(img_gray, img_sobel_y_64F, CV_64F, 1, 0);

    // Take absolute values and scale
    convertScaleAbs(img_sobel_x_8U,  img_sobel_x_8U);
    convertScaleAbs(img_sobel_y_64F, img_sobel_y_64F);

    // Display the result
    Mat img_result;
    hconcat(vector<Mat>({img_gray, img_sobel_x_8U, img_sobel_y_64F}), img_result);
    imshow("Sobel Filter - Image Depth", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}