#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load color images
    Mat img_park = imread("park.png");
    Mat img_tom  = imread("tom.png");

    // Check if image loading is successful
    if (img_park.empty() || img_tom.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Display the result
    Mat img_blended = img_park.clone();
    Mat img_result;
    vector<Mat> imgs = {img_park, img_blended, img_tom};
    hconcat(imgs, img_result);
    imshow("Image Blending", img_result);
    waitKey();

    // Blend two images
    for (double w = 0.0; w < 1.0; w += 0.01)
    {
        addWeighted(img_park, 1.0-w, img_tom, w, 0.0, img_blended);
        hconcat(imgs, img_result);
        imshow("Image Blending", img_result);
        waitKey(30);
    }
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}