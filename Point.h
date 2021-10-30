#include <cmath>
#include <string>

#ifndef POINT_CLASS
#define POINT_CLASS

class Point {
    
    // Point on an X and Y axis
    //
    //   Y
    // 3 |
    // 2 |      * Point(3, 2)
    // 1 |
    //   +-------------- X
    //    1  2  3  4  5
    
public:
    int x = 0;
    int y = 0;
    
    // Constructors
    Point();
    Point(int x, int y);
    
    // Indirect accessors
    std::string toString();
    double distanceFrom(Point* point);
    
    // Operator overloads
    friend bool operator==(const Point& l, const Point& r);
    
};

#endif
