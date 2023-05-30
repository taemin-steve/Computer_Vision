#define _USE_MATH_DEFINES
#include <iostream>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

// Global variables
Mat    g_imgColor;
bool   g_is_L_MousePressed = false;
bool   g_is_R_MousePressed = false;
int    g_mouseStartX = -1;
int    g_mouseStartY = -1;

Mat M_current = (Mat_<double>(3,3) << 1,  0,  0,
                                      0,  1,  0,
                                      0,  0,  1);

// Create image
Mat img = imread("messi5.jpg");
Mat img_ori = imread("messi5.jpg");

// Center of original img
int g_imgCenterX = img_ori.size().width/2;
int g_imgCenterY = img_ori.size().height/2;

// Center of current img
Mat M_imgCenter = (Mat_<double>(1,3) << g_imgCenterX, g_imgCenterY, 1);

// Mat crossProduct = (Mat_<double>(1,3) << 1, 1, 1);


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
            Mat M_temp = (Mat_<double>(3,3) << 1,  0,  x - g_mouseStartX,
                                               0,  1,   y - g_mouseStartY,
                                               0,  0,   1);

            gemm(M_temp, M_current, 1.0, cv::Mat(), 0, M_current);
            warpAffine(img_ori, img,  M_current.rowRange(0,2), img.size());

            g_mouseStartX = x;
            g_mouseStartY = y;

            M_temp.release();
        }

        if(g_is_R_MousePressed){

            Mat vector1 = (Mat_<double>(3,1) << g_mouseStartX - M_imgCenter.at<double>(0,0), 
                                              -(g_mouseStartY - M_imgCenter.at<double>(1,0)),
                                                0);

            Mat vector2 = (Mat_<double>(3,1) << x - M_imgCenter.at<double>(0,0), 
                                              -(y - M_imgCenter.at<double>(1,0)),
                                                0);

            Mat crossProduct = vector1.cross(vector2);

            double d1 = norm(vector1);
            double d2 = norm(vector2);
            double d3 = norm(crossProduct);
        
            double degree = asin(d3 / (d1*d2))* 180.0 / M_PI;

            // cout << degree << endl;
            if(crossProduct.at<double>(2,0) > 10){

                Point2f center(M_imgCenter.at<double>(0,0),M_imgCenter.at<double>(1,0));
                Mat M_rot = getRotationMatrix2D(center, degree, 1.0);
                Mat M_temp = (Mat_<double>(3,3) << M_rot.at<double>(0,0),  M_rot.at<double>(0,1),  M_rot.at<double>(0,2),
                                                   M_rot.at<double>(1,0),  M_rot.at<double>(1,1),   M_rot.at<double>(1,2),
                                                   0,  0,   1);

                gemm(M_temp, M_current, 1.0, cv::Mat(), 0, M_current);
                warpAffine(img_ori, img,  M_current.rowRange(0,2), img.size());

                g_mouseStartX = x;
                g_mouseStartY = y;

                M_temp.release();
            }
            else if (crossProduct.at<double>(2,0) < -10)
            {
                Point2f center(M_imgCenter.at<double>(0,0),M_imgCenter.at<double>(1,0));
                Mat M_rot = getRotationMatrix2D(center, -degree, 1.0);
                Mat M_temp = (Mat_<double>(3,3) << M_rot.at<double>(0,0),  M_rot.at<double>(0,1),  M_rot.at<double>(0,2),
                                                   M_rot.at<double>(1,0),  M_rot.at<double>(1,1),   M_rot.at<double>(1,2),
                                                   0,  0,   1);

                gemm(M_temp, M_current, 1.0, cv::Mat(), 0, M_current);
                warpAffine(img_ori, img,  M_current.rowRange(0,2), img.size());

                g_mouseStartX = x;
                g_mouseStartY = y;

                M_temp.release();
            }
        }
    }

    // Left button released
    if (event == EVENT_LBUTTONUP)
    {
        // Flag off
        g_is_L_MousePressed = false;

    }

    // Mouse Wheel 
    if (event == cv::EVENT_MOUSEWHEEL)
    {
        // Handle mouse wheel event
        int delta = cv::getMouseWheelDelta(flags);
        
        // Do something with the delta value
        if (delta > 0)
        {
            Mat M_temp = (Mat_<double>(3,3) << 0.8,  0,  (0.2)*x,
                                               0,  0.8,   (0.2)*y,
                                               0,  0,   1);

            gemm(M_temp, M_current, 1.0, cv::Mat(), 0, M_current);
            warpAffine(img_ori, img,  M_current.rowRange(0,2), img.size());

            M_temp.release();
        }
        else if (delta < 0)
        {
            Mat M_temp = (Mat_<double>(3,3) << 1.2,  0,  -(0.2)*x,
                                               0,  1.2,   -(0.2)*y,
                                               0,  0,   1);
            
            gemm(M_temp, M_current, 1.0, cv::Mat(), 0, M_current);
            warpAffine(img_ori, img,  M_current.rowRange(0,2), img.size());

            M_temp.release();
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