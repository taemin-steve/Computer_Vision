#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

// Global variables
Mat g_imgOrigin;
Mat g_imgView;
Mat g_imgCropped;
Mat g_imgResult;
vector<Point> g_points;

// Mouse callback function
void mouse_callback(int event, int x, int y, int flags, void *param)
{
    // Left button clicked
    if (event != EVENT_LBUTTONDOWN ) return;

    // If it is clicked on the original image left-hand side
    if (x >= g_imgOrigin.cols) return;

    // If four points are already selected
    if (g_points.size() == 4)
    {
        // Clear them all
        g_points.clear();

        // Copy the origin
        g_imgOrigin.copyTo(g_imgView);

        // Concatenate horizontally
        hconcat(g_imgView, g_imgCropped, g_imgResult);

        return;
    }

    // Add a point
    g_points.push_back(Point(x, y)); 

    // Draw lines
    for (size_t i = 1; i < g_points.size(); i++)
    {
        line(g_imgView, g_points[i-1], g_points[i], Scalar(255, 0, 0), 4);
    }

    // Draw points
    for (size_t i = 0; i < g_points.size(); i++)
    {
        circle(g_imgView, g_points[i], 6, Scalar(0, 0, 255), -1);
    }

    // If four points are selected
    if (g_points.size() == 4)
    {
        // Draw the final line
        line(g_imgView, g_points[3], g_points[0], Scalar(255, 0, 0), 4);

        // Draw the first and last circle again
        circle(g_imgView, g_points[3], 6, Scalar(0, 0, 255), -1);
        circle(g_imgView, g_points[0], 6, Scalar(0, 0, 255), -1);
 
        // Find Homography
        int newWidth  = g_imgOrigin.rows * 16/9;
        int newHeight = g_imgOrigin.rows;
        vector<Point> newPoints({Point(0, 0), Point(newWidth, 0), 
                                 Point(newWidth, newHeight), Point(0, newHeight)});
        Mat H = findHomography(g_points, newPoints);

        // Warp the original image
        warpPerspective(g_imgOrigin, g_imgCropped, H, Size(newWidth, newHeight));
    }                      

    // Concatenate horizontally
    hconcat(g_imgView, g_imgCropped, g_imgResult);
}

int main()
{
    // Load a color image
    g_imgOrigin = imread("name_card.jpg");

    // Check if image loading is successful
    if (g_imgOrigin.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Copy the original image
    g_imgOrigin.copyTo(g_imgView);
    g_imgCropped = Mat::zeros(g_imgOrigin.rows, g_imgOrigin.rows * 16/9, CV_8UC3);

    // Add a text
    int font = FONT_HERSHEY_SIMPLEX;
    putText(g_imgCropped, "Select 4 Corners Clockwise From TL", Point(20, g_imgOrigin.rows/2), font, 1, Scalar(255,255,255), 2, LINE_AA);
    hconcat(g_imgView, g_imgCropped, g_imgResult);

    // Create a window
    String strWindowName = "Homography";
    namedWindow(strWindowName);

    // Register the mouse callback function
    setMouseCallback(strWindowName, mouse_callback);

    // Infinite loop
    while (true)
    {
        // Display the image
        imshow(strWindowName, g_imgResult);

        // Get user input
        char key = waitKey(1);

        // ESC
        if (key == 27) break;
    }

    // Destroy all windows
    destroyAllWindows();

    return 0;
}