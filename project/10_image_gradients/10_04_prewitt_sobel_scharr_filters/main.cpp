#include <iostream>
#include <vector>
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

    // Prewitt
    Mat prewitt_x = (Mat_<double>(3,3) << -1,  0,  1,
                                          -1,  0,  1,
                                          -1,  0,  1);
    Mat prewitt_y = (Mat_<double>(3,3) << -1, -1, -1, 
                                           0,  0,  0,
                                           1,  1,  1);
    Mat img_prewitt_x, img_prewitt_y;
    filter2D(img_gray, img_prewitt_x, -1, prewitt_x);
    filter2D(img_gray, img_prewitt_y, -1, prewitt_y);

    // Sobel
    Mat img_sobel_x, img_sobel_y;
    Sobel(img_gray, img_sobel_x, CV_64F, 1, 0);
    Sobel(img_gray, img_sobel_y, CV_64F, 0, 1);

    // Scharr
    Mat img_scharr_x, img_scharr_y;
    Scharr(img_gray, img_scharr_x, CV_64F, 1, 0);
    Scharr(img_gray, img_scharr_y, CV_64F, 0, 1);

    // Take absolute values and scale
    convertScaleAbs(img_prewitt_x, img_prewitt_x);
    convertScaleAbs(img_prewitt_y, img_prewitt_y);
    convertScaleAbs(img_sobel_x,   img_sobel_x);
    convertScaleAbs(img_sobel_y,   img_sobel_y);
    convertScaleAbs(img_scharr_x,  img_scharr_x);
    convertScaleAbs(img_scharr_y,  img_scharr_y);

    // Add both images
    Mat img_prewitt, img_sobel, img_scharr;
    addWeighted(img_prewitt_x, 1, img_prewitt_y, 1, 0, img_prewitt);
    addWeighted(img_sobel_x,   1, img_sobel_y,   1, 0, img_sobel);
    addWeighted(img_scharr_x,  1, img_scharr_y,  1, 0, img_scharr);

    // Display the result
    Mat img_result_01, img_result_02, img_result_03, img_result;
    hconcat(vector<Mat>({img_gray, img_prewitt_x, img_prewitt_y, img_prewitt}), img_result_01);
    hconcat(vector<Mat>({img_gray, img_sobel_x,   img_sobel_y,   img_sobel}),   img_result_02);
    hconcat(vector<Mat>({img_gray, img_scharr_x,  img_scharr_y,  img_scharr}),  img_result_03);
    vconcat(vector<Mat>({img_result_01, img_result_02, img_result_03}),  img_result);
    imshow("Prewitt vs. Sobel vs. Scharr", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}