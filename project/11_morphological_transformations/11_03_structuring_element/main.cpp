#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Morph shapes
    int shapes[] = {MORPH_RECT, MORPH_CROSS, MORPH_ELLIPSE};

    // Draw kernels
    Mat img_result;
    for (int row = 0; row < 3; row++)
    {
        Mat img_result_row;
        for (int col = 0; col < 3; col++)
        {
            // Create a kernel
            Mat kernel = getStructuringElement(shapes[col], Size(2*col+3, 2*row+3));
            kernel *= 255; // [0, 1] -> [0, 255]

            // Horizontal concatenate
            if (img_result_row.empty()) kernel.copyTo(img_result_row);
            else                        hconcat(img_result_row, kernel, img_result_row);
        }

        // Vertical concatenate
        if (img_result.empty()) img_result_row.copyTo(img_result);
        else                    vconcat(img_result, img_result_row, img_result);
    }
            
    // Display the result
    resize(img_result, img_result, Size(600, 600), 0, 0, INTER_NEAREST);
    imshow("Structuring Element", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}