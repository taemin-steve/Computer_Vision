#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

// Global variables
Mat    g_imgColor;
bool   g_is_L_MousePressed = false;
int    g_mouseStartX = -1;
int    g_mouseStartY = -1;
Mat M_current = (Mat_<double>(3,3) << 1,  0,  0,
                                      0,  1,  0,
                                      0,  0,  1);

Mat M_temp = (Mat_<double>(3,3) << 1,  0,  0,
                                   0,  1,  0,
                                   0,  0,  1);

Mat M_scale = (Mat_<double>(3,3) << 1,  0,  0,
                                   0,  1,  0,
                                   0,  0,  1);
// Create image
Mat img = imread("messi5.jpg");
Mat img_ori = imread("messi5.jpg");



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
        g_is_L_MousePressed = true;
        
        // Record the mouse position
        g_mouseStartX = x;
        g_mouseStartY = y;
    }

     // Mouse move
    if (event == EVENT_MOUSEMOVE)
    {
        if(g_is_L_MousePressed){
            M_temp = (Mat_<double>(3,3) << 1,  0,  x - g_mouseStartX,
                                           0,  1,   y - g_mouseStartY,
                                           0,  0,   1);
            gemm(M_temp, M_current, 1.0, cv::Mat(), 0, M_current);
            warpAffine(img_ori, img,  M_current.rowRange(0,2), img.size());
            g_mouseStartX = x;
            g_mouseStartY = y;             
        }
    }

    // Left button released
    if (event == EVENT_LBUTTONUP)
    {
        // Flag off
        g_is_L_MousePressed = false;
        M_temp = (Mat_<double>(3,3) << 1,  0,  x - g_mouseStartX,
                                       0,  1,   y - g_mouseStartY,
                                       0,  0,   1);

        gemm(M_temp, M_current, 1.0, cv::Mat(), 0, M_current);
        warpAffine(img_ori, img,  M_current.rowRange(0,2), img.size());

    }

    // Mouse Wheel 
    if (event == cv::EVENT_MOUSEWHEEL)
    {
        // Handle mouse wheel event
        int delta = cv::getMouseWheelDelta(flags);
        
        // Do something with the delta value
        if (delta > 0)
        {
            M_temp = (Mat_<double>(3,3) << 0.8,  0,  (0.2)*x,
                                           0,  0.8,   (0.2)*y,
                                           0,  0,   1);
            gemm(M_temp, M_current, 1.0, cv::Mat(), 0, M_current);
            warpAffine(img_ori, img,  M_current.rowRange(0,2), img.size());
        }
        else if (delta < 0)
        {
            M_temp = (Mat_<double>(3,3) << 1.2,  0,  -(0.2)*x,
                                           0,  1.2,   -(0.2)*y,
                                           0,  0,   1);
            
            gemm(M_temp, M_current, 1.0, cv::Mat(), 0, M_current);
            warpAffine(img_ori, img,  M_current.rowRange(0,2), img.size());
        }
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