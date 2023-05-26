#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

// Global variables
Mat    g_imgColor;
bool   g_is_L_MousePressed = false; // check does mouse clicked 
int    g_mouseStartX = -1;
int    g_mouseStartY = -1;
Scalar color; // for share color in events

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

        //set color when we press mouse left button
        color = randomColor(g_rng);
    }

    // Mouse move
    if (event == EVENT_MOUSEMOVE)
    {
        if(g_is_L_MousePressed){
            //draw all 
            rectangle(g_imgColor, Point(g_mouseStartX, g_mouseStartY), Point(x, y), color, -1);
        }
    }

    // Left button released
    if (event == EVENT_LBUTTONUP)
    {
        // Flag off
        g_is_L_MousePressed = false;

        // Draw a rectangle
        rectangle(g_imgColor, Point(g_mouseStartX, g_mouseStartY), Point(x, y), color, -1);
    }
    

}

int main()
{
    // Create a black image
    const int rows = 480;
    const int cols = 640;
    g_imgColor = Mat::zeros(rows, cols, CV_8UC3);

    // Create a window
    String strWindowName = "Mouse Events";
    namedWindow(strWindowName);

    // Register the mouse callback function
    setMouseCallback(strWindowName, mouse_callback);

    // Infinite loop
    while (true)
    {
        // Display the image
        imshow(strWindowName, g_imgColor);

        // Get user input
        char key = waitKey(1);

        // ESC
        if (key == 27) break;
    }

    // Destroy all windows
    destroyAllWindows();

    return 0;
}