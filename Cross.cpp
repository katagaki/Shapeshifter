// Cross class

#include <string>
#include "Cross.h"
#include "Rectangle.h"
#include "ShapeTwoD.h"

// Constructors inherited from superclass
Cross::Cross() : ShapeTwoD("", false) { }
Cross::Cross(std::string name, bool containsWarpSpace) : ShapeTwoD(name, containsWarpSpace) { }

// Add bounding rectangle when constructing with points
// Cross must always have 12 points
Cross::Cross(std::string name, bool containsWarpSpace, Point** points) : ShapeTwoD(name, containsWarpSpace, points) {
    
    pointCount = 12;
    
    boundingRectPoints = new Point*[4];
    
    boundingRectPoints[0] = new Point(points[0] -> x, points[2] -> y);
    boundingRectPoints[1] = new Point(points[5] -> x, points[2] -> y);
    boundingRectPoints[2] = new Point(points[0] -> x, points[8] -> y);
    boundingRectPoints[3] = new Point(points[5] -> x, points[8] -> y);
    
    // Set the bounding rectangle
    boundingRect = new Rectangle(name + "_BOUND",
                                 false,
                                 boundingRectPoints);
    
}

// Destructors
Cross::~Cross() {
    delete boundingRect;
    if (boundingRectPoints) {
        delete[] boundingRectPoints;
    }
    if (points) {
        delete[] points;
    }
}

// Operator overload to check if LHS shape's area is less than RHS shape's area
bool operator<(Cross& l, Cross& r) {
    return (l.computeArea()) < (r.computeArea());
}

// Operator overload to check if LHS shape's area is more than RHS shape's area
bool operator>(Cross& l, Cross& r) {
    return (l.computeArea()) > (r.computeArea());
}

std::string Cross::toString() {
    std::string pointString = ShapeTwoD::toString() + "\nVertices: \n";
    for (int i = 0; i < pointCount; ++i) {
        pointString = pointString + "\n　Point " + std::to_string(i + 1) + ": " + points[i] -> toString();
    }
    return pointString;
}

double Cross::computeArea() {
    if (points) {
        return (boundingRect -> computeArea()) - topLeftBoundingRectArea() - topRightBoundingRectArea() - bottomLeftBoundingRectArea() - bottomRightBoundingRectArea();
    } else {
        return 0.0;
    }
}

bool Cross::isPointInShape(int x, int y) {
    
    int boundXMin = (boundingRect -> getPoints())[0] -> x;
    int boundXMax = (boundingRect -> getPoints())[1] -> x;
    int boundYMin = (boundingRect -> getPoints())[2] -> y;
    int boundYMax = (boundingRect -> getPoints())[0] -> y;
    
    // Check if point is within bounding rectangle
    if (x > boundXMin && x < boundXMax && y > boundYMin && y < boundYMax) {
        
        // Check if point is in the top left corner hole
        if (x > (points[0] -> x) && x <= (points[1] -> x) && y >= (points[1] -> y) && y < (points[2] -> y)) {
            return false;
        }
        
        // Check if point is in the top right corner hole
        if (x >= (points[4] -> x) && x < (points[5] -> x) && y >= (points[4] -> y) && y < (points[3] -> y)) {
            return false;
        }
        
        // Check if point is in the bottom left corner hole
        if (x > (points[6] -> x) && x <= (points[7] -> x) && y > (points[8] -> y) && y <= (points[7] -> y)) {
            return false;
        }
        
        // Check if point is in the bottom right corner hole
        if (x >= (points[10] -> x) && x < (points[11] -> x) && y > (points[9] -> y) && y <= (points[10] -> y)) {
            return false;
        }
        
        return true;
        
    } else {
        return false;
    }
    
}

bool Cross::isPointOnShape(int x, int y) {
    
    return (x >= (points[0] -> x)  && x <= (points[1] -> x)  && y == (points[0] -> y))  ||
           (x == (points[2] -> x)  && y >= (points[1] -> y)  && y <= (points[2] -> y))  ||
           (x >= (points[2] -> x)  && x <= (points[3] -> x)  && y == (points[2] -> y))  ||
           (x == (points[3] -> x)  && y <= (points[3] -> y)  && y >= (points[4] -> y))  ||
           (x >= (points[4] -> x)  && x <= (points[5] -> x)  && y == (points[4] -> y))  ||
           (x == (points[5] -> x)  && y <= (points[5] -> y)  && y >= (points[11] -> y)) ||
           (x <= (points[11] -> x) && x >= (points[10] -> x) && y == (points[11] -> y)) ||
           (x == (points[10] -> x) && y <= (points[10] -> y) && y >= (points[9] -> y))  ||
           (x <= (points[9] -> x)  && x >= (points[8] -> x)  && y == (points[10] -> y)) ||
           (x == (points[8] -> x)  && y >= (points[8] -> y)  && y <= (points[7] -> y))  ||
           (x <= (points[7] -> x)  && x >= (points[6] -> x)  && y == (points[7] -> y))  ||
           (x == (points[6] -> x)  && y >= (points[6] -> y)  && y <= (points[0] -> y));
    
}

double Cross::topLeftBoundingRectArea() {
    return (points[1] -> distanceFrom(points[2])) * (points[1] -> distanceFrom(points[0]));
}

double Cross::topRightBoundingRectArea() {
    return (points[4] -> distanceFrom(points[3])) * (points[5] -> distanceFrom(points[4]));
}

double Cross::bottomLeftBoundingRectArea() {
    return (points[6] -> distanceFrom(points[7])) * (points[7] -> distanceFrom(points[8]));
}

double Cross::bottomRightBoundingRectArea() {
    return (points[9] -> distanceFrom(points[10])) * (points[10] -> distanceFrom(points[11]));
}
