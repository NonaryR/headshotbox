#include "geometry.h"
#include <cmath>
#include <cstdio>

const double epsilon = 0.0001;

bool insideInterval(double x, double a, double b) {
    return x >= a && x <= b;
}

bool intersects(Point line1, Point line2, Point center, double radius, double height) {
    Point start = line1 - center;
    Point direction = line2 - line1;
    start = Point(start.x / radius, start.y / radius, start.z / height);
    direction = Point(direction.x / radius, direction.y / radius, direction.z / height);
    double t0, t1;
    double a = direction.x * direction.x + direction.y * direction.y;
    double b = 2 * start.x * direction.x + 2 * start.y * direction.y;
    double c = start.x * start.x + start.y * start.y - 1;

    double b24ac = b * b - 4 * a * c;
    if (b24ac < 0)
        return false;

    double sqb24ac = sqrt(b24ac);
    t0 = (-b + sqb24ac) / (2 * a);
    t1 = (-b - sqb24ac) / (2 * a);
    if (t0 > t1) {
        double tmp = t0;
        t0 = t1;
        t1 = tmp;
    }

    double y0 = start.z + t0 * direction.z;
    double y1 = start.z + t1 * direction.z;

    if (y0 < -1) {
        if (y1 < -1)
            return false;
        else {
            // hit the cap
            double th = t0 + (t1 - t0) * (y0 + 1) / (y0 - y1);
            if (th <= -epsilon)
                return false;
            return true;
        }
    } else if (y0 >= -1 && y0 <= 1) {
        // hit the cylinder bit
        // check if on the segment
        if (!insideInterval(t0, 0, 1))
            return false;
        if (t0 < -epsilon)
            return false;
        return true;
    } else if (y0 > 1) {
        if (y1 > 1)
            return false;
        else {
            // hit the cap
            double th = t0 + (t1 - t0) * (y0 - 1) / (y0 - y1);
            if (th <= 0)
                return false;
            return true;
        }
    }
    return false;
}
