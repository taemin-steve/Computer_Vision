#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load color images
    Mat img_color = imread("opencv-logo-white.png");

    // Check if image loading is successful
    if (img_color.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Convert to a gray
    Mat img_gray;
    cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

    // Blur the image
    Mat img_blur;
    medianBlur(img_gray, img_blur, 5);

    // Find Hough circles
    vector<Vec3f> circles;
    HoughCircles(img_blur, circles, HOUGH_GRADIENT, 1, 20, 50, 25);

    // Draw circles
    Mat img_circles = img_color.clone();
    for (size_t i = 0; i < circles.size(); i++)
    {
        Vec3i c = circles[i];
		circle(img_circles, Point(c[0], c[1]), c[2], Scalar(0, 255, 0), 2);
        circle(img_circles, Point(c[0], c[1]), 2, Scalar(0, 0, 255), 3);
    }
     
    // Display the result
    imshow("Hough Circles", img_circles);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}