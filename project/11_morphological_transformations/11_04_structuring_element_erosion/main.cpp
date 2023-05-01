#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load color images
    Mat img_orig = imread("j.png", IMREAD_GRAYSCALE);

    // Check if image loading is successful
    if (img_orig.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }
    
    // Morph shapes
    int shapes[] = {MORPH_RECT, MORPH_CROSS, MORPH_ELLIPSE};

    // Draw kernels
    Mat img_result;
    for (int shape = 0; shape < 3; shape++)
    {
        // Row image 
        Mat img_result_row = img_orig.clone();

        for (int size = 3; size <=7; size += 2)
        {
            // Create a kernel
            Mat kernel = getStructuringElement(shapes[shape], Size(size, size));
            
            // Erosion
            Mat img_erosion;
            erode(img_orig, img_erosion, kernel);

            // Horizontal concatenate
            hconcat(img_result_row, img_erosion, img_result_row);
        }

        // Vertical concatenate
        if (img_result.empty()) img_result_row.copyTo(img_result);
        else                    vconcat(img_result, img_result_row, img_result);
    }
            
    // Display the result
    imshow("Erosion", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}