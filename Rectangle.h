#include <string>
#include "ShapeTwoD.h"

#ifndef RECTANGLE_CLASS
#define RECTANGLE_CLASS

class Rectangle: public ShapeTwoD {
    
    // Rectangles contain 4 points
    //
    // [0]      [1]
    //   +------+
    //   |      |
    //   +------+
    // [2]      [3]
    
public:
    
    // Constructors
    Rectangle();
    Rectangle(std::string name, bool containsWarpSpace);
    Rectangle(std::string name, bool containsWarpSpace, Point* points[]);
    
    // Destructors
    ~Rectangle();
    
    // Operator overloads
    friend bool operator<(const Rectangle& l, const Rectangle& r);
    friend bool operator>(const Rectangle& l, const Rectangle& r);
    
    // Indirect accessors
    std::string toString();
    double computeArea();
    bool isPointInShape(int x, int y);
    bool isPointOnShape(int x, int y);
    
private:
    
    double height();
    double width();
    
};

#endif
