#include <iostream>
#include <string>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Files
    String file_names[] ={"box.png", "white_circle.png", "lena.jpg"};

    // for each file
    for (int i = 0; i < 3; i++)
    {
        // Load color images
        Mat img_gray = imread(file_names[i], IMREAD_GRAYSCALE);

        // Check if image loading is successful
        if (img_gray.empty())
        {
            cout << "Error: No image exists!" << endl;
            exit(-1);
        }

        // Apply Sobel filters
        Mat img_sobel_x, img_sobel_y;
        Sobel(img_gray, img_sobel_x, CV_64F, 1, 0);
        Sobel(img_gray, img_sobel_y, CV_64F, 0, 1);

        // Take absolute values and scale
        convertScaleAbs(img_sobel_x, img_sobel_x);
        convertScaleAbs(img_sobel_y, img_sobel_y);

        // Add both images
        Mat img_sobel;
        addWeighted(img_sobel_x, 1, img_sobel_y, 1, 0, img_sobel);

        // Display the result
        Mat img_result_01, img_result_02, img_result;
        hconcat(img_gray, img_sobel, img_result_01);
        hconcat(img_sobel_x, img_sobel_y, img_result_02);
        vconcat(img_result_01, img_result_02, img_result);
        imshow("Sobel Filter", img_result);
        waitKey();

        // Destroy all windows
        destroyAllWindows();
    }

    return 0;
}