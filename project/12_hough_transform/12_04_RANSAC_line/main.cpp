#include <iostream>
#include <vector>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

#include "normalized_line.hpp"

// OpenCV Random Number Generator
RNG g_rng(getTickCount());

void select_two_random_samples(const int n, int &i, int &j)
{
    i = g_rng.uniform(0, n-1);
    do
    {
        j = g_rng.uniform(0, n-1);
    } while (i == j);
}

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

    // Collect edge points
    vector<Point> edge_points;    
    findNonZero(img_edge, edge_points);
    const int NUM_SAMPLES = edge_points.size();

    // For each iteration,       
    const int MAX_ITER = 10000;
    const double MAX_DISTANCE = 2;
    const int MIN_CONCENSUS = 400;

    vector<Normalized_Line> lines;
    for (int iter = 0; iter < MAX_ITER; iter++)
    {
        // Select two random samples
        int idx1, idx2;
        select_two_random_samples(NUM_SAMPLES, idx1, idx2);
        
        // Fit a line: ax + by + c = 0;
        Normalized_Line line;
        if (!line.fit(edge_points[idx1], edge_points[idx2])) continue;

        // For each data sample,
        int num_inliers = 0;
        for (int i = 0; i < NUM_SAMPLES; i++)
        {
            // Check if it is an inlier or an outlier based on the distance
            if (line.distance_to_point(edge_points[i]) < MAX_DISTANCE) num_inliers++;
        }

        // If a enough concensus is made, take it as a good model
        if (num_inliers > MIN_CONCENSUS)
        {
            lines.push_back(line);
        }
    }

    // Draw lines
    Mat img_lines = img_color.clone();
    for (size_t i = 0; i < lines.size(); i++)
    {
        // rho and theta
        float rho   = lines[i].rho();   // distance from the origin
        float theta = lines[i].theta(); // angle from the x-axis

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
    imshow("RANSAC - Line", img_result);
    waitKey();

    // Destroy all windows
    destroyAllWindows();

    return 0;
}