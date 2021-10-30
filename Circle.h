#include <string>
#include "ShapeTwoD.h"

#ifndef CIRCLE_CLASS
#define CIRCLE_CLASS

class Circle: public ShapeTwoD {
    
    // Circles contain 2 points
    //
    //          [0] topmost point
    //       /---*---\
    //     /           \
    //    /             \
    //   |       *       |
    //    \     [1]     /
    //     \   center  /
    //       \-------/
    
public:
    
    // Constructors
    Circle();
    Circle(std::string name, bool containsWarpSpace);
    Circle(std::string name, bool containsWarpSpace, Point* points[]);
    
    // Destructors
    ~Circle();
    
    // Operator overloads
    friend bool operator<(const Circle& l, const Circle& r);
    friend bool operator>(const Circle& l, const Circle& r);
    
    // Indirect accessors
    std::string toString();
    double computeArea();
    bool isPointInShape(int x, int y);
    bool isPointOnShape(int x, int y);
    
private:
    
    double radius();
    
};

#endif
