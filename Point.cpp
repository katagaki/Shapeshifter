// Coordinate point class

#include <cmath>
#include "Point.h"
#include <string>

Point::Point() {
    Point(0, 0);
}

Point::Point(int x, int y): x(x), y(y) { }

std::string Point::toString() {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

double Point::distanceFrom(Point* point) {
    return std::sqrt(((x - point -> x) * (x - point -> x)) +
                     ((y - point -> y) * (y - point -> y)));
}

// Operator = on 2 points returns true if the 2 points are the same
bool operator==(const Point& l, const Point& r) {
    bool isXEquals = l.x == r.x;
    bool isYEquals = l.y == r.y;
    return isXEquals && isYEquals;
}
