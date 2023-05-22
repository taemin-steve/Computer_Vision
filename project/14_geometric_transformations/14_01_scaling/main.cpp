#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load color images
    Mat img_orig = imread("messi5.jpg");

    // Check if image loading is successful
    if (img_orig.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Scale-down
    vector<Mat> img_half(4);
    resize(img_orig, img_half[0], Size(), 0.5, 0.5, INTER_NEAREST);
    resize(img_orig, img_half[1], Size(), 0.5, 0.5, INTER_LINEAR);
    resize(img_orig, img_half[2], Size(), 0.5, 0.5, INTER_CUBIC);
    resize(img_orig, img_half[3], Size(), 0.5, 0.5, INTER_AREA);

    // Display the result

    // Scale-up
    vector<Mat> img_double(3);
    resize(img_half[3], img_double[0], Size(), 2, 2, INTER_NEAREST);
    resize(img_half[3], img_double[1], Size(), 2, 2, INTER_LINEAR);
    resize(img_half[3], img_double[2], Size(), 2, 2, INTER_CUBIC);

    // Display the result
    Mat img_row_01, img_row_02, img_result_half, img_result_double;

    hconcat(img_half[0], img_half[1], img_row_01);
    hconcat(img_half[2], img_half[3], img_row_02);
    vconcat(img_row_01, img_row_02, img_result_half);

    hconcat(img_orig,      img_double[0], img_row_01);
    hconcat(img_double[1], img_double[2], img_row_02);
    vconcat(img_row_01, img_row_02, img_result_double);

    imshow("Scale-down", img_result_half);
    imshow("Scale-up", img_result_double);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}