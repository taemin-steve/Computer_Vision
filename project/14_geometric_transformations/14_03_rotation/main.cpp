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

    // Rotation
    Mat M = getRotationMatrix2D(Point2f(img_orig.cols/2.f, img_orig.rows/2.f), 90, 1.0);
    
    Mat img_rotated;
    warpAffine(img_orig, img_rotated, M, img_orig.size());

    // Display the result
    Mat img_result;
    hconcat(img_orig, img_rotated, img_result);
    imshow("Rotation", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}