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

    // Translation
    Mat M = (Mat_<double>(2,3) << 1,  0,  100,
                                  0,  1,   50);
    
    Mat img_translated;
    warpAffine(img_orig, img_translated, M, img_orig.size());

    // Display the result
    Mat img_result;
    hconcat(img_orig, img_translated, img_result);
    imshow("Translation", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}