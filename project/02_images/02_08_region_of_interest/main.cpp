#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load an image
    Mat img = imread("messi5.jpg");

    // Check if image loading is successful
    if (img.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Set the region of interest
    Mat img_ROI_01 = img(Rect(338, 286, 53, 47));
    Mat img_ROI_02 = img(Rect(Point(338, 286), Point(390, 332)));

    // Display the region of interest
    imshow("Ball 1", img_ROI_01);
    imshow("Ball 2", img_ROI_02);
    waitKey(0);

    // Destroy all windows
    destroyAllWindows();

    return 0;
}