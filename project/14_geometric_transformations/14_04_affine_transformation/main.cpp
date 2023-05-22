#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load color images
    Mat img_orig = imread("drawing.png");

    // Check if image loading is successful
    if (img_orig.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Affine Transformation
    Point2f pts1[3] = {Point2f(50, 50), Point2f(200, 50), Point2f(50, 200)};
    Point2f pts2[3] = {Point2f(10, 100), Point2f(200, 50), Point2f(100, 250)};
    Mat M = getAffineTransform(pts1, pts2);
    
    Mat img_affined;
    warpAffine(img_orig, img_affined, M, img_orig.size());

    // Display the result
    Mat img_result;
    hconcat(img_orig, img_affined, img_result);
    imshow("Affine Transformation", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}