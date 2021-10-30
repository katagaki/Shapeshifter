// ShapeTwoD class

#include <iomanip>
#include <sstream>
#include <string>
#include "ShapeTwoD.h"
#include "Point.h"

// Default constructor
ShapeTwoD::ShapeTwoD() : ShapeTwoD("", false) { }

// Constructor without points
ShapeTwoD::ShapeTwoD(std::string name, bool containsWarpSpace) : name(name), containsWarpSpace(containsWarpSpace) { }

// Constructor defining points
ShapeTwoD::ShapeTwoD(std::string name, bool containsWarpSpace, Point** points) : ShapeTwoD(name, containsWarpSpace) {
    this -> points = points;
}

// Destructor
ShapeTwoD::~ShapeTwoD() {
    if (boundingRectPoints) {
        delete[] boundingRectPoints;
    }
    if (points) {
         delete[] points;
    }
}

// Operator overload to check if LHS shape's area is less than RHS shape's area
bool operator<(ShapeTwoD& l, ShapeTwoD& r) {
    return (l.computeArea()) < (r.computeArea());
}

// Operator overload to check if LHS shape's area is more than RHS shape's area
bool operator>(ShapeTwoD& l, ShapeTwoD& r) {
    return (l.computeArea()) > (r.computeArea());
}

// Accessor to get name
std::string ShapeTwoD::getName() {
    return name;
};

// Accessor to get whether shape contains warp space
bool ShapeTwoD::getContainsWarpSpace() {
    return containsWarpSpace;
};

// Accessor to get array of points
Point** ShapeTwoD::getPoints() {
    return points;
}

// Accessor to get the number of points
int ShapeTwoD::getPointCount() {
    return pointCount;
}

// Accessor to get the bounding points
Point** ShapeTwoD::getBoundingRectPoints() {
    return boundingRectPoints;
}

// ToString function
std::string ShapeTwoD::toString() {
    
    // Convert area to 2 decimal places string
    std::ostringstream s;
    s << std::fixed << std::setprecision(2) << computeArea();
    std::string strArea = s.str();
    
    return "Name: " + name + "\nSpecial Type: " + (containsWarpSpace ? "WS" : "NS") + "\nArea: " + strArea;
}

// Modifier to set the name
void ShapeTwoD::setName(std::string name) {
    this -> name = name;
}

// Modifier to set whether shape contains warp space
void ShapeTwoD::setContainsWarpSpace(bool containsWarpSpace) {
    this -> containsWarpSpace = containsWarpSpace;
}

// Modifier to set the array of points
void ShapeTwoD::setPoints(Point** points) {
    this -> points = points;
}

