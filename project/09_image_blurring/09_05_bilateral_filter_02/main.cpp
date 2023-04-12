#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load color images
    Mat img = imread("texture.png");

    // Check if image loading is successful
    if (img.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Blurring
    Mat img_blur;
    blur(img, img_blur, Size(5, 5));

    // Gaussian Blurring
    Mat img_Gaussian_blur;
    GaussianBlur(img, img_Gaussian_blur, Size(5, 5), 0, 0);

    // Median blurring
    Mat img_median_blur;
    medianBlur(img, img_median_blur, 5);

    // Bilateral filter
    Mat img_bilateral;
    bilateralFilter(img, img_bilateral, 15, 75, 75);

    // Display the result
    Mat img_result;
    vector<Mat> imgs = {img, img_blur, img_Gaussian_blur, img_median_blur, img_bilateral};
    hconcat(imgs, img_result);
    imshow("Image Blurring", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}