#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load color images
    Mat img_side_view = imread("chalk-globe-from-side.jpg");
    Mat img_front_view = imread("chalk-globe-from-front.jpg");

    // Check if image loading is successful
    if (img_side_view.empty() || img_front_view.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Homography Matrix
    Mat H = (Mat_<double>(3, 3) <<  -6.10358, -16.55199, 3487.78219,
                                    -0.37680, -2.438106, 51.4454929,
                                    -0.01474, -0.012236, 1);

    Mat img_side_view_warped;
    warpPerspective(img_side_view, img_side_view_warped, H, Size(450,300));

    // Display the result
    Mat img_result;
    hconcat(img_side_view, img_side_view_warped, img_result);
    hconcat(img_result, img_front_view, img_result);
    imshow("Side View vs. Warped Side View vs. Front View", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}