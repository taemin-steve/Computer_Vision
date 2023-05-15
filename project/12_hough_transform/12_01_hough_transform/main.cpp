#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load color images
    Mat img_color = imread("sudoku.png");

    // Check if image loading is successful
    if (img_color.empty())
    {
        cout << "Error: No image exists!" << endl;
        exit(-1);
    }

    // Convert to a gray
    Mat img_gray;
    cvtColor(img_color, img_gray, COLOR_BGR2GRAY);

    // Find Canny edges
    Mat img_edge;
    Canny(img_gray, img_edge, 50, 150);

    // Find Hough lines
    vector<Vec2f> lines;
    HoughLines(img_edge, lines, 1, CV_PI/180, 200);

    // Draw lines
    Mat img_lines = img_color.clone();
    for (size_t i = 0; i < lines.size(); i++)
    {
        // rho and theta
        float rho   = lines[i][0]; // distance from the origin
        float theta = lines[i][1]; // angle from the x-axis

        Point pt1, pt2;
        double cos_theta = cos(theta);
        double sin_theta = sin(theta);
        double x0 = rho * cos_theta;
        double y0 = rho * sin_theta;
        pt1.x = cvRound(x0 + 1000 * (-sin_theta));
        pt1.y = cvRound(y0 + 1000 * ( cos_theta));
        pt2.x = cvRound(x0 - 1000 * (-sin_theta));
        pt2.y = cvRound(y0 - 1000 * ( cos_theta));
        line(img_lines, pt1, pt2, Scalar(0,0,255), 2);
    }
     
    // Display the result
    Mat img_edge_color;
    cvtColor(img_edge, img_edge_color, COLOR_GRAY2BGR);
    Mat img_result;
    hconcat(img_color, img_edge_color, img_result);
    hconcat(img_result, img_lines, img_result);
    imshow("Original vs. Canny Edges vs. Hough Lines", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}