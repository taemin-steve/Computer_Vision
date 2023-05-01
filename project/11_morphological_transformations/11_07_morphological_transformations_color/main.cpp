#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load color images
    Mat img_orig  = imread("lena.jpg");

    // Check if image loading is successful
    if (img_orig.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }
    
    // Kernel for erosion and dilation
    Mat kernel = Mat::ones(5, 5, CV_8U);

    // Moprhoplogial transformations 
    Mat img_temp, img_result_row, img_result;

    // Row: 1
    // lena
    img_orig.copyTo(img_result);

    // Erosion
    erode(img_orig, img_temp, kernel);
    hconcat(img_result, img_temp, img_result);

    // Dilation
    dilate(img_orig, img_temp, kernel);
    hconcat(img_result, img_temp, img_result);

    // Row: 2
    // lena
    img_orig.copyTo(img_result_row);

    // Opening
    morphologyEx(img_orig, img_temp, MORPH_OPEN, kernel);
    hconcat(img_result_row, img_temp, img_result_row);
  
    // Closing
    morphologyEx(img_orig, img_temp, MORPH_CLOSE, kernel);
    hconcat(img_result_row, img_temp, img_result_row);
    vconcat(img_result, img_result_row, img_result);

    // Row: 2
    // lena
    img_orig.copyTo(img_result_row);
    
    // Top Hat
    morphologyEx(img_orig, img_temp, MORPH_TOPHAT, kernel);
    hconcat(img_result_row, img_temp, img_result_row);

    // Back Hat
    morphologyEx(img_orig, img_temp, MORPH_BLACKHAT, kernel);
    hconcat(img_result_row, img_temp, img_result_row);
    vconcat(img_result, img_result_row, img_result);
            
    // Display the result
    imshow("Morphological Transformations", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}