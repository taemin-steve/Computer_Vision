#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

// Global variables
Mat    g_imgColor; // base
Mat    g_imgColor_copy; // for mouse up
Mat    g_imgColor_temp; // for mouse move

bool   g_isMousePressed = false; // check does mouse clicked 
bool   is_ellipse = false;
int    g_mouseStartX = -1;
int    g_mouseStartY = -1;
int    cnt;
Scalar color; // for share color in events

Point2f center;
Size axes;

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

        //set color when we press mouse left button
        color = randomColor(g_rng);
    }

    // Mouse move
    if (event == EVENT_MOUSEMOVE)
    {
        if(g_isMousePressed){
            //draw all 
            g_imgColor_temp = g_imgColor_copy.clone(); //Copy imgColor before Mouseup event 
            if(cnt%3 == 0){
                rectangle(g_imgColor_temp, Point(g_mouseStartX, g_mouseStartY), Point(x, y), color, -1);
                g_imgColor = g_imgColor_temp.clone(); // draw new imgColor
            }
            else if(cnt%3 == 1){
                ellipse(g_imgColor_temp, Point(abs(g_mouseStartX + x)/2,abs(g_mouseStartY + y)/2), Point(abs(g_mouseStartX -x)/2,abs(g_mouseStartY - y)/2), 0, 0, 360, color, FILLED);
                g_imgColor = g_imgColor_temp.clone(); // draw new imgColor
            }
            else{
                circle(g_imgColor, Point(x, y), 5, color, -1);
            }
        }
    }

    // Left button released
    if (event == EVENT_LBUTTONUP)
    {
        // Flag off
        g_isMousePressed = false;

        // Draw a rectangle
        if(cnt%3 == 0){
            rectangle(g_imgColor, Point(g_mouseStartX, g_mouseStartY), Point(x, y), color, -1);
            g_imgColor_copy = g_imgColor.clone(); // update g_imgColor_copy
            }
        else if(cnt%3 == 1){
            ellipse(g_imgColor, Point(abs(g_mouseStartX + x)/2,abs(g_mouseStartY + y)/2), Point(abs(g_mouseStartX -x)/2,abs(g_mouseStartY - y)/2), 0, 0, 360, color, FILLED);
            g_imgColor_copy = g_imgColor.clone(); // update g_imgColor_copy
        }
        else{
            circle(g_imgColor, Point(x, y), 5, color, -1);
            g_imgColor_copy = g_imgColor.clone(); // update g_imgColor_copy
        }
    }
    

}

int main()
{
    // Create a black image
    const int rows = 480;
    const int cols = 640;
    g_imgColor = Mat::zeros(rows, cols, CV_8UC3);
    g_imgColor_copy = Mat::zeros(rows, cols, CV_8UC3);
    g_imgColor_temp = Mat::zeros(rows, cols, CV_8UC3);
    // Create a window
    String strWindowName = "Mouse Events";
    namedWindow(strWindowName);

    // Register the mouse callback function
    setMouseCallback(strWindowName, mouse_callback);

    // Infinite loop
    bool quit = false;
    while (!quit)
    {
        // Display the image
        imshow(strWindowName, g_imgColor);

        // Get user input
        char key = waitKey(1);
        switch (key)
        {
            // Flip aroun the x-axis: vertically
            case 'm':
                cnt++;
                break;
            
            // ESC
            case 27:
                quit = true;
                break;
        }

    }

    // Destroy all windows
    destroyAllWindows();

    return 0;
}