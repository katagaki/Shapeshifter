// Square class

#include <string>
#include "ShapeTwoD.h"
#include "Square.h"

// Constructors inherited from superclass
Square::Square() : ShapeTwoD("", false) { }
Square::Square(std::string name, bool containsWarpSpace) : ShapeTwoD(name, containsWarpSpace) { }

// Square must always have 4 points
Square::Square(std::string name, bool containsWarpSpace, Point** points) : ShapeTwoD(name, containsWarpSpace, points) {
    
    pointCount = 4;
    
    boundingRectPoints = new Point*[4];
    
    boundingRectPoints[0] = new Point(points[0] -> x, points[0] -> y);
    boundingRectPoints[1] = new Point(points[1] -> x, points[1] -> y);
    boundingRectPoints[2] = new Point(points[2] -> x, points[2] -> y);
    boundingRectPoints[3] = new Point(points[3] -> x, points[3] -> y);
    
}

// Destructors
Square::~Square() {
    if (boundingRectPoints) {
        delete[] boundingRectPoints;
    }
    if (points) {
        delete[] points;
    }
}

// Operator overload to check if LHS shape's area is less than RHS shape's area
bool operator<(Square& l, Square& r) {
    return (l.computeArea()) < (r.computeArea());
}

// Operator overload to check if LHS shape's area is more than RHS shape's area
bool operator>(Square& l, Square& r) {
    return (l.computeArea()) > (r.computeArea());
}

std::string Square::toString() {
    std::string pointString = ShapeTwoD::toString() + "\nVertices: \n";
    for (int i = 0; i < pointCount; ++i) {
        pointString = pointString + "\n　Point " + std::to_string(i + 1) + ": " + points[i] -> toString();
    }
    return pointString;
}

double Square::computeArea() {
    if (points) {
        return height() * height();
    } else {
        return 0.0;
    }
}

bool Square::isPointInShape(int x, int y) {
    
    int xMin = points[0] -> x;
    int xMax = points[1] -> x;
    int yMin = points[2] -> y;
    int yMax = points[0] -> y;
    
    // Point must be on any bounds to be on a shape
    if (x > xMin && x < xMax && y > yMin && y < yMax) {
        return true;
    } else {
        return false;
    }
    
}

bool Square::isPointOnShape(int x, int y) {
    
    int xMin = points[0] -> x;
    int xMax = points[1] -> x;
    int yMin = points[2] -> y;
    int yMax = points[0] -> y;
    
    // Point must be on any bounds to be on a shape
    if (((x == xMin || x == xMax) && (y >= yMin && y <= yMax)) ||
        ((x >= xMin && x <= xMax) && (y == yMin || y == yMax))) {
        return true;
    } else {
        return false;
    }
    
}

double Square::height() {
    return points[2] -> distanceFrom(points[0]);
}

double Square::width() {
    return height();
}
