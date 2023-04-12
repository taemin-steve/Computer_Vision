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

    // Sobel
    Mat img_sobel_x, img_sobel_y;
    Sobel(img_gray, img_sobel_x, CV_64F, 1, 0);
    Sobel(img_gray, img_sobel_y, CV_64F, 0, 1);

    // Laplace
    Mat img_laplace;
    Laplacian(img_gray, img_laplace, CV_64F);

    // Take absolute values and scale
    convertScaleAbs(img_sobel_x, img_sobel_x);
    convertScaleAbs(img_sobel_y, img_sobel_y);
    convertScaleAbs(img_laplace, img_laplace);

    // Add both images
    Mat img_sobel;
    addWeighted(img_sobel_x,   1, img_sobel_y,   1, 0, img_sobel);

    // Display the result
    Mat img_result;
    hconcat(vector<Mat>({img_gray, img_sobel, img_laplace}), img_result);
    imshow("Sobel vs. Laplace", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}