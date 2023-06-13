#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load color images
    Mat img_front_view = imread("front-view.png");

    // Check if image loading is successful
    if (img_front_view.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Homography Matrix
    Mat H = (Mat_<double>(3, 3) <<  -0.04887, -0.65301, 259.102,
                                    -0.02498, -2.43859, 938.170,
                                    -0.00004, -0.00296,       1);

    Mat img_top_view;
    warpPerspective(img_front_view, img_top_view, H, Size(360,713));

    // Display the result
    Mat img_result;
    hconcat(img_front_view, img_top_view, img_result);
    resize(img_result, img_result, Size(), 0.5, 0.5);
    imshow("Front vs. Top View", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}