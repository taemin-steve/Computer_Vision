#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load a grayscale image
    Mat img_gray = imread("sudoku.png", IMREAD_GRAYSCALE);

    // Check if image loading is successful
    if (img_gray.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Blur the image
    Mat img_blurred;
    medianBlur(img_gray, img_blurred, 5);

    Mat img_result1;
    hconcat(img_gray, img_blurred, img_result1);
    imshow("Origival vs. Blurred", img_result1);

    // Threshold the image
    vector<Mat> img_results(3);
    threshold(img_blurred, img_results[0], 127, 255, THRESH_BINARY);
    adaptiveThreshold(img_blurred, img_results[1], 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 11, 2);
    adaptiveThreshold(img_blurred, img_results[2], 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 11, 2);

    Mat img_result2;
    hconcat(img_results, img_result2);
    imshow("Thresholded Images", img_result2);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}