#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

// #include <vector>

// Global variables
Mat    g_imgColor;
bool   g_is_L_MousePressed = false;
bool   g_is_R_MousePressed = false;
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
int g_imgCenterX = img_ori.size().width/2;
int g_imgCenterY = img_ori.size().height/2;
Mat M_imgCenter = (Mat_<double>(1,3) << g_imgCenterX, g_imgCenterY, 1);

Mat crossProduct = (Mat_<double>(1,3) << 1, 1, 1);


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
        if(g_is_R_MousePressed){
            Mat vector1(g_mouseStartX - M_imgCenter.at<double>(1,1), -(g_mouseStartX - M_imgCenter.at<double>(2,1)) , 1);
            // Mat vector2(x - M_imgCenter.at<double>(1,1), -(y - M_imgCenter.at<double>(2,1)) , 1);
            // Mat vector3 = vector1.cross(vector2);
            // cout << vector3 << endl;
            // Vec3d crossProduct = cross(vector1,vector2);
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

    // right button pressed
    if (event == EVENT_RBUTTONDOWN)
    {
        // Flag on
        g_is_R_MousePressed = true;
        M_imgCenter = (Mat_<double>(3,1) << g_imgCenterX, g_imgCenterY, 1);
        gemm(M_current, M_imgCenter, 1.0, cv::Mat(), 0, M_imgCenter);

        g_mouseStartX = x;
        g_mouseStartY = y;
        
    }

    // Left button released
    if (event == EVENT_RBUTTONUP)
    {
        // Flag off
        g_is_R_MousePressed = false;
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