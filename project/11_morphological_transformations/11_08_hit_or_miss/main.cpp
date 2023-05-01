#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Input image
    Mat img_orig = (Mat_<uchar>(8,8) << 0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 255, 255, 255, 0, 0, 0, 255,
                                        0, 255, 255, 255, 0, 0, 0, 0,
                                        0, 255, 255, 255, 0, 255, 0, 0,
                                        0, 0, 255, 0, 0, 0, 0, 0,
                                        0, 0, 255, 0, 0, 255, 255, 0,
                                        0, 255, 0, 255, 0, 0, 255, 0,
                                        0, 255, 255, 255, 0, 0, 0, 0);

    // Kernel
    Mat kernel = (Mat_<char>(3,3) << 0, 1, 0,
                                     1, -1, 1,
                                     0, 1, 0);

    // Output
    Mat img_result;
    morphologyEx(img_orig, img_result, MORPH_HITMISS, kernel);

    // Resize
    resize(img_result, img_result, Size(800, 800), 0, 0, INTER_NEAREST);

    // Display the result
    imshow("Hit or Miss", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}