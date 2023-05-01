#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load color images
    Mat img_orig  = imread("j.png",       IMREAD_GRAYSCALE);
    Mat img_noise = imread("j_noise.png", IMREAD_GRAYSCALE);
    Mat img_holes = imread("j_holes.png", IMREAD_GRAYSCALE);

    // Check if image loading is successful
    if (img_orig.empty() || img_noise.empty() || img_holes.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }
    
    // Kernel for erosion and dilation
    Mat kernel = Mat::ones(5, 5, CV_8U);

    // Moprhoplogial transformations 
    Mat img_temp, img_result_row, img_result;

    // Row: 1
    // j
    img_orig.copyTo(img_result);

    // Erosion
    erode(img_orig, img_temp, kernel);
    hconcat(img_result, img_temp, img_result);

    // Dilation
    dilate(img_orig, img_temp, kernel);
    hconcat(img_result, img_temp, img_result);

    // Morphological gradient
    morphologyEx(img_orig, img_temp, MORPH_GRADIENT, kernel);
    hconcat(img_result, img_temp, img_result);

    // Row: 2
    // j_noise
    img_noise.copyTo(img_result_row);

    // Opening
    morphologyEx(img_noise, img_temp, MORPH_OPEN, kernel);
    hconcat(img_result_row, img_temp, img_result_row);

    // j_holes
    hconcat(img_result_row, img_holes, img_result_row);
   
    // Closing
    morphologyEx(img_holes, img_temp, MORPH_CLOSE, kernel);
    hconcat(img_result_row, img_temp, img_result_row);
    vconcat(img_result, img_result_row, img_result);

    // Row: 2
    // j_noise
    img_noise.copyTo(img_result_row);
    
    // Top Hat
    morphologyEx(img_noise, img_temp, MORPH_TOPHAT, kernel);
    hconcat(img_result_row, img_temp, img_result_row);

    // j_holes
    hconcat(img_result_row, img_holes, img_result_row);

    // Back Hat
    morphologyEx(img_holes, img_temp, MORPH_BLACKHAT, kernel);
    hconcat(img_result_row, img_temp, img_result_row);
    vconcat(img_result, img_result_row, img_result);
            
    // Display the result
    imshow("Morphological Transformations", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}