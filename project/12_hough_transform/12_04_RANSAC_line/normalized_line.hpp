#ifndef _NORMALIZED_LINE_HPP_
#define _NORMALIZED_LINE_HPP_

#include <cmath>
using namespace std;

#include <opencv2/opencv.hpp>
using namespace cv;

class Normalized_Line
{
public:
    bool fit(const Point &p1, const Point &p2)
    {
        // Fit a line
        // (y2-y1)(x-x1) - (x2-x1)(y-y1) = 0
        // (y2-y1)x - (x2-x1)y - (y2-y1)x1 + (x2-x1)y1 = 0
        // ax + by + c = 0
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = - a * p1.x - b * p1.y;

        // If the parameters are not stable, bail
        double length = sqrt(a*a + b*b);
        if (length < 1e-7) return false;

        // Normalize the parameters
        a /= length;
        b /= length;
        c /= length;

        return true;
    }

    double distance_to_point(const Point &p) const
    {
        //     |ax0 + by0 + c|
        // d = ---------------
        //     sqrt(a^2 + b^2)

        // return fabs(a*p.x + b*p.y + c) / sqrt(a*a + b*b);
        return fabs(a*p.x + b*p.y + c); // normalized
    }

    // signed distance from the origin
    double rho() const
    {
        return -c;
    }

    // angle from the x-axis
    double theta() const
    {
        return atan2(b, a);
    }

protected:
    double a, b, c; // ax + by + c = 0
};

#endif // _LINE_HPP_