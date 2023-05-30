#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

// Global variables
Mat    g_imgColor;
bool   g_is_L_MousePressed = false;
int    g_mouseStartX = -1;
int    g_mouseStartY = -1;

// Create image
Mat img = imread("messi5.jpg");

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
            //make matrix
            Mat M_temp = (Mat_<double>(3,3) << 1,  0,  x - g_mouseStartX,
                                               0,  1,   y - g_mouseStartY,
                                               0,  0,   1);
            //use only 0,1 rows for wrapAffine
            warpAffine(img, img, M_temp.rowRange(0,2), img.size());
            //reset Mouse start pos
            g_mouseStartX = x;
            g_mouseStartY = y;

            M_temp.release();            
        }
    }

    // Left button released
    if (event == EVENT_LBUTTONUP)
    {
        // Flag off
        g_is_L_MousePressed = false;

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