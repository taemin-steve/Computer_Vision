#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load an image
    Mat img_color = imread("messi5.jpg");

    // Check if image loading is successful
    if (img_color.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Convert the color image to gray
    Mat img_gray;
    cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

    // Save the gray image
    imwrite("messi5_gray.jpg", img_gray);
    
    // Display both images in each window
    imshow("Color Image", img_color);
    imshow("Gray Image", img_gray);

    // Wait for a key to be pressed
    waitKey(0);

    // Destroy all windows
    destroyAllWindows();

    return 0;
}