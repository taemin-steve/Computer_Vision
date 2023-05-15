#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // Load color images
    Mat img_color = imread("building.jpg");

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
    Canny(img_gray, img_edge, 50, 200);

    // Find Hough lines
    vector<Vec4i> lines;
    HoughLinesP(img_edge, lines, 1, CV_PI/180, 80, 30, 10);

    // Draw lines
    Mat img_lines = img_color.clone();
    for (size_t i = 0; i < lines.size(); i++)
    {
        Vec4i l = lines[i];
		line(img_lines, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2);
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