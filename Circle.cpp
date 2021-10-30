// Circle class

#include <string>
#include "Circle.h"
#include "ShapeTwoD.h"

// Constructors inherited from superclass
Circle::Circle() : ShapeTwoD("", false) { }
Circle::Circle(std::string name, bool containsWarpSpace) : ShapeTwoD(name, containsWarpSpace) { }

// Circle must always have 2 points
Circle::Circle(std::string name, bool containsWarpSpace, Point** points) : ShapeTwoD(name, containsWarpSpace, points) {
    
    pointCount = 2;
    
    // Set the bounding rectangle
    boundingRectPoints = new Point*[4];
    
    boundingRectPoints[0] = new Point((points[0] -> x) - radius(), points[0] -> y);
    boundingRectPoints[1] = new Point((points[0] -> x) + radius(), points[0] -> y);
    boundingRectPoints[2] = new Point((points[0] -> x) - radius(), (points[1] -> y) - radius());
    boundingRectPoints[3] = new Point((points[0] -> x) + radius(), (points[1] -> y) - radius());
    
}

// Destructors
Circle::~Circle() {
    if (boundingRectPoints) {
        delete[] boundingRectPoints;
    }
    if (points) {
        delete[] points;
    }
}

// Operator overload to check if LHS shape's area is less than RHS shape's area
bool operator<(Circle& l, Circle& r) {
    return (l.computeArea()) < (r.computeArea());
}

// Operator overload to check if LHS shape's area is more than RHS shape's area
bool operator>(Circle& l, Circle& r) {
    return (l.computeArea()) > (r.computeArea());
}

std::string Circle::toString() {
    std::string pointString = ShapeTwoD::toString() + "\nVertices: \n";
    for (int i = 0; i < pointCount; ++i) {
        pointString = pointString + "\n　Point " + std::to_string(i + 1) + ": " + points[i] -> toString();
    }
    return pointString;
}

double Circle::computeArea() {
    if (points) {
        return 3.14 * radius() * radius();
    } else {
        return 0.0;
    }
}

bool Circle::isPointInShape(int x, int y) {
    Point* p = new Point(x, y);
    if ((points[1] -> distanceFrom(p)) < radius()) {
        delete p;
        return true;
    } else {
        delete p;
        return false;
    }
}

bool Circle::isPointOnShape(int x, int y) {
    Point* p = new Point(x, y);
    if ((points[1] -> distanceFrom(p)) == radius()) {
        delete p;
        return true;
    } else {
        delete p;
        return false;
    }
}

double Circle::radius() {
    return (points[0] -> y) - (points[1] -> y);
}
