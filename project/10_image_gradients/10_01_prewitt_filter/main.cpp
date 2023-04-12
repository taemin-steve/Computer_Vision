#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load color images
    Mat img_gray = imread("lena.jpg", IMREAD_GRAYSCALE);

    // Check if image loading is successful
    if (img_gray.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Prewitt Kernels
    Mat prewitt_x = (Mat_<double>(3,3) << -1,  0,  1,
                                          -1,  0,  1,
                                          -1,  0,  1);
    Mat prewitt_y = (Mat_<double>(3,3) << -1, -1, -1, 
                                           0,  0,  0,
                                           1,  1,  1);

    // Image Filtering
    Mat img_prewitt_x, img_prewitt_y;
    filter2D(img_gray, img_prewitt_x, -1, prewitt_x);
    filter2D(img_gray, img_prewitt_y, -1, prewitt_y);

    // Take absolute values and scale
    convertScaleAbs(img_prewitt_x, img_prewitt_x);
    convertScaleAbs(img_prewitt_y, img_prewitt_y);

    // Add both images
    Mat img_prewitt;
    addWeighted(img_prewitt_x, 1, img_prewitt_y, 1, 0, img_prewitt);

    // Display the result
    Mat img_result_01, img_result_02, img_result;
    hconcat(img_gray, img_prewitt, img_result_01);
    hconcat(img_prewitt_x, img_prewitt_y, img_result_02);
    vconcat(img_result_01, img_result_02, img_result);
    imshow("Prewitt Filter", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}