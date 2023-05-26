#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

// Global variables
Mat    g_imgColor;
bool   g_isMousePressed = false;
int    g_mouseStartX = -1;
int    g_mouseStartY = -1;
Mat M = (Mat_<double>(2,3) << 1,  0,  0,
                              0,  1,  0);

// Create image
Mat img = imread("messi5.jpg");


// OpenCV Random Number Generator
RNG g_rng(getTickCount());
Scalar randomColor(RNG &g_rng)
{
    int icolor = (unsigned) g_rng;
    return Scalar(icolor&255, (icolor>>8)&255, (icolor>>16)&255);
}

// Mouse callback function
void mouse_callback(int event, int x, int y, int flags, void *param)
{
    // Left button pressed
    if (event == EVENT_LBUTTONDOWN)
    {
        // Flag on
        g_isMousePressed = true;
        
        // Record the mouse position
        g_mouseStartX = x;
        g_mouseStartY = y;
    }

    // Left button released
    if (event == EVENT_LBUTTONUP)
    {
        // Flag off
        g_isMousePressed = false;
        M = (Mat_<double>(2,3) << 1,  0,  x - g_mouseStartX ,
                                  0,  1,   y - g_mouseStartY );

        warpAffine(img, img, M, img.size());

    }
}

int main()
{
    // Create a window
    String strWindowName = "Mouse Events";
    namedWindow(strWindowName);

    // Register the mouse callback function
    setMouseCallback(strWindowName, mouse_callback);

    // Infinite loop
    while (true)
    {
        // Display the image
        imshow(strWindowName, img);
        // Get user input
        char key = waitKey(1);

        // ESC
        if (key == 27) break;
    }

    // Destroy all windows
    destroyAllWindows();

    return 0;
}