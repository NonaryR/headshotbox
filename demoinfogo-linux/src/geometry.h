struct Point {
    double x, y, z;
    Point() {}
    Point(double xx, double yy, double zz) : x(xx), y(yy), z(zz) {}
    Point operator-(const Point &p) const { return Point(x - p.x, y - p.y, z - p.z); }
};

bool intersects(Point line1, Point line2, Point center, double radius, double height);